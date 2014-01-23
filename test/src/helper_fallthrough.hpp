// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace fifi
{
    template<class Field>
    struct helper_fallthrough
    {

        typedef Field field_type;

        typedef typename Field::value_type value_type;

        value_type packed_multiply(value_type a, value_type b) const
        {
            (void) b;
            m_fallthrough = true;
            return a;
        }

        value_type packed_divide(value_type numerator,
                                 value_type denominator) const
        {
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
            (void) b;
            m_fallthrough = true;
            return a;
        }

        value_type packed_subtract(value_type a, value_type b) const
        {
            (void) a;
            m_fallthrough = true;
            return b;
        }

        mutable bool m_fallthrough;
    };
}