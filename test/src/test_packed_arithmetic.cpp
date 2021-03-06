// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/binary8.hpp>
#include <fifi/packed_arithmetic.hpp>
#include "fifi_unit_test/helper_fall_through.hpp"

namespace fifi
{
    // Put dummy layers and tests classes in an anonymous namespace
    // to avoid violations of ODF (one-definition-rule) in other
    // translation units
    namespace
    {
        template<class Field>
        struct dummy_stack : public
            packed_arithmetic<
            helper_fall_through<Field> >
        { };
    }
}

/// Check that the packed_arithmetic layer correctly forwards the calls
/// to the arithmetic layer.
TEST(test_packed_arithmetic, fall_through)
{
    typedef fifi::binary8 field_type;
    typedef field_type::value_type value_type;
    typedef fifi::dummy_stack<field_type> stack;

    // Get some input values
    fifi::random_constant<field_type> constants;

    value_type a = constants.pack();
    value_type b = constants.pack();
    value_type r = 0;

    fifi::capture_calls<value_type> expected_calls;

    stack s;

    // Add
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_add(a,b);
    r = s.packed_add(a,b);
    expected_calls.return_add(r);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Subtract
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_subtract(a,b);
    r = s.packed_subtract(a,b);
    expected_calls.return_subtract(r);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Multiply
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_multiply(a,b);
    r = s.packed_multiply(a,b);
    expected_calls.return_multiply(r);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Divide
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_divide(a,b);
    r = s.packed_divide(a,b);
    expected_calls.return_divide(r);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Invert
    s.m_calls.clear();
    expected_calls.clear();

    expected_calls.call_invert(a);
    r = s.packed_invert(a);
    expected_calls.return_invert(r);

    EXPECT_EQ(expected_calls, s.m_calls);
}
