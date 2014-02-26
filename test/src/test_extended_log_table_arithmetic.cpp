// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/extended_log_table_arithmetic.hpp>
#include <fifi/final.hpp>
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
            extended_log_table_arithmetic<
            helper_fall_through<Field> >
        { };

        template<class Field>
        struct dummy_stack : public
            extended_log_table_arithmetic<
            simple_online_arithmetic<
            final<Field> > >
        { };
    }
}

template<class Field>
inline void helper_fall_through()
{
    typedef Field field_type;
    typedef typename field_type::value_type value_type;
    typedef fifi::dummy_stack_fall_through<field_type> stack;

    // Get some input values
    fifi::random_constant<field_type> constants;

    value_type a = constants.value();
    value_type b = constants.value();
    value_type r = 0;

    fifi::capture_calls<value_type> expected_calls;

    stack s;

    // Multiply, divide and invert are implemented so we do not
    // expect to get any "fall-through" when calling those
    s.m_calls.clear();
    expected_calls.clear();

    r = s.multiply(a,b);
    r = s.divide(a,b);
    r = s.invert(a);

    EXPECT_EQ(expected_calls, s.m_calls);

}


TEST(TestExtendedLogTableArithmetic, fall_through)
{
    {
        SCOPED_TRACE("binary4");
        helper_fall_through<fifi::binary4>();
    }
    {
        SCOPED_TRACE("binary8");
        helper_fall_through<fifi::binary8>();
    }
    {
        SCOPED_TRACE("binary16");
        helper_fall_through<fifi::binary16>();
    }
}

TEST(TestExtendedLogTableArithmetic, multiply)
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

TEST(TestExtendedLogTableArithmetic, divide)
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

TEST(TestExtendedLogTableArithmetic, invert)
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

TEST(TestExtendedLogTableArithmetic, random)
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
