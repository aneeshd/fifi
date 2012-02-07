// Copyright Steinwurf APS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE_1_0.txt or
// http://www.steinwurf.dk/licensing

#include <gtest/gtest.h>

#include <fifi/full_table.h>
#include <fifi/field_types.h>

#include "expected_results.h"

TEST(test_full_table, binary8multiply)
{

    fifi::full_table<fifi::binary8> fulltable;

    uint32_t size = expected_multiply_binary8_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::binary8> res = expected_multiply_binary8[i];
	EXPECT_EQ(fulltable.multiply(res.arg1, res.arg2), res.result);
    }

}


TEST(test_full_table, binary8divide)
{
    fifi::full_table<fifi::binary8> fulltable;

    uint32_t size = expected_divide_binary8_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::binary8> res = expected_divide_binary8[i];	
	EXPECT_EQ(fulltable.divide(res.arg1, res.arg2), res.result);
    }
    
}


TEST(test_full_table, binary8invert)
{

    fifi::full_table<fifi::binary8> fulltable;

    uint32_t size = expected_invert_binary8_size;
    
    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_1<fifi::binary8> res = expected_invert_binary8[i];
	EXPECT_EQ(fulltable.invert(res.arg1), res.result);
    }

}


TEST(test_full_table, binary8randCheck)
{
    fifi::full_table<fifi::binary8> fulltable;

    int elements = 100;

    for(int i = 0; i < elements; ++i)
    {
        fifi::binary8::value_type v = rand() % fifi::binary8::order;

        if(v == 0)
            ++v;

        EXPECT_EQ( fulltable.multiply(v, fulltable.divide(1, v)), 1);
    }
}
