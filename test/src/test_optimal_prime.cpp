// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/optimal_prime.h>
#include <fifi/field_types.h>

#include "expected_results.h"

TEST(test_optimal_prime, multiply)
{
    fifi::optimal_prime<fifi::prime2325> optimal;

    uint32_t size = expected_multiply_prime2325_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::prime2325> res = expected_multiply_prime2325[i];
	EXPECT_EQ(optimal.multiply(res.arg1, res.arg2), res.result);
    }

}

TEST(test_optimal_prime, divide)
{
    fifi::optimal_prime<fifi::prime2325> optimal;

    uint32_t size = expected_divide_prime2325_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::prime2325> res = expected_divide_prime2325[i];
	EXPECT_EQ(optimal.divide(res.arg1, res.arg2), res.result);
    }

}


TEST(test_optimal_prime, add)
{
    fifi::optimal_prime<fifi::prime2325> optimal;

    uint32_t size = expected_add_prime2325_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::prime2325> res = expected_add_prime2325[i];
	EXPECT_EQ(optimal.add(res.arg1, res.arg2), res.result);
    }

}

TEST(test_optimal_prime, subtract)
{
    fifi::optimal_prime<fifi::prime2325> optimal;

    uint32_t size = expected_subtract_prime2325_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_2<fifi::prime2325> res = expected_subtract_prime2325[i];
	EXPECT_EQ(optimal.subtract(res.arg1, res.arg2), res.result);
    }

}


TEST(test_optimal_prime, invert)
{
    fifi::optimal_prime<fifi::prime2325> optimal;

    uint32_t size = expected_invert_prime2325_size;

    for(uint32_t i = 0; i < size; ++i)
    {
	expected_result_1<fifi::prime2325> res = expected_invert_prime2325[i];
	EXPECT_EQ(optimal.invert(res.arg1), res.result);
    }

}


TEST(test_optimal_prime, prime2325randCheck)
{
    fifi::optimal_prime<fifi::prime2325> optimal;

    int elements = 10000;

    for(int i = 0; i < elements; ++i)
    {
        fifi::prime2325::value_type v = rand() % fifi::prime2325::order;

        if(v == 0)
            ++v;

        EXPECT_EQ( optimal.multiply(v, optimal.invert(v)), 1U);
        EXPECT_EQ( optimal.multiply(v, optimal.divide(1, v)), 1U);
    }
}





