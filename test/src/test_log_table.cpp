// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/log_table.h>
#include <fifi/field_types.h>

#include "expected_results.h"

TEST(test_log_table,binary8multiply)
{

    fifi::log_table<fifi::binary8> logtable;

    uint32_t size = expected_multiply_binary8_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::binary8> res = expected_multiply_binary8[i];
	EXPECT_EQ(logtable.multiply(res.arg1, res.arg2), res.result);
    }

}


TEST(test_log_table,binary8invert)
{

    fifi::log_table<fifi::binary8> logtable;

    uint32_t size = expected_invert_binary8_size;
    
    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_1<fifi::binary8> res = expected_invert_binary8[i];
	EXPECT_EQ(logtable.invert(res.arg1), res.result);
    }
    
}


TEST(test_log_table,binary8divide)
{
    fifi::log_table<fifi::binary8> logtable;

    uint32_t size = expected_divide_binary8_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::binary8> res = expected_divide_binary8[i];	
	EXPECT_EQ(logtable.divide(res.arg1, res.arg2), res.result);
    }

}


TEST(test_log_table,binary16multiply)
{

    fifi::log_table<fifi::binary16> logtable;

    uint32_t size = expected_multiply_binary16_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::binary16> res = expected_multiply_binary16[i];
	EXPECT_EQ(logtable.multiply(res.arg1, res.arg2), res.result);
    }

}


TEST(test_log_table,binary16invert)
{

    fifi::log_table<fifi::binary16> logtable;

    uint32_t size = expected_invert_binary16_size;
    
    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_1<fifi::binary16> res = expected_invert_binary16[i];
	EXPECT_EQ(logtable.invert(res.arg1), res.result);
    }
    
}


TEST(test_log_table,binary16divide)
{
    fifi::log_table<fifi::binary16> logtable;

    uint32_t size = expected_divide_binary16_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::binary16> res = expected_divide_binary16[i];	
	EXPECT_EQ(logtable.divide(res.arg1, res.arg2), res.result);
    }

}



TEST(test_log_table,binary8randCheck)
{
    fifi::log_table<fifi::binary8> logtable;

    int elements = 100;

    for(int i = 0; i < elements; ++i)
    {
        fifi::binary8::value_type v = rand() % fifi::binary8::order;

        if(v == 0)
            ++v;

        EXPECT_EQ( logtable.multiply(v, logtable.divide(1, v)), 1);
    }

}
