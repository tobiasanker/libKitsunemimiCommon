/**
 *  @file    data_items_DataArray_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef DATAITEMS_DATAARRAY_TEST_H
#define DATAITEMS_DATAARRAY_TEST_H

#include <testing/unit_test.h>

namespace Kitsune
{
namespace Common
{
class DataArray;

class DataItems_DataArray_Test
        : public Kitsune::Common::UnitTest
{
public:
    DataItems_DataArray_Test();

private:
    void operator_test();
    void get_test();
    void getSize_test();
    void remove_test();
    void copy_test();
    void print_test();
    void getType_test();
    void isValue_isObject_isArray_test();
    void toValue_toObject_toArray_test();
    void toString_toInt_toFloat_test();

    void append_test();

    DataArray initTestArray();
};

}  // namespace Common
}  // namespace Kitsune

#endif // DATAITEMS_DATAARRAY_TEST_H