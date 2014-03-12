// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary4_packed_arithmetic.hpp>
#include <fifi/binary8.hpp>
#include <fifi/packed_arithmetic.hpp>
#include <fifi/prime2325.hpp>
#include <fifi/simple_online_arithmetic.hpp>

#include <gtest/gtest.h>

#include "fifi_unit_test/expected_results.hpp"
#include "fifi_unit_test/helper_fall_through.hpp"

namespace fifi
{
    // Put dummy layers and tests classes in an anonymous namespace
    // to avoid violations of ODF (one-definition-rule) in other
    // translation units
    namespace
    {
        // Dummy stack used to check the fall-through
        template<class Field>
        struct fall_through_stack : public
            binary4_packed_arithmetic<Field,
            helper_fall_through<Field> >
        { };

        // Dummy stack used to check the calculations
        template<class Field>
        struct arithmetic_stack : public
            binary4_packed_arithmetic<Field,
            simple_online_arithmetic<
            final<Field> > >
        { };
    }
}

TEST(test_binary4_packed_arithmetic, fall_through_binary)
{
    fifi::test_packed_fall_through<fifi::fall_through_stack<fifi::binary>>();
}

TEST(test_binary4_packed_arithmetic, fall_through_binary4)
{
    typedef fifi::fall_through_stack<fifi::binary4> stack;
    typedef stack::field_type field_type;
    typedef field_type::value_type value_type;

    fifi::capture_calls<value_type> expected_calls;
    stack s;
    {
        s.m_calls.clear();
        expected_calls.clear();

        // add and subtract are independent of the underlying implementation
        s.packed_add(1U, 1U);
        s.packed_subtract(1U, 1U);

        EXPECT_EQ(expected_calls, s.m_calls);
    }
    {
        // Multiply
        s.m_calls.clear();
        expected_calls.clear();

        value_type a = 1;
        value_type b = 1;

        expected_calls.call_multiply(a >> 4, b >> 4);
        expected_calls.call_multiply(a & 0xf, b & 0xf);

        auto constant = s.m_constants;

        expected_calls.return_multiply(constant.value());
        expected_calls.return_multiply(constant.value());

        s.packed_multiply(a, b);

        EXPECT_EQ(expected_calls, s.m_calls);
    }
    {
        // Divide
        s.m_calls.clear();
        expected_calls.clear();

        value_type a = 1;
        value_type b = 0xff;

        expected_calls.call_divide(a >> 4, b >> 4);
        expected_calls.call_divide(a & 0xf, b & 0xf);

        auto constant = s.m_constants;

        expected_calls.return_divide(constant.value());
        expected_calls.return_divide(constant.value());

        s.packed_divide(a, b);

        EXPECT_EQ(expected_calls, s.m_calls);
    }
    {
        // Invert
        s.m_calls.clear();
        expected_calls.clear();

        value_type a = 0xff;

        expected_calls.call_invert(a >> 4);
        expected_calls.call_invert(a & 0xf);

        auto constant = s.m_constants;

        expected_calls.return_invert(constant.value());
        expected_calls.return_invert(constant.value());

        s.packed_invert(a);

        EXPECT_EQ(expected_calls, s.m_calls);
    }
}

TEST(test_binary4_packed_arithmetic, fall_through_binary8)
{
    fifi::test_packed_fall_through<fifi::fall_through_stack<fifi::binary8>>();
}

TEST(test_binary4_packed_arithmetic, fall_through_binary16)
{
    fifi::test_packed_fall_through<fifi::fall_through_stack<fifi::binary16>>();
}

TEST(test_binary4_packed_arithmetic, packed_add)
{
    check_results_packed_add<fifi::arithmetic_stack<fifi::binary4>>();
}

TEST(test_binary4_packed_arithmetic, packed_subtract)
{
    check_results_packed_subtract<fifi::arithmetic_stack<fifi::binary4>>();
}

TEST(test_binary4_packed_arithmetic, packed_multiply)
{
    check_results_packed_multiply<fifi::arithmetic_stack<fifi::binary4>>();
}

TEST(test_binary4_packed_arithmetic, packed_divide)
{
    check_results_packed_divide<fifi::arithmetic_stack<fifi::binary4>>();
}

TEST(test_binary4_packed_arithmetic, packed_invert)
{
    check_results_packed_invert<fifi::arithmetic_stack<fifi::binary4>>();
}
