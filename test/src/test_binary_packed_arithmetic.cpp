// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/binary_packed_arithmetic.hpp>

#include "helper_fallthrough_stack.hpp"

template<Arithmetic, class Field>
void test_field()
{
    typedef typename Field::value_type value_type;

    fifi::helper_fallthrough_stack<Arithmetic, Field> stack;
    value_type value = 1;

    stack.m_fallthrough = false;
    value = stack.packed_multiply(value, value);
    EXPECT_TRUE(stack.m_fallthrough);

    stack.m_fallthrough = false;
    value = stack.packed_divide(value, value);
    EXPECT_TRUE(stack.m_fallthrough);

    stack.m_fallthrough = false;
    value = stack.packed_invert(value);
    EXPECT_TRUE(stack.m_fallthrough);

    stack.m_fallthrough = false;
    value = stack.packed_add(value, value);
    EXPECT_TRUE(stack.m_fallthrough);

    stack.m_fallthrough = false;
    value = stack.packed_subtract(value, value);
    EXPECT_TRUE(stack.m_fallthrough);

}

template<class Arithmetic>
void test_field<fifi::binary>()
{
    typedef fifi::binary::value_type value_type;

    fifi::helper_fallthrough_stack<Arithmetic, fifi::binary> stack;

    // Create an all ones value (zero negated) since invert and divide
    // only works with all ones for the binary case
    value_type all_ones = ~0;
    value_type value = 1;

    stack.m_fallthrough = false;
    value = stack.packed_multiply(value, value);
    EXPECT_FALSE(stack.m_fallthrough);

    stack.m_fallthrough = false;
    value = stack.packed_divide(value, all_ones);
    EXPECT_FALSE(stack.m_fallthrough);

    stack.m_fallthrough = false;
    value = stack.packed_invert(all_ones);
    EXPECT_FALSE(stack.m_fallthrough);

    stack.m_fallthrough = false;
    value = stack.packed_add(value, value);
    EXPECT_FALSE(stack.m_fallthrough);

    stack.m_fallthrough = false;
    value = stack.packed_subtract(value, value);
    EXPECT_FALSE(stack.m_fallthrough);
}

TEST(TestBinaryPackedArithmetic, api)
{
    test_field<fifi::binary_packed_arithmetic, fifi::binary>();
    test_field<fifi::binary_packed_arithmetic, fifi::binary4>();
    test_field<fifi::binary_packed_arithmetic, fifi::binary8>();
    test_field<fifi::binary_packed_arithmetic, fifi::binary16>();
    test_field<fifi::binary_packed_arithmetic, fifi::prime2325>();
}
