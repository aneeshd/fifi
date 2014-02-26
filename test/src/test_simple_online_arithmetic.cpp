// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/final.hpp>
#include <fifi/polynomial_degree.hpp>
#include <fifi/simple_online_arithmetic.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"
#include "helper_catch_all.hpp"
#include "helper_fall_through.hpp"

namespace fifi
{
    // Put dummy layers and tests classes in an anonymous namespace
    // to avoid violations of ODF (one-definition-rule) in other
    // translation units
    namespace
    {
        template<class Field>
        struct dummy_stack_fall_through : public
            simple_online_arithmetic<
            polynomial_degree<
            helper_fall_through<Field> > >
        { };

        template<class Field>
        struct dummy_stack : public
            simple_online_arithmetic<
            polynomial_degree<
            final<Field> > >
        { };
    }
}

TEST(TestSimpleOnlineArithmetic, fall_through)
{
    fifi::fall_through_result expected;
    expected.add = false;
    expected.subtract = false;
    expected.multiply = false;
    expected.divide = false;
    expected.invert = false;
    {
        SCOPED_TRACE("binary4");
        fifi::helper_fall_through_test<fifi::binary4,
        fifi::dummy_stack_fall_through<fifi::binary4> >(expected);
    }
    {
        SCOPED_TRACE("binary8");
        fifi::helper_fall_through_test<fifi::binary8,
        fifi::dummy_stack_fall_through<fifi::binary8> >(expected);
    }
    {
        SCOPED_TRACE("binary16");
        fifi::helper_fall_through_test<fifi::binary16,
        fifi::dummy_stack_fall_through<fifi::binary16> >(expected);
    }
}

TEST(TestSimpleOnlineArithmetic, add)
{
    {
        SCOPED_TRACE("binary");
        check_results_add<fifi::dummy_stack<fifi::binary> >();
    }
    {
        SCOPED_TRACE("binary4");
        check_results_add<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_add<fifi::dummy_stack<fifi::binary8> >();
    }
    {
        SCOPED_TRACE("binary16");
        check_results_add<fifi::dummy_stack<fifi::binary16> >();
    }
}

TEST(TestSimpleOnlineArithmetic, subtract)
{
    {
        SCOPED_TRACE("binary");
        check_results_subtract<fifi::dummy_stack<fifi::binary> >();
    }
    {
        SCOPED_TRACE("binary4");
        check_results_subtract<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_subtract<fifi::dummy_stack<fifi::binary8> >();
    }
    {
        SCOPED_TRACE("binary16");
        check_results_subtract<fifi::dummy_stack<fifi::binary16> >();
    }
}

TEST(TestSimpleOnlineArithmetic, multiply)
{
    {
        SCOPED_TRACE("binary4");
        check_results_multiply<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_multiply<fifi::dummy_stack<fifi::binary8> >();
    }
    {
        SCOPED_TRACE("binary16");
        check_results_multiply<fifi::dummy_stack<fifi::binary16> >();
    }
}

TEST(TestSimpleOnlineArithmetic, divide)
{
    {
        SCOPED_TRACE("binary4");
        check_results_divide<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_divide<fifi::dummy_stack<fifi::binary8> >();
    }
    {
        SCOPED_TRACE("binary16");
        check_results_divide<fifi::dummy_stack<fifi::binary16> >();
    }
}

TEST(TestSimpleOnlineArithmetic, invert)
{
    {
        SCOPED_TRACE("binary4");
        check_results_invert<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_invert<fifi::dummy_stack<fifi::binary8> >();
    }
    {
        SCOPED_TRACE("binary16");
        check_results_invert<fifi::dummy_stack<fifi::binary16> >();
    }
}

TEST(TestSimpleOnlineArithmetic, random)
{
    {
        SCOPED_TRACE("binary4");
        check_random_default<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_random_default<fifi::dummy_stack<fifi::binary8> >();
    }
    {
        SCOPED_TRACE("binary16");
        check_random_default<fifi::dummy_stack<fifi::binary16> >();
    }
}
