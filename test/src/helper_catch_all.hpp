// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace fifi
{
    template<class Field>
    struct helper_catch_all
    {

        typedef Field field_type;

        typedef typename Field::value_type value_type;

        value_type packed_multiply(value_type a, value_type b) const
        {
            (void) b;
            return a;
        }

        value_type packed_divide(value_type numerator,
                                 value_type denominator) const
        {
            (void) denominator;
            return numerator;
        }

        value_type packed_invert(value_type a) const
        {
            return a;
        }

        value_type packed_add(value_type a, value_type b) const
        {
            (void) b;
            return a;
        }

        value_type packed_subtract(value_type a, value_type b) const
        {
            (void) a;
            return b;
        }

        value_type multiply(value_type a, value_type b) const
        {
            (void) b;
            return a;
        }

        value_type divide(value_type numerator,
                                 value_type denominator) const
        {
            (void) denominator;
            return numerator;
        }

        value_type invert(value_type a) const
        {
            return a;
        }

        value_type add(value_type a, value_type b) const
        {
            (void) b;
            return a;
        }

        value_type subtract(value_type a, value_type b) const
        {
            (void) a;
            return b;
        }

    };
}
