// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/prime2325.hpp>
#include <fifi/region_arithmetic.hpp>
#include <fifi/region_info.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"
#include "helper_catch_all.hpp"
#include "helper_region_fall_through.hpp"

namespace fifi
{
    namespace {
        template<class Field>
        struct dummy_stack : public
        region_arithmetic<
        region_info<Field,
        helper_region_fall_through<Field,
        helper_catch_all<Field> > > >
        { };
    }
}

TEST(TestRegionArithmetic, fall_through)
{
    {
        SCOPED_TRACE("binary");
        fifi::helper_region_fall_through_test<fifi::binary,
        fifi::dummy_stack<fifi::binary> >(
            false, false, false, false, false, false, false);
    }
    {
        SCOPED_TRACE("binary4");
        fifi::helper_region_fall_through_test<fifi::binary4,
        fifi::dummy_stack<fifi::binary4> >(
            false, false, false, false, false, false, false);
    }
    {
        SCOPED_TRACE("binary8");
        fifi::helper_region_fall_through_test<fifi::binary8,
        fifi::dummy_stack<fifi::binary8> >(
            false, false, false, false, false, false, false);
    }
    {
        SCOPED_TRACE("binary16");
        fifi::helper_region_fall_through_test<fifi::binary16,
        fifi::dummy_stack<fifi::binary16> >(
            false, false, false, false, false, false, false);
    }
    {
        SCOPED_TRACE("prime2325");
        fifi::helper_region_fall_through_test<fifi::prime2325,
        fifi::dummy_stack<fifi::prime2325> >(
            false, false, false, false, false, false, false);
    }
}
