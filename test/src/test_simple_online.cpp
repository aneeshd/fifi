// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/simple_online.h>
#include <fifi/field_types.h>

#include "expected_results.h"

TEST(test_simple_online, binary8fieldDegree)
{
    EXPECT_EQ( fifi::find_degree<fifi::binary8>(2), 1);
    EXPECT_EQ( fifi::find_degree<fifi::binary8>(17), 4);
}


TEST(test_simple_online, binary8multiply)
{

    fifi::simple_online<fifi::binary8> simple;

    uint32_t size = expected_multiply_binary8_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::binary8> res = expected_multiply_binary8[i];
	EXPECT_EQ(simple.multiply(res.arg1, res.arg2), res.result);
    }

}


TEST(test_simple_online, binary8invert)
{

    fifi::simple_online<fifi::binary8> simple;

    uint32_t size = expected_invert_binary8_size;
    
    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_1<fifi::binary8> res = expected_invert_binary8[i];
	EXPECT_EQ(simple.invert(res.arg1), res.result);
    }

}


TEST(test_simple_online, binary8divide)
{

    fifi::simple_online<fifi::binary8> simple;

    uint32_t size = expected_divide_binary8_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::binary8> res = expected_divide_binary8[i];	
	EXPECT_EQ(simple.divide(res.arg1, res.arg2), res.result);
    }

}


TEST(test_simple_online, binary16multiply)
{

    fifi::simple_online<fifi::binary16> simple;

    uint32_t size = expected_multiply_binary16_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::binary16> res = expected_multiply_binary16[i];
	EXPECT_EQ(simple.multiply(res.arg1, res.arg2), res.result);
    }

}


TEST(test_simple_online, binary16invert)
{

    fifi::simple_online<fifi::binary16> simple;

    uint32_t size = expected_invert_binary16_size;
    
    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_1<fifi::binary16> res = expected_invert_binary16[i];
	EXPECT_EQ(simple.invert(res.arg1), res.result);
    }

}


TEST(test_simple_online, binary16divide)
{

    fifi::simple_online<fifi::binary16> simple;

    uint32_t size = expected_divide_binary16_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::binary16> res = expected_divide_binary16[i];	
	EXPECT_EQ(simple.divide(res.arg1, res.arg2), res.result);
    }

}


TEST(test_simple_online, binary8randCheck)
{

    fifi::simple_online<fifi::binary8> simple;


    int elements = 100;

    for(int i = 0; i < elements; ++i)
    {
        fifi::binary8::value_type v = rand() % fifi::binary8::order;

        if(v == 0)
            ++v;

        EXPECT_EQ( simple.multiply(v, simple.invert(v)), 1);
        EXPECT_EQ( simple.multiply(v, simple.divide(1, v)), 1);
    }


}
