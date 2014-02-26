// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/final.hpp>
#include <fifi/full_table_arithmetic.hpp>
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
            full_table_arithmetic<
            helper_fall_through<Field> >
        { };

        template<class Field>
        struct dummy_stack : public
            full_table_arithmetic<
            simple_online_arithmetic<
            polynomial_degree<
            final<Field> > > >
        { };
    }
}

TEST(TestFullTableArithmetic, fall_through)
{
    fifi::fall_through_result expected;
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
}

TEST(TestFullTableArithmetic, multiply)
{
    {
        SCOPED_TRACE("binary4");
        check_results_multiply<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_multiply<fifi::dummy_stack<fifi::binary8> >();
    }
}

TEST(TestFullTableArithmetic, divide)
{
    {
        SCOPED_TRACE("binary4");
        check_results_divide<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_divide<fifi::dummy_stack<fifi::binary8> >();
    }
}

TEST(TestFullTableArithmetic, invert)
{
    {
        SCOPED_TRACE("binary4");
        check_results_invert<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_invert<fifi::dummy_stack<fifi::binary8> >();
    }
}

TEST(TestFullTableArithmetic, random)
{
    {
        SCOPED_TRACE("binary4");
        check_random_default<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_random_default<fifi::dummy_stack<fifi::binary8> >();
    }
}
