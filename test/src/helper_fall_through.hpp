// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace fifi
{
    template<class Field, class Super>
    struct helper_fall_through : public Super
    {

        typedef Field field_type;

        typedef typename Field::value_type value_type;

        value_type multiply(value_type a, value_type b) const
        {
            (void) b;
            m_fall_through = true;
            return a;
        }

        value_type divide(value_type numerator,
                                 value_type denominator) const
        {
            (void) denominator;
            m_fall_through = true;
            return numerator;
        }

        value_type invert(value_type a) const
        {
            m_fall_through = true;
            return a;
        }

        value_type add(value_type a, value_type b) const
        {
            (void) b;
            m_fall_through = true;
            return a;
        }

        value_type subtract(value_type a, value_type b) const
        {
            (void) a;
            m_fall_through = true;
            return b;
        }

        mutable bool m_fall_through;
    };

    struct fall_through_result
    {
        bool add = true;
        bool subtract = true;
        bool multiply = true;
        bool divide = true;
        bool invert = true;
    };

    template<class Field, class Stack>
    void helper_fall_through_test(const fall_through_result& expected)
    {
        Stack stack;

        typedef typename Field::value_type value_type;

        value_type value = 1;

        stack.m_fall_through = false;
        stack.add(value, value);
        EXPECT_EQ(expected.add, stack.m_fall_through);

        stack.m_fall_through = false;
        stack.subtract(value, value);
        EXPECT_EQ(expected.subtract, stack.m_fall_through);

        stack.m_fall_through = false;
        stack.multiply(value, value);
        EXPECT_EQ(expected.multiply, stack.m_fall_through);

        stack.m_fall_through = false;
        stack.divide(value, value);
        EXPECT_EQ(expected.divide, stack.m_fall_through);

        stack.m_fall_through = false;
        stack.invert(value);
        EXPECT_EQ(expected.invert, stack.m_fall_through);
    }
}
