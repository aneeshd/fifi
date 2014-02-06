// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/final.hpp>
#include <fifi/log_table_arithmetic.hpp>
#include <fifi/simple_online_arithmetic.hpp>
#include <fifi/sum_modulo.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"
#include "helper_catch_all.hpp"
#include "helper_fall_through.hpp"

namespace fifi
{
    namespace {
        template<class Field>
        struct dummy_stack_fall_through : public
        log_table_arithmetic<Field,
        helper_fall_through<Field,
        sum_modulo<
        helper_catch_all<Field> > > >
        { };
    }

    namespace {
        template<class Field>
        struct dummy_stack : public
        log_table_arithmetic<Field,
        simple_online_arithmetic<
        sum_modulo<
        final<Field> > > >
        { };
    }
}

TEST(TestLogTableArithmetic, fall_through)
{
    {
        SCOPED_TRACE("binary4");
        fifi::helper_fall_through_test<fifi::binary4,
        fifi::dummy_stack_fall_through<fifi::binary4> >(true, true, false, false, false);
    }
    {
        SCOPED_TRACE("binary8");
        fifi::helper_fall_through_test<fifi::binary8,
        fifi::dummy_stack_fall_through<fifi::binary8> >(true, true, false, false, false);
    }
    {
        SCOPED_TRACE("binary16");
        fifi::helper_fall_through_test<fifi::binary16,
        fifi::dummy_stack_fall_through<fifi::binary16> >(true, true, false, false, false);
    }
}

TEST(TestLogTableArithmetic, multiply)
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

TEST(TestLogTableArithmetic, divide)
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

TEST(TestLogTableArithmetic, invert)
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

TEST(TestLogTableArithmetic, random)
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
