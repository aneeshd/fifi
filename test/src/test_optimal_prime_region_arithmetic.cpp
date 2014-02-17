// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/final.hpp>
#include <fifi/optimal_prime_arithmetic.hpp>
#include <fifi/optimal_prime_region_arithmetic.hpp>
#include <fifi/packed_arithmetic.hpp>
#include <fifi/prime2325.hpp>
#include <fifi/region_arithmetic.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"
#include "helper_catch_all.hpp"
#include "helper_region_fall_through.hpp"

namespace fifi
{
    namespace
    {
        template<class Field>
        struct dummy_stack_fall_through : public
        optimal_prime_region_arithmetic<Field,
        helper_region_fall_through<Field,
        optimal_prime_arithmetic<
        helper_catch_all<Field> > > >
        { };
    }

    namespace
    {
        template<class Field>
        struct dummy_stack : public
        optimal_prime_region_arithmetic<Field,
        region_arithmetic<
        packed_arithmetic<
        optimal_prime_arithmetic<
        final<Field> > > > >
        { };
    }
}

TEST(TestOptimalPrimeRegionArithmetic, fall_through)
{
    fifi::region_fall_through_result expected;
    expected.add = false;
    expected.subtract = false;
    fifi::helper_region_fall_through_test<fifi::prime2325,
    fifi::dummy_stack_fall_through<fifi::prime2325> >(expected);
}

TEST(TestOptimalPrimeRegionArithmetic, add)
{
    check_results_region_add<fifi::dummy_stack<fifi::prime2325> >();
}

TEST(TestOptimalPrimeRegionArithmetic, subtract)
{
    check_results_region_subtract<fifi::dummy_stack<fifi::prime2325> >();
}
