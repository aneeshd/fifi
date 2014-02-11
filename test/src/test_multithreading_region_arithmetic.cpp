// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary4.hpp>
#include <fifi/binary4_packed_arithmetic.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary_packed_arithmetic.hpp>
#include <fifi/binary_simple_online_arithmetic.hpp>
#include <fifi/final.hpp>
#include <fifi/multithreading_region_arithmetic.hpp>
#include <fifi/multithreading_region_info.hpp>
#include <fifi/optimal_prime_arithmetic.hpp>
#include <fifi/packed_arithmetic.hpp>
#include <fifi/polynomial_degree.hpp>
#include <fifi/region_arithmetic.hpp>
#include <fifi/region_info.hpp>
#include <fifi/simple_online_arithmetic.hpp>

#include <gtest/gtest.h>

#include "helper_test_region_arithmetic.hpp"
#include "helper_catch_all.hpp"
#include "helper_region_fall_through.hpp"

namespace fifi
{
    namespace
    {
        template<class Field>
        struct dummy_stack_fall_through : public
        multithreading_region_arithmetic<
        multithreading_region_info<
        helper_region_fall_through<Field,
        region_info<Field,
        helper_catch_all<Field> > > > >
        { };

        template<class Field>
        struct dummy_stack : public
        multithreading_region_arithmetic<
        multithreading_region_info<
        region_arithmetic<
        region_info<Field,
        binary4_packed_arithmetic<Field,
        binary_packed_arithmetic<Field,
        packed_arithmetic<
        binary_simple_online_arithmetic<Field,
        simple_online_arithmetic<
        polynomial_degree<
        final<Field> > > > > > > > > > >
        { };

        template<class Field>
        struct optimal_dummy_stack : public
        multithreading_region_arithmetic<
        multithreading_region_info<
        region_arithmetic<
        region_info<Field,
        packed_arithmetic<
        optimal_prime_arithmetic<
        final<Field> > > > > > >
        { };

    }
}

TEST(TestMultithreadingRegionArithmetic, fall_through)
{
    fifi::region_fall_through_result expected;
    {
        SCOPED_TRACE("binary");
        fifi::helper_region_fall_through_test<fifi::binary,
        fifi::dummy_stack_fall_through<fifi::binary> >(expected);
    }
    {
        SCOPED_TRACE("binary4");
        fifi::helper_region_fall_through_test<fifi::binary4,
        fifi::dummy_stack_fall_through<fifi::binary4> >(expected);
    }
    {
        SCOPED_TRACE("binary8");
        fifi::helper_region_fall_through_test<fifi::binary8,
        fifi::dummy_stack_fall_through<fifi::binary8> >(expected);
    }
    {
        SCOPED_TRACE("binary16");
        fifi::helper_region_fall_through_test<fifi::binary16,
        fifi::dummy_stack_fall_through<fifi::binary16> >(expected);
    }
    {
        SCOPED_TRACE("prime2325");
        fifi::helper_region_fall_through_test<fifi::prime2325,
        fifi::dummy_stack_fall_through<fifi::prime2325> >(expected);
    }
}

TEST(TestMultithreadingRegionArithmetic, add)
{
    fifi::check_region_add<fifi::dummy_stack>();
}
