﻿/**
 *  @file    data_items.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 *
 *  @brief data-items for universal data-structures
 *
 *  @detail These was originally created in libKitsuneJson. Thats why the strint-output of the
 *          structure has still json-format. It can handle list, maps and values and is used
 *          in all of the kitsune-parser libraries as internal data-representation.
 */

#include <common_items/data_items.h>

namespace Kitsune
{
namespace Common
{

//===================================================================
// AbstractData
//===================================================================

DataItem::~DataItem() {}

/**
 * @brief request type, of the current data-object
 *
 * @return object-specific entry of the dataTypes-enumeration
 */
DataItem::dataTypes
DataItem::getType() const
{
    return m_type;
}

/**
 * @brief check if DataItem is a DataValue
 */
bool
DataItem::isValue() const
{
    if(m_type == VALUE_TYPE)
    {
        return true;
    }
    return false;
}

/**
 * @brief check if DataItem is a DataMap
 */
bool
DataItem::isMap() const
{
    if(m_type == MAP_TYPE) {
        return true;
    }
    return false;
}

/**
 * @brief check if DataItem is a DataArray
 */
bool
DataItem::isArray() const
{
    if(m_type == ARRAY_TYPE) {
        return true;
    }
    return false;
}

/**
 * @brief convert to a DataArray
 */
DataArray*
DataItem::toArray()
{
    if(m_type == ARRAY_TYPE) {
        return static_cast<DataArray*>(this);
    }
    return nullptr;
}

/**
 * @brief convert to a DataMap
 */
DataMap*
DataItem::toMap()
{
    if(m_type == MAP_TYPE) {
        return static_cast<DataMap*>(this);
    }
    return nullptr;
}

/**
 * @brief convert to a DataVolue
 */
DataValue*
DataItem::toValue()
{
    if(m_type == VALUE_TYPE)
    {
        return static_cast<DataValue*>(this);
    }
    return nullptr;
}

/**
 * @brief request the string of the data-value, if it is from string-type
 *
 * @return string of the data-value, if data-value is from string-type, else empty string
 */
const std::string
DataItem::getString() const
{
    if(m_valueType == STRING_TYPE)
    {
        const DataValue* value = dynamic_cast<const DataValue*>(this);
        return std::string(value->m_content.stringValue);
    }
    if(m_valueType == INT_TYPE)
    {
        const DataValue* value = dynamic_cast<const DataValue*>(this);
        return std::to_string(value->m_content.intValue);
    }
    if(m_valueType == FLOAT_TYPE)
    {
        const DataValue* value = dynamic_cast<const DataValue*>(this);
        return std::to_string(value->m_content.floatValue);
    }
    return "";
}

/**
 * @brief request the integer of the data-value, if it is from int-type
 *
 * @return integer of the data-value, if data-value is from int-type, else empty 0
 */
int
DataItem::getInt()
{
    if(m_valueType == INT_TYPE)
    {
        DataValue* value = dynamic_cast<DataValue*>(this);
        return value->m_content.intValue;
    }
    return 0;
}


/**
 * @brief request the flaot of the data-value, if it is from float-type
 *
 * @return float of the data-value, if data-value is from float-type, else empty 0.0
 */
float
DataItem::getFloat()
{
    if(m_valueType == FLOAT_TYPE)
    {
        DataValue* value = dynamic_cast<DataValue*>(this);
        return value->m_content.floatValue;
    }
    return 0.0f;
}

/**
 * @brief add indent and linebreak to be better human-readable
 */
void
DataItem::addIndent(std::string* output,
                    const bool indent,
                    const uint32_t level)
{
    if(indent == true)
    {
        output->append("\n");
        for(uint32_t i = 0; i < level; i++)
        {
            output->append("    ");
        }
    }
}

//===================================================================
// DataValue
//===================================================================

/**
 * @brief DataValue::DataValue
 */
DataValue::DataValue()
{
    m_type = VALUE_TYPE;
    m_valueType = STRING_TYPE;

    m_content.stringValue = new char[1];
    m_content.stringValue[0] = '\0';
}

/**
 * @brief data-value for strings
 */
DataValue::DataValue(const std::string &text)
{
    m_type = VALUE_TYPE;
    m_valueType = STRING_TYPE;

    m_content.stringValue = new char[text.size()+1];
    memcpy(m_content.stringValue, text.c_str(), text.size());
    m_content.stringValue[text.size()] = '\0';
}

/**
 * @brief data-value for integers
 */
DataValue::DataValue(const int value)
{
    m_type = VALUE_TYPE;
    m_valueType = INT_TYPE;
    m_content.intValue = value;
}

/**
 * @brief data-value for float
 */
DataValue::DataValue(const float value)
{
    m_type = VALUE_TYPE;
    m_valueType = FLOAT_TYPE;
    m_content.floatValue = value;
}

/**
 * @brief destructor
 */
DataValue::~DataValue() {}

/**
 * @brief get type inside the data-value
 *
 * @return value-type
 */
DataValue::dataValueTypes
DataValue::getValueType()
{
    return m_valueType;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime nullptr
 */
DataItem*
DataValue::operator[](const std::string)
{
    return nullptr;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime nullptr
 */
DataItem*
DataValue::operator[](const uint64_t)
{
    return nullptr;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime nullptr
 */
DataItem*
DataValue::get(const std::string)
{
    return nullptr;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime nullptr
 */
DataItem*
DataValue::get(const uint64_t)
{
    return nullptr;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime 0
 */
uint64_t
DataValue::size()
{
    return getString().size();
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime false
 */
bool
DataValue::remove(const std::string&)
{
    return false;
}

/**
 * @brief fake-method which exist here only for the inheritance and returns everytime false
 */
bool
DataValue::remove(const uint64_t)
{
    return false;
}

/**
 * @brief copy the data-value
 *
 * @return pointer to a copy of the value
 */
DataItem*
DataValue::copy()
{
    DataValue* tempItem = nullptr;
    if(m_valueType == STRING_TYPE) {
        tempItem = new DataValue(std::string(m_content.stringValue));
    }
    if(m_valueType == INT_TYPE) {
        tempItem = new DataValue(m_content.intValue);
    }
    if(m_valueType == FLOAT_TYPE) {
        tempItem = new DataValue(m_content.floatValue);
    }
    return tempItem;
}

/**
 * @brief return the content as string
 */
std::string
DataValue::toString(const bool,
                    std::string* output,
                    const uint32_t)
{
    std::string out = "";
    if(output == nullptr) {
        output = &out;
    }

    if(m_valueType == STRING_TYPE)
    {
        output->append("\"");
        output->append(std::string(m_content.stringValue));
        output->append("\"");
    }
    if(m_valueType == INT_TYPE) {
        output->append(std::to_string(m_content.intValue));
    }
    if(m_valueType == FLOAT_TYPE) {
        output->append(std::to_string(m_content.floatValue));
    }

    return out;
}

/**
 * @brief writes a new string into the data-value
 */
void
DataValue::setValue(const std::string &item)
{
    if(m_valueType == STRING_TYPE) {
        delete m_content.stringValue;
    }

    m_type = VALUE_TYPE;
    m_valueType = STRING_TYPE;

    m_content.stringValue = new char[item.size()+1];
    memcpy(m_content.stringValue, item.c_str(), item.size());
    m_content.stringValue[item.size()] = '\0';
}

/**
 * @brief writes a new integer into the data-value
 */
void
DataValue::setValue(const int &item)
{
    if(m_valueType == STRING_TYPE) {
        delete m_content.stringValue;
    }

    m_type = VALUE_TYPE;
    m_valueType = INT_TYPE;

    m_content.intValue = item;
}

/**
 * @brief writes a new integer into the data-value
 */
void
DataValue::setValue(const float &item)
{
    if(m_valueType == STRING_TYPE) {
        delete m_content.stringValue;
    }

    m_type = VALUE_TYPE;
    m_valueType = FLOAT_TYPE;

    m_content.floatValue = item;
}

//===================================================================
// DataMap
//===================================================================

/**
 * @brief object for key-value-pairs
 */
DataMap::DataMap()
{
    m_type = MAP_TYPE;
}

/**
 * @brief delete all items in the key-value-list
 */
DataMap::~DataMap()
{
    std::map<std::string, DataItem*>::iterator it;
    for(it = m_map.begin(); it != m_map.end(); it++)
    {
        DataItem* tempItem = it->second;
        delete tempItem;
    }
    m_map.clear();
}

/**
 * @brief get a specific item of the object
 *
 * @return nullptr if index in key is to high, else object
 */
DataItem*
DataMap::operator[](const std::string key)
{
    return get(key);
}

/**
 * @brief get a specific item of the object
 *
 * @return nullptr if index is to high, else object
 */
DataItem*
DataMap::operator[](const uint64_t index)
{
    return get(index);
}

/**
 * @brief get a specific item of the object
 *
 * @return nullptr if index in key is to high, else object
 */
DataItem*
DataMap::get(const std::string key)
{
    std::map<std::string, DataItem*>::iterator it;
    it = m_map.find(key);

    if(it != m_map.end()) {
        return it->second;
    }

    return nullptr;
}

/**
 * @brief get a specific item of the object
 *
 * @return nullptr if index is to high, else object
 */
DataItem*
DataMap::get(const uint64_t index)
{
    if(m_map.size() <= index) {
        return nullptr;
    }

    uint32_t counter = 0;
    std::map<std::string, DataItem*>::iterator it;
    for(it = m_map.begin();
        it != m_map.end();
        it++)
    {
        if(counter == index) {
            return it->second;
        }
        counter++;
    }

    return nullptr;
}

/**
 * @brief getter for the number of elements in the key-value-list
 *
 * @return number of elements in the key-value-list
 */
uint64_t
DataMap::size()
{
    return m_map.size();
}

/**
 * @brief get list of keys of the objects-map
 *
 * @return string-list with the keys of the map
 */
std::vector<std::string>
DataMap::getKeys()
{
    std::vector<std::string> result;
    std::map<std::string, DataItem*>::iterator it;
    for(it = m_map.begin(); it != m_map.end(); it++)
    {
        result.push_back(it->first);
    }
    return result;
}

/**
 * @brief get list of values of the objects-map
 *
 * @return DataItem-list with the keys of the map
 */
std::vector<DataItem*>
DataMap::getValues()
{
    std::vector<DataItem*> result;
    std::map<std::string, DataItem*>::iterator it;
    for(it = m_map.begin(); it != m_map.end(); it++)
    {
        result.push_back(it->second);
    }
    return result;
}

/**
 * @brief check if a key is in the object-map
 *
 * @return false if the key doesn't exist, else true
 */
bool
DataMap::contains(const std::string &key)
{
    std::map<std::string, DataItem*>::iterator it;
    it = m_map.find(key);

    if(it != m_map.end())
    {
        return true;
    }
    return false;
}

/**
 * @brief get the string-value behind the key inside the data-map
 */
std::string
DataMap::getStringByKey(const std::string &key)
{
    DataItem* item = get(key);
    return item->getString();
}

/**
 * @brief get the int-value behind the key inside the data-map
 */
int
DataMap::getIntByKey(const std::string &key)
{
    DataItem* item = get(key);
    return item->getInt();
}

/**
 * @brief get the float-value behind the key inside the data-map
 */
float
DataMap::getFloatByKey(const std::string &key)
{
    DataItem* item = get(key);
    return item->getFloat();
}

/**
 * @brief remove an item from the key-value-list
 *
 * @return false if the key doesn't exist, else true
 */
bool
DataMap::remove(const std::string &key)
{
    std::map<std::string, DataItem*>::iterator it;
    it = m_map.find(key);

    if(it != m_map.end())
    {
        DataItem* tempItem = it->second;
        delete tempItem;
        m_map.erase(it);
        return true;
    }

    return false;
}

/**
 * @brief remove an item from the object
 *
 * @return false if index is to high, else true
 */
bool
DataMap::remove(const uint64_t index)
{
    if(m_map.size() <= index) {
        return false;
    }

    uint32_t counter = 0;
    std::map<std::string, DataItem*>::iterator it;
    for(it = m_map.begin(); it != m_map.end(); it++)
    {
        if(counter == index)
        {
            DataItem* tempItem = it->second;
            delete tempItem;
            m_map.erase(it);
            return true;
        }
        counter++;
    }
    return false;
}

/**
 * @brief copy the object with all elements
 *
 * @return pointer to a copy of the object
 */
DataItem*
DataMap::copy()
{
    DataMap* tempItem = new DataMap();
    std::map<std::string, DataItem*>::iterator it;
    for(it = m_map.begin(); it != m_map.end(); it++)
    {
        tempItem->insert(it->first, it->second->copy());
    }
    return tempItem;
}

/**
 * @brief return the content as string
 */
std::string
DataMap::toString(const bool indent,
                     std::string* output,
                     const uint32_t level)
{
    std::string out = "";
    if(output == nullptr) {
        output = &out;
    }

    bool firstPring = false;
    output->append("{");

    for(uint8_t typeCounter = 1; typeCounter < 6; typeCounter++)
    {
        std::map<std::string, DataItem*>::iterator it;
        for(it = m_map.begin(); it != m_map.end(); it++)
        {
            if(it->second != nullptr
                    && it->second->getType() != typeCounter)
            {
                continue;
            }

            if(firstPring) {
                output->append(",");
            }
            firstPring = true;

            addIndent(output, indent, level+1);

            output->append("\"");
            output->append(it->first);
            output->append("\"");
            output->append(":");

            if(indent == true) {
                output->append(" ");
            }

            // TODO: add unit-tests for nullptr-case
            if(it->second == nullptr) {
                output->append("NULL");
            } else {
                it->second->toString(indent, output, level+1);
            }
        }
    }

    addIndent(output, indent, level);
    output->append("}");

    return out;
}

/**
 * @brief add new key-value-pair to the object
 *
 * @return false if key already exist, else true
 */
bool
DataMap::insert(const std::string &key,
                   DataItem* value,
                   bool force)
{


    std::map<std::string, DataItem*>::iterator it;
    it = m_map.find(key);

    if(it != m_map.end()
            && force == false)
    {
        return false;
    }

    if(it != m_map.end()) {
        it->second = value;
    } else {
        m_map.insert(std::pair<std::string, DataItem*>(key, value));
    }
    return true;
}

//===================================================================
// DataArray
//===================================================================

/**
 * @brief array for items in data-style
 */
DataArray::DataArray()
{
    m_type = ARRAY_TYPE;
}

/**
 * @brief delete all items in the array
 */
DataArray::~DataArray()
{
    //std::cout<<"DataArray: "<<this<<std::endl;
    for(uint32_t i = 0; i < m_array.size(); i++)
    {
        DataItem* tempItem = m_array[i];
        delete tempItem;
    }
    m_array.clear();
}

/**
 * @brief get a specific item of the array
 *
 * @return nullptr if index in key is to high, else true
 */
DataItem*
DataArray::operator[](const std::string key)
{
    return get(key);
}

/**
 * @brief get a specific item of the array
 *
 * @return nullptr if index is to high, else true
 */
DataItem*
DataArray::operator[](const uint64_t index)
{
    return get(index);
}

/**
 * @brief get a specific item of the array
 *
 * @return nullptr if index in key is to high, else object
 */
DataItem*
DataArray::get(const std::string)
{
    return nullptr;
}

/**
 * @brief get a specific item of the array
 *
 * @return nullptr if index is to high, else the object
 */
DataItem*
DataArray::get(const uint64_t index)
{
    if(m_array.size() <= index) {
        return nullptr;
    }

    return m_array[index];
}

/**
 * @brief getter for the number of elements in the array
 *
 * @return number of elements in the array
 */
uint64_t
DataArray::size()
{
    return m_array.size();
}

/**
 * @brief remove an item from the array
 *
 * @return false if index in key is to high, else true
 */
bool
DataArray::remove(const std::string &key)
{
    const uint32_t index = static_cast<uint32_t>(std::stoi(key));
    if(m_array.size() <= index) {
        return false;
    }
    DataItem* tempItem = m_array[index];
    delete tempItem;
    m_array.erase(m_array.begin() + index);
    return true;
}

/**
 * @brief remove an item from the array
 *
 * @return false if index is to high, else true
 */
bool
DataArray::remove(const uint64_t index)
{
    if(m_array.size() <= index) {
        return false;
    }
    DataItem* tempItem = m_array[index];
    delete tempItem;
    m_array.erase(m_array.begin() + index);
    return true;
}

/**
 * @brief copy the array with all elements
 *
 * @return pointer to a copy of the array
 */
DataItem*
DataArray::copy()
{
    DataArray* tempItem = new DataArray();
    for(uint32_t i = 0; i < m_array.size(); i++)
    {
        tempItem->append(m_array[i]->copy());
    }
    return tempItem;
}

/**
 * @brief return the content as string
 */
std::string
DataArray::toString(const bool indent,
                    std::string* output,
                    const uint32_t level)
{
    std::string out = "";
    if(output == nullptr) {
        output = &out;
    }

    output->append("[");
    addIndent(output, indent, level+1);

    std::vector<DataItem*>::iterator it;
    for(it = m_array.begin(); it != m_array.end(); it++)
    {
        if(it != m_array.begin())
        {
            output->append(",");
            addIndent(output, indent, level+1);
        }

        if((*it) == nullptr) {
            continue;
        }

        (*it)->toString(indent, output, level+1);
    }

    addIndent(output, indent, level);
    output->append("]");

    return out;
}

/**
 * @brief add a new item to the array
 *
 * @return false, if new item-pointer is nullptr, else true
 */
bool
DataArray::append(DataItem* item)
{
    if(item == nullptr) {
        return false;
    }

    m_array.push_back(item);
    return true;
}


}  // namespace Common
}  // namespace Kitsune
