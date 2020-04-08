#include "stack_buffer_test.h"
#include <libKitsunemimiCommon/buffer/stack_buffer.h>

namespace Kitsunemimi
{

StackBuffer_Test::StackBuffer_Test()
    : Kitsunemimi::CompareTestHelper("StackBuffer_Test")
{
    constructor_test();
    addNewToStack_test();
    writeDataIntoBuffer_test();
    addObjectToBuffer_test();
    getFirstElement_test();
    removeFirstFromStack_test();
    resetBuffer_test();
}

/**
 * @brief constructor_test
 */
void
StackBuffer_Test::constructor_test()
{
    // init
    bool isNullptr = false;

    // test if m_stackBufferReserve is correctly set
    isNullptr = Kitsunemimi::m_stackBufferReserve == nullptr;
    TEST_EQUAL(isNullptr, true);

    // test constructor
    StackBuffer stackBuffer(10, 20);
    TEST_EQUAL(stackBuffer.preOffset, 10);
    TEST_EQUAL(stackBuffer.postOffset, 20);
    TEST_EQUAL(stackBuffer.effectiveBlockSize, STACK_BUFFER_BLOCK_SIZE-30);
    TEST_EQUAL(stackBuffer.blockSize, STACK_BUFFER_BLOCK_SIZE);

    // test if m_stackBufferReserve is correctly set after first buffer-creation
    isNullptr = Kitsunemimi::m_stackBufferReserve == nullptr;
    TEST_EQUAL(isNullptr, false);
}

/**
 * @brief addNewToStack_test
 */
void
StackBuffer_Test::addNewToStack_test()
{
    // init
    StackBuffer stackBuffer;

    // run test
    TEST_EQUAL(stackBuffer.blocks.size(), 0);
    addNewToStackBuffer(stackBuffer);
    TEST_EQUAL(stackBuffer.blocks.size(), 1);
}

/**
 * @brief writeDataIntoBuffer
 */
void
StackBuffer_Test::writeDataIntoBuffer_test()
{
    // init
    StackBuffer stackBuffer;
    DataBuffer buffer(STACK_BUFFER_BLOCK_SIZE/4096);

    // run test
    writeDataIntoStackBuffer(stackBuffer, buffer.data, 1000);
    TEST_EQUAL(stackBuffer.blocks.size(), 1);
    writeDataIntoStackBuffer(stackBuffer, buffer.data, 1000);
    TEST_EQUAL(stackBuffer.blocks.size(), 1);
    writeDataIntoStackBuffer(stackBuffer, buffer.data, buffer.totalBufferSize);
    TEST_EQUAL(stackBuffer.blocks.size(), 2);
}

/**
 * @brief addObjectToBuffer_test
 */
void
StackBuffer_Test::addObjectToBuffer_test()
{
    // init
    StackBuffer stackBuffer;
    uint64_t testValue = 42;

    // run test
    addObjectToStackBuffer(stackBuffer, &testValue);
    TEST_EQUAL(stackBuffer.blocks.at(0)->bufferPosition, sizeof(testValue));
}

/**
 * @brief getFirstElement_test
 */
void
StackBuffer_Test::getFirstElement_test()
{
    // init
    StackBuffer stackBuffer;
    DataBuffer buffer(STACK_BUFFER_BLOCK_SIZE/4096);
    bool isNullptr = false;
    DataBuffer* result = nullptr;

    TEST_EQUAL(stackBuffer.blocks.size(), 0);
    result = getFirstElementFromStackBuffer(stackBuffer);
    isNullptr = result == nullptr;
    TEST_EQUAL(isNullptr, true);
    TEST_EQUAL(stackBuffer.blocks.size(), 0);

    // prepare test-buffer
    uint64_t testValue = 42;
    addObjectToBuffer(buffer, &testValue);
    writeDataIntoStackBuffer(stackBuffer, buffer.data, buffer.totalBufferSize);

    TEST_EQUAL(stackBuffer.blocks.size(), 1);
    result = getFirstElementFromStackBuffer(stackBuffer);
    isNullptr = result == nullptr;
    TEST_EQUAL(isNullptr, false);
    TEST_EQUAL(stackBuffer.blocks.size(), 1);

    uint64_t ret = *static_cast<uint64_t*>(result->data);
    TEST_EQUAL(ret, testValue);
}

/**
 * @brief removeFirstFromStack_test
 */
void
StackBuffer_Test::removeFirstFromStack_test()
{
    // init
    StackBuffer stackBuffer;
    DataBuffer buffer(STACK_BUFFER_BLOCK_SIZE/4096);

    // prepare test-buffer
    writeDataIntoStackBuffer(stackBuffer, buffer.data, buffer.totalBufferSize);
    writeDataIntoStackBuffer(stackBuffer, buffer.data, buffer.totalBufferSize);

    // run test
    TEST_EQUAL(stackBuffer.blocks.size(), 2);
    TEST_EQUAL(removeFirstFromStackBuffer(stackBuffer), true);
    TEST_EQUAL(stackBuffer.blocks.size(), 1);
    TEST_EQUAL(removeFirstFromStackBuffer(stackBuffer), true);
    TEST_EQUAL(stackBuffer.blocks.size(), 0);
    TEST_EQUAL(removeFirstFromStackBuffer(stackBuffer), false);
}

/**
 * @brief resetBuffer_test
 */
void
StackBuffer_Test::resetBuffer_test()
{
    // init
    StackBuffer stackBuffer;
    DataBuffer buffer(STACK_BUFFER_BLOCK_SIZE/4096);

    // prepare test-buffer
    writeDataIntoStackBuffer(stackBuffer, buffer.data, buffer.totalBufferSize);
    writeDataIntoStackBuffer(stackBuffer, buffer.data, buffer.totalBufferSize);

    // run test
    resetStackBuffer(stackBuffer);

    // check result
    TEST_EQUAL(stackBuffer.blocks.size(), 0);
    bool isNullptr = stackBuffer.localReserve == nullptr;
    TEST_EQUAL(isNullptr, false);
}

} // namespace Kitsunemimi
