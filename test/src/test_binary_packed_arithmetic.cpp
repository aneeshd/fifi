// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary_packed_arithmetic.hpp>
#include <fifi/final.hpp>
#include <fifi/packed_arithmetic.hpp>
#include <fifi/prime2325.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"
#include "helper_packed_fall_through.hpp"

namespace fifi
{
    namespace {
        template<class Field>
        struct dummy_stack : public
        binary_packed_arithmetic<Field,
        helper_packed_fall_through<Field,
        packed_arithmetic<
        final<Field> > > >
        { };
    }
}

TEST(TestBinaryPackedArithmetic, fall_through)
{
    {
        SCOPED_TRACE("binary");
        fifi::helper_packed_fall_through_test<fifi::binary,
        fifi::dummy_stack<fifi::binary> >(false, false, false, false, false);
    }
    {
        SCOPED_TRACE("binary4");
        fifi::helper_packed_fall_through_test<fifi::binary4,
        fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        fifi::helper_packed_fall_through_test<fifi::binary8,
        fifi::dummy_stack<fifi::binary8> >();
    }
    {
        SCOPED_TRACE("binary16");
        fifi::helper_packed_fall_through_test<fifi::binary16,
        fifi::dummy_stack<fifi::binary16> >();
    }
    {
        SCOPED_TRACE("prime2325");
        fifi::helper_packed_fall_through_test<fifi::prime2325,
        fifi::dummy_stack<fifi::prime2325> >();
    }
}

TEST(TestBinaryPackedArithmetic, add)
{
    check_results_packed_add<fifi::dummy_stack<fifi::binary>>();
}

TEST(TestBinaryPackedArithmetic, subtract)
{
    check_results_packed_subtract<fifi::dummy_stack<fifi::binary>>();
}

TEST(TestBinaryPackedArithmetic, multiply)
{
    check_results_packed_multiply<fifi::dummy_stack<fifi::binary> >();
}

TEST(TestBinaryPackedArithmetic, divide)
{
    check_results_packed_divide<fifi::dummy_stack<fifi::binary>>();
}

TEST(TestBinaryPackedArithmetic, invert)
{
    check_results_packed_invert<fifi::dummy_stack<fifi::binary>>();
}
