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
    // Put dummy layers and tests classes in an anonymous namespace
    // to avoid violations of ODF (one-definition-rule) in other
    // translation units
    namespace
    {
        template<class Field>
        struct dummy_stack : public
            binary_simple_online_arithmetic<Field,
            helper_fall_through<Field> >
        { };
    }
}

template<class Field>
void test_fall_through()
{
    typedef Field field_type;
    typedef typename field_type::value_type value_type;
    typedef fifi::dummy_stack<field_type> stack;

    value_type a = 1;
    value_type b = 1;
    value_type r = 0;

    fifi::capture_calls<value_type> expected_calls;

    stack s;

    // Add
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_add(a, b);

    r = s.add(a, b);

    expected_calls.return_add(r);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Subtract
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_subtract(a, b);

    r = s.subtract(a, b);

    expected_calls.return_subtract(r);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Multiply
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_multiply(a, b);

    r = s.multiply(a, b);

    expected_calls.return_multiply(r);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Divide
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_divide(a, b);

    r = s.divide(a, b);

    expected_calls.return_divide(r);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Invert
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_invert(a);

    r = s.invert(a);

    expected_calls.return_invert(r);

    EXPECT_EQ(expected_calls, s.m_calls);
}

template<>
void test_fall_through<fifi::binary>()
{
    typedef fifi::binary field_type;
    typedef field_type::value_type value_type;
    typedef fifi::dummy_stack<field_type> stack;

    value_type a = 1U;
    value_type b = 1U;

    fifi::capture_calls<value_type> expected_calls;

    stack s;

    // Multiply
    s.m_calls.clear();
    expected_calls.clear();
    s.multiply(a, b);
    s.divide(a, b);
    s.invert(a);

    EXPECT_EQ(expected_calls, s.m_calls);
}

TEST(TestBinarySimpleOnlineArithmetic, fall_through)
{
    test_fall_through<fifi::binary>();
    test_fall_through<fifi::binary4>();
    test_fall_through<fifi::binary8>();
    test_fall_through<fifi::binary16>();
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
