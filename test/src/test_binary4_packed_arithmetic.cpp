// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/binary4_packed_arithmetic.hpp>
#include "helper_fall_through.hpp"
#include "helper_catch_all.hpp"

namespace fifi
{
    namespace {
        template<class Field>
        struct helper_fall_through_stack : public
        binary4_packed_arithmetic<Field,
        helper_fall_through<Field,
        helper_catch_all<Field> > >
        { };
    }
}

TEST(TestBinary4PackedArithmetic, api)
{
    fifi::helper_fall_through_test<fifi::binary,
        fifi::helper_fall_through_stack<fifi::binary> >(true);
    fifi::helper_fall_through_test<fifi::binary4,
        fifi::helper_fall_through_stack<fifi::binary4> >(false);
    fifi::helper_fall_through_test<fifi::binary8,
        fifi::helper_fall_through_stack<fifi::binary8> >(true);
    fifi::helper_fall_through_test<fifi::binary16,
        fifi::helper_fall_through_stack<fifi::binary16> >(true);
    fifi::helper_fall_through_test<fifi::prime2325,
        fifi::helper_fall_through_stack<fifi::prime2325> >(true);
}
