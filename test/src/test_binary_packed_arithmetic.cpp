// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/binary_packed_arithmetic.hpp>

namespace fifi
{

    // Put dummy layers and tests classes in an anonymous namespace
    // to avoid violations of ODF (one-definition-rule) in other
    // translation units
    namespace
    {

        template<class Field>
        struct dummy_layer
        {

            typedef Field field_type;

            typedef typename Field::value_type value_type;

            value_type packed_multiply(value_type a, value_type b) const
            {
                (void) a;
                (void) b;
                m_fallthrough = true;
                return a;
            }

            value_type packed_divide(value_type numerator,
                                     value_type denominator) const
            {
                (void) numerator;
                (void) denominator;
                m_fallthrough = true;
                return numerator;
            }

            value_type packed_invert(value_type a) const
            {
                m_fallthrough = true;
                return a;
            }

            value_type packed_add(value_type a, value_type b) const
            {
                (void) a;
                (void) b;
                m_fallthrough = true;
                return a;
            }

            value_type packed_subtract(value_type a, value_type b) const
            {
                (void) a;
                (void) b;
                m_fallthrough = true;
                return a;
            }

            mutable bool m_fallthrough;
        };

        template<class Field>
        struct dummy_stack : public
        binary_packed_arithmetic<Field, dummy_layer<Field> >
        { };


    }
}

template<class Field>
void test_field()
{
    typedef typename Field::value_type value_type;

    fifi::dummy_stack<Field> stack;
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

template<>
void test_field<fifi::binary>()
{
    typedef fifi::binary::value_type value_type;

    fifi::dummy_stack<fifi::binary> stack;

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
    test_field<fifi::binary>();
    test_field<fifi::binary4>();
    test_field<fifi::binary8>();
    test_field<fifi::binary16>();
    test_field<fifi::prime2325>();

}



