// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/binary.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>
#include <fifi/simple_online_arithmetic.hpp>
#include <fifi/polynomial_degree.hpp>
#include <fifi/final.hpp>
#include "helper_catch_all.hpp"
#include "helper_fall_through.hpp"
#include "expected_results.hpp"

namespace fifi
{
    namespace {
        template<class Field>
        struct dummy_stack_fall_through : public
        simple_online_arithmetic<
        polynomial_degree<
        helper_fall_through<Field,
        helper_catch_all<Field> > > >
        { };
    }

    namespace {
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
    {
        SCOPED_TRACE("binary4");
        fifi::helper_fall_through_test<fifi::binary4,
        fifi::dummy_stack_fall_through<fifi::binary4> >(
            false, false, false, false, false);
    }
    {
        SCOPED_TRACE("binary8");
        fifi::helper_fall_through_test<fifi::binary8,
        fifi::dummy_stack_fall_through<fifi::binary8> >(
            false, false, false, false, false);
    }
    {
        SCOPED_TRACE("binary16");
        fifi::helper_fall_through_test<fifi::binary16,
        fifi::dummy_stack_fall_through<fifi::binary16> >(
            false, false, false, false, false);
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

