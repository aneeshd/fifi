// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/final.hpp>
#include <fifi/optimal_prime_arithmetic.hpp>
#include <fifi/prime2325.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"

namespace fifi
{
    namespace
    {
        template<class Field>
        struct dummy_stack : public
        optimal_prime_arithmetic<
        final<Field> >
        { };
    }
}

TEST(test_optimal_prime_arithmetic, multiply)
{
    check_results_multiply<fifi::dummy_stack<fifi::prime2325> >();
}

TEST(test_optimal_prime_arithmetic, divide)
{
    check_results_divide<fifi::dummy_stack<fifi::prime2325> >();
}

TEST(test_optimal_prime_arithmetic, invert)
{

    check_results_invert<fifi::dummy_stack<fifi::prime2325> >();
}

TEST(test_optimal_prime_arithmetic, random)
{
    check_random_default<fifi::dummy_stack<fifi::prime2325> >();
}
