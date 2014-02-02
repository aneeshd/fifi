// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace fifi
{
    template<class Field, class Super>
    struct helper_packed_fall_through : public Super
    {

        typedef Field field_type;

        typedef typename Field::value_type value_type;

        value_type packed_multiply(value_type a, value_type b) const
        {
            (void) b;
            m_fall_through = true;
            return a;
        }

        value_type packed_divide(value_type numerator,
                                 value_type denominator) const
        {
            (void) denominator;
            m_fall_through = true;
            return numerator;
        }

        value_type packed_invert(value_type a) const
        {
            m_fall_through = true;
            return a;
        }

        value_type packed_add(value_type a, value_type b) const
        {
            (void) b;
            m_fall_through = true;
            return a;
        }

        value_type packed_subtract(value_type a, value_type b) const
        {
            (void) a;
            m_fall_through = true;
            return b;
        }

        mutable bool m_fall_through;
    };

    template<class Field, class Stack>
    void helper_packed_fall_through_test(
        bool expect_add = true,
        bool expect_subtract = true,
        bool expect_multiply = true,
        bool expect_divide = true,
        bool expect_invert = true)
    {
        Stack stack;

        typedef typename Field::value_type value_type;

        // Create an all ones value (zero negated) since invert and divide
        // only works with all ones for the binary case
        value_type all_ones = ~0;

        value_type value = 1;

        stack.m_fall_through = false;
        stack.packed_add(value, value);
        EXPECT_EQ(expect_add, stack.m_fall_through);

        stack.m_fall_through = false;
        stack.packed_subtract(value, value);
        EXPECT_EQ(expect_subtract, stack.m_fall_through);

        stack.m_fall_through = false;
        stack.packed_multiply(value, value);
        EXPECT_EQ(expect_multiply, stack.m_fall_through);

        stack.m_fall_through = false;
        stack.packed_divide(value, all_ones);
        EXPECT_EQ(expect_divide, stack.m_fall_through);

        stack.m_fall_through = false;
        stack.packed_invert(all_ones);
        EXPECT_EQ(expect_invert, stack.m_fall_through);
    }
}
