// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary_simple_online_arithmetic.hpp>
#include <fifi/prime2325.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"
#include "helper_catch_all.hpp"
#include "helper_fall_through.hpp"

namespace fifi
{
    namespace {
        template<class Field>
        struct dummy_stack : public
        binary_simple_online_arithmetic<Field,
        helper_fall_through<Field,
        helper_catch_all<Field> > >
        { };
    }
}

TEST(TestBinarySimpleOnlineArithmetic, fall_through)
{
    {
        SCOPED_TRACE("binary");
        fifi::fall_through_result expected;
        expected.multiply = false;
        expected.divide = false;
        expected.invert = false;
        fifi::helper_fall_through_test<fifi::binary,
        fifi::dummy_stack<fifi::binary> >(expected);
    }
    {
        SCOPED_TRACE("binary4");
        fifi::fall_through_result expected;
        fifi::helper_fall_through_test<fifi::binary4,
        fifi::dummy_stack<fifi::binary4> >(expected);
    }
    {
        SCOPED_TRACE("binary8");
        fifi::fall_through_result expected;
        fifi::helper_fall_through_test<fifi::binary8,
        fifi::dummy_stack<fifi::binary8> >(expected);
    }
    {
        SCOPED_TRACE("binary16");
        fifi::fall_through_result expected;
        fifi::helper_fall_through_test<fifi::binary16,
        fifi::dummy_stack<fifi::binary16> >(expected);
    }
    {
        SCOPED_TRACE("prime2325");
        fifi::fall_through_result expected;
        fifi::helper_fall_through_test<fifi::prime2325,
        fifi::dummy_stack<fifi::prime2325> >(expected);
    }
}

TEST(TestBinarySimpleOnlineArithmetic, multiply)
{
    check_results_multiply<fifi::dummy_stack<fifi::binary> >();
}

TEST(TestBinarySimpleOnlineArithmetic, divide)
{
    check_results_divide<fifi::dummy_stack<fifi::binary>>();
}

TEST(TestBinarySimpleOnlineArithmetic, invert)
{
    check_results_invert<fifi::dummy_stack<fifi::binary>>();
}

TEST(TestBinarySimpleOnlineArithmetic, random)
{
    check_random_default<fifi::dummy_stack<fifi::binary>>();
}
