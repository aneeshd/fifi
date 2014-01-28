// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/binary4_packed_arithmetic.hpp>
#include "helper_packed_fall_through.hpp"
#include "helper_catch_all.hpp"

#include <fifi/binary.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>
#include <fifi/prime2325.hpp>

namespace fifi
{
    namespace {
        template<class Field>
        struct dummy_stack : public
        binary4_packed_arithmetic<Field,
        helper_packed_fall_through<Field,
        helper_catch_all<Field> > >
        { };
    }
}

TEST(TestBinary4PackedArithmetic, fall_through)
{
    fifi::helper_packed_fall_through_test<fifi::binary,
        fifi::dummy_stack<fifi::binary> >();
    fifi::helper_packed_fall_through_test<fifi::binary4,
        fifi::dummy_stack<fifi::binary4> >(false, false, false, false, false);
    fifi::helper_packed_fall_through_test<fifi::binary8,
        fifi::dummy_stack<fifi::binary8> >();
    fifi::helper_packed_fall_through_test<fifi::binary16,
        fifi::dummy_stack<fifi::binary16> >();
    fifi::helper_packed_fall_through_test<fifi::prime2325,
        fifi::dummy_stack<fifi::prime2325> >();
}
