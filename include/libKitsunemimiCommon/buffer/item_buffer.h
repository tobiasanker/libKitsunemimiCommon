/**
 *  @file       item_buffer.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef ITEM_BUFFER_H
#define ITEM_BUFFER_H

#include <libKitsunemimiCommon/buffer/data_buffer.h>

namespace Kitsunemimi
{

class ItemBuffer;
template<typename T>
inline T* getBuffer(ItemBuffer &itembuffer);

class ItemBuffer
{
public:
    uint32_t itemSize = 0;
    uint64_t itemCapacity = 0;
    uint64_t numberOfItems = 0;
    DataBuffer buffer = DataBuffer(1);
    bool dynamic = false;

    ItemBuffer();

    /**
     * @brief addNewItem
     * @param itemBuffer
     * @param item
     * @param simple
     * @return
     */
    template<typename T>
    uint64_t addNewItem(T &item)
    {
        assert(itemSize != 0);
        assert((numberOfItems + 1) * itemSize < buffer.bufferPosition);

        uint64_t position = 0xFFFFFFFFFFFFFFFF;
        while(lock.test_and_set(std::memory_order_acquire)) { asm(""); }

        if(dynamic == false)
        {
            position = numberOfItems;
            numberOfItems++;
        }
        else
        {
            position = reserveDynamicItem();
        }

        T* array = static_cast<T*>(buffer.data);
        array[position] = item;

        lock.clear(std::memory_order_release);

        return position;
    }

    /**
     * @brief initBuffer
     * @param numberOfItems
     * @return
     */
    template<typename T>
    bool initBuffer(const uint64_t numberOfItems)
    {
        bool ret = initDataBlocks(numberOfItems, sizeof(T));
        if(ret == false) {
            return false;
        }

        T* items = static_cast<T*>(buffer.data);
        for(uint32_t i = 0; i < numberOfItems; i++)
        {
            T newItem;
            items[i] = newItem;
        }
        this->numberOfItems = numberOfItems;

        return true;
    }

    bool deleteAll();
    bool deleteDynamicItem(const uint64_t itemPos);

private:
    uint64_t* m_allocationList = nullptr;
    std::atomic_flag lock = ATOMIC_FLAG_INIT;

    uint64_t bytePositionOfFirstEmptyBlock = 0xFFFFFFFFFFFFFFFF;
    uint64_t bytePositionOfLastEmptyBlock = 0xFFFFFFFFFFFFFFFF;

    bool initDataBlocks(const uint64_t numberOfItems,
                        const uint32_t itemSize);
    uint64_t reuseItemPosition();
    uint64_t reserveDynamicItem();
};

/**
 * @brief getBuffer
 * @param itembuffer
 * @return
 */
template<typename T>
inline T*
getBuffer(ItemBuffer &itembuffer)
{
    return static_cast<T*>(itembuffer.buffer.data);
}

}

#endif // ITEM_BUFFER_H