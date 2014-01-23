// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/optimal_prime_arithmetic.hpp>

#include <fifi/prime2325.hpp>

#include "expected_results.hpp"

TEST(test_optimal_prime_arithmetic, multiply)
{
    check_results_multiply<fifi::optimal_prime_arithmetic<fifi::prime2325> >();
}

TEST(test_optimal_prime_arithmetic, divide2325)
{
    check_results_divide<fifi::optimal_prime_arithmetic<fifi::prime2325> >();
}

TEST(test_optimal_prime_arithmetic, add2325)
{
    check_results_add<fifi::optimal_prime_arithmetic<fifi::prime2325> >();
}

TEST(test_optimal_prime_arithmetic, subtract2325)
{
    check_results_subtract<fifi::optimal_prime_arithmetic<fifi::prime2325> >();
}

TEST(test_optimal_prime_arithmetic, invert2325)
{
    check_results_invert<fifi::optimal_prime_arithmetic<fifi::prime2325> >();
}

TEST(test_optimal_prime_arithmetic, prime2325randCheck)
{
    fifi::optimal_prime_arithmetic<fifi::prime2325> optimal;

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
