// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace fifi
{

    template<class Super>
    class packed_arithmetic : public Super
    {
    public:

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

    public:

        /// For all binary extension fields the binary
        /// @copydoc finite_field::packed_add()
        value_type packed_multiply(value_type a, value_type b) const
        {
            return Super::multiply(a, b);
        }

        /// @copydoc finite_field::divide()
        value_type packed_divide(value_type numerator, value_type denominator) const
        {
            return Super::divide(numerator, denominator);
        }

        /// @copydoc finite_field::invert()
        value_type packed_invert(value_type a) const
        {
            return Super::invert(a);
        }

        /// @copydoc finite_field::add()
        value_type packed_add(value_type a, value_type b) const
        {
            return Super::packed_add(a, b);
        }

        /// @copydoc finite_field::subtract()
        value_type packed_subtract(value_type a, value_type b) const
        {
            return Super::packed_subract(a, b);
        }

    };

}


