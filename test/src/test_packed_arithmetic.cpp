// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/packed_arithmetic.hpp>
#include <fifi/prime2325.hpp>

#include "helper_catch_all.hpp"
#include "helper_packed_fall_through.hpp"

namespace fifi
{
    namespace
    {
        template<class Field>
        struct dummy_stack : public
        packed_arithmetic<
        helper_packed_fall_through<Field,
        helper_catch_all<Field> > >
        { };
    }
}

TEST(TestPackedArithmetic, fall_through)
{
    fifi::fall_through_packed_result expected;
    expected.add = false;
    expected.subtract = false;
    expected.multiply = false;
    expected.divide = false;
    expected.invert = false;

    {
        SCOPED_TRACE("binary");
        fifi::helper_packed_fall_through_test<fifi::binary,
        fifi::dummy_stack<fifi::binary> >(expected);
    }
    {
        SCOPED_TRACE("binary4");
        fifi::helper_packed_fall_through_test<fifi::binary4,
        fifi::dummy_stack<fifi::binary4> >(expected);
    }
    {
        SCOPED_TRACE("binary8");
        fifi::helper_packed_fall_through_test<fifi::binary8,
        fifi::dummy_stack<fifi::binary8> >(expected);
    }
    {
        SCOPED_TRACE("binary16");
        fifi::helper_packed_fall_through_test<fifi::binary16,
        fifi::dummy_stack<fifi::binary16> >(expected);
    }
    {
        SCOPED_TRACE("prime2325");
        fifi::helper_packed_fall_through_test<fifi::prime2325,
        fifi::dummy_stack<fifi::prime2325> >(expected);
    }
}
