// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/prime2325.hpp>
#include <fifi/optimal_prime_arithmetic.hpp>
#include <fifi/final.hpp>
#include "expected_results.hpp"

namespace fifi
{
    namespace {
        template<class Field>
        struct dummy_stack : public
        optimal_prime_arithmetic<
        final<Field> >
        { };
    }
}

TEST(TestOptimalPrimeArithmetic, multiply)
{
    {
        SCOPED_TRACE("prime2325");
        check_results_multiply<fifi::dummy_stack<fifi::prime2325> >();
    }
}

TEST(TestOptimalPrimeArithmetic, divide)
{
    {
        SCOPED_TRACE("prime2325");
        check_results_divide<fifi::dummy_stack<fifi::prime2325> >();
    }
}

TEST(TestOptimalPrimeArithmetic, invert)
{
    {
        SCOPED_TRACE("prime2325");
        check_results_invert<fifi::dummy_stack<fifi::prime2325> >();
    }
}

TEST(TestOptimalPrimeArithmetic, random)
{
    {
        SCOPED_TRACE("prime2325");
        check_random_default<fifi::dummy_stack<fifi::prime2325> >();
    }
}
