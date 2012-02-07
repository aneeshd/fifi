// Copyright Steinwurf APS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE_1_0.txt or
// http://www.steinwurf.dk/licensing

#include <gtest/gtest.h>

#include <fifi/extended_log_table.h>
#include <fifi/field_types.h>

#include "expected_results.h"

TEST(test_extended_log_table, binary8multiply)
{

    fifi::extended_log_table<fifi::binary8> extlogtable;

    uint32_t size = expected_multiply_binary8_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::binary8> res = expected_multiply_binary8[i];
	EXPECT_EQ(extlogtable.multiply(res.arg1, res.arg2), res.result);
    }
}


TEST(test_extended_log_table, binary8invert)
{

    fifi::extended_log_table<fifi::binary8> extlogtable;

    uint32_t size = expected_invert_binary8_size;
    
    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_1<fifi::binary8> res = expected_invert_binary8[i];
	EXPECT_EQ(extlogtable.invert(res.arg1), res.result);
    }

}


TEST(test_extended_log_table, binary8divide)
{
    fifi::extended_log_table<fifi::binary8> extlogtable;

    uint32_t size = expected_divide_binary8_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::binary8> res = expected_divide_binary8[i];	
	EXPECT_EQ(extlogtable.divide(res.arg1, res.arg2), res.result);
    }
}


TEST(test_extended_log_table, binary16multiply)
{

    fifi::extended_log_table<fifi::binary16> extlogtable;

    uint32_t size = expected_multiply_binary16_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::binary16> res = expected_multiply_binary16[i];
	EXPECT_EQ(extlogtable.multiply(res.arg1, res.arg2), res.result);
    }

}


TEST(test_extended_log_table, binary16invert)
{

    fifi::extended_log_table<fifi::binary16> extlogtable;

    uint32_t size = expected_invert_binary16_size;
    
    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_1<fifi::binary16> res = expected_invert_binary16[i];
	EXPECT_EQ(extlogtable.invert(res.arg1), res.result);
    }

}


TEST(test_extended_log_table, binary16divide)
{

    fifi::extended_log_table<fifi::binary16> extlogtable;

    uint32_t size = expected_divide_binary16_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::binary16> res = expected_divide_binary16[i];	
	EXPECT_EQ(extlogtable.divide(res.arg1, res.arg2), res.result);
    }

}


TEST(test_extended_log_table, binary8randCheck)
{
    fifi::extended_log_table<fifi::binary8> extlogtable;

    int elements = 100;

    for(int i = 0; i < elements; ++i)
    {
        fifi::binary8::value_type v = rand() % fifi::binary8::order;

        if(v == 0)
            ++v;

        EXPECT_EQ( extlogtable.multiply(v, extlogtable.divide(1, v)), 1);
    }

}
