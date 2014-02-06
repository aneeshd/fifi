// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary_packed_arithmetic.hpp>
#include <fifi/binary_region_arithmetic.hpp>
#include <fifi/binary_simple_online_arithmetic.hpp>
#include <fifi/final.hpp>
#include <fifi/packed_arithmetic.hpp>
#include <fifi/polynomial_degree.hpp>
#include <fifi/prime2325.hpp>
#include <fifi/region_arithmetic.hpp>
#include <fifi/region_info.hpp>
#include <fifi/simple_online_arithmetic.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"
#include "helper_catch_all.hpp"
#include "helper_region_fall_through.hpp"
/*
namespace fifi
{
    namespace {
        template<class Field>
        struct dummy_stack_fall_through : public
        binary_region_arithmetic<Field,
        helper_region_fall_through<Field,
        region_info<Field,
        helper_catch_all<Field> > > >
        { };
    }

    namespace {
        template<class Field>
        struct dummy_stack : public
        binary_region_arithmetic<Field,
        region_arithmetic<
        region_info<Field,
        binary_packed_arithmetic<Field,
        packed_arithmetic<
        binary_simple_online_arithmetic<Field,
        simple_online_arithmetic<
        polynomial_degree<
        final<Field> > > > > > > > >
        { };
    }
}

TEST(TestBinaryRegionArithmetic, fall_through)
{
    {
        SCOPED_TRACE("binary");
        fifi::helper_region_fall_through_test<fifi::binary,
        fifi::dummy_stack_fall_through<fifi::binary> >(
            true, true, true, true, false, false, false);
    }
    {
        SCOPED_TRACE("binary4");
        fifi::helper_region_fall_through_test<fifi::binary4,
        fifi::dummy_stack_fall_through<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        fifi::helper_region_fall_through_test<fifi::binary8,
        fifi::dummy_stack_fall_through<fifi::binary8> >();
    }
    {
        SCOPED_TRACE("binary16");
        fifi::helper_region_fall_through_test<fifi::binary16,
        fifi::dummy_stack_fall_through<fifi::binary16> >();
    }
    {
        SCOPED_TRACE("prime2325");
        fifi::helper_region_fall_through_test<fifi::prime2325,
        fifi::dummy_stack_fall_through<fifi::prime2325> >();
    }
}


TEST(TestBinaryRegionArithmetic, multiply_constant)
{
    check_results_region_multiply_constant<fifi::dummy_stack<fifi::binary> >();
}

TEST(TestBinaryRegionArithmetic, multiply_add)
{
    check_results_region_multiply_add<fifi::dummy_stack<fifi::binary> >();
}

TEST(TestBinaryRegionArithmetic, multiply_subtract)
{
    check_results_region_multiply_subtract<fifi::dummy_stack<fifi::binary> >();
}
*/
