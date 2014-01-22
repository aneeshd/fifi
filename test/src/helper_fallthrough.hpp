// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace fifi
{
    template<class Field, class Super>
    struct helper_fallthrough
    {

        typedef Field field_type;

        typedef typename Field::value_type value_type;

        value_type packed_multiply(value_type a, value_type b) const
        {
            m_fallthrough = true;
            return Super::packed_multiply(a, b);
        }

        value_type packed_divide(value_type numerator,
                                 value_type denominator) const
        {
            (void) numerator;
            (void) denominator;
            m_fallthrough = true;
            return Super::packed_divide(numerator, denominator);
        }

        value_type packed_invert(value_type a) const
        {
            m_fallthrough = true;
            return Super::packed_invert(a);
        }

        value_type packed_add(value_type a, value_type b) const
        {
            (void) a;
            (void) b;
            m_fallthrough = true;
            return Super::packed_add(a, b);
        }

        value_type packed_subtract(value_type a, value_type b) const
        {
            (void) a;
            (void) b;
            m_fallthrough = true;
            return Super::packed_subtract(a, b);
        }

        mutable bool m_fallthrough;
    };
}