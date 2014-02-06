// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary8_region_arithmetic_full_table.hpp>
#include <fifi/final.hpp>
#include <fifi/full_table_arithmetic.hpp>
#include <fifi/packed_arithmetic.hpp>
#include <fifi/polynomial_degree.hpp>
#include <fifi/region_arithmetic.hpp>
#include <fifi/region_info.hpp>
#include <fifi/simple_online_arithmetic.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"
#include "helper_catch_all.hpp"
#include "helper_region_fall_through.hpp"

namespace fifi
{
    namespace {
        template<class Field>
        struct dummy_stack_fall_through : public
        binary8_region_arithmetic_full_table<Field,
        helper_region_fall_through<Field,
        region_info<Field,
        full_table_arithmetic<Field,
        simple_online_arithmetic<
        polynomial_degree<
        helper_catch_all<Field> > > > > > >
        { };
    }

    namespace {
        template<class Field>
        struct dummy_stack : public
        binary8_region_arithmetic_full_table<Field,
        region_arithmetic<
        region_info<Field,
        packed_arithmetic<
        full_table_arithmetic<Field,
        simple_online_arithmetic<
        polynomial_degree<
        final<Field> > > > > > > >
        { };
    }
}

TEST(TestBinary8RegionArithmeticFullTable, fall_through)
{
    {
        SCOPED_TRACE("binary4");
        fifi::helper_region_fall_through_test<fifi::binary4,
        fifi::dummy_stack_fall_through<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        fifi::helper_region_fall_through_test<fifi::binary8,
        fifi::dummy_stack_fall_through<fifi::binary8> >(
            true, true, true, true, true, false, false);
    }
}

TEST(TestBinary8RegionArithmeticFullTable, init)
{
    fifi::dummy_stack<fifi::binary8> stack;
    (void) stack;
}

TEST(TestBinary8RegionArithmeticFullTable, multiply_add)
{
    check_results_region_multiply_add<fifi::dummy_stack<fifi::binary8> >();
}
/*
TEST(TestBinary8RegionArithmeticFullTable, multiply_subtract)
{
    check_results_region_multiply_subtract<fifi::dummy_stack<fifi::binary8> >();
}
*/
