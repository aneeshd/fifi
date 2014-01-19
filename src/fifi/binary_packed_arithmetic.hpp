// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace fifi
{

    /// Fall through case for other fields
    template<class Field, class Super>
    class binary_packed_arithmetic : public Super
    { };

    template<class Super>
    class binary_packed_arithmetic<binary,Super> : public Super
    {
    public:

        /// The value type
        typedef typename Super::value_type value_type;

    public:

        /// For all binary extension fields the binary
        /// @copydoc finite_field::packed_add()
        value_type packed_multiply(value_type a, value_type b) const
        {
            return a & b;
        }

        /// @copydoc finite_field::divide()
        value_type packed_divide(value_type numerator,
                                 value_type denominator) const
        {
            // Division by zero is not allowed so the denominator must
            // be all ones
            assert(denominator == std::numeric_limits<value_type>::max());

            return numerator & denominator;
        }

        /// @copydoc finite_field::invert()
        value_type packed_invert(value_type a) const
        {
            // Zero does not have an inverse so the value a should be
            // a vector of all ones
            assert(a == std::numeric_limits<value_type>::max());
            return Super::invert(a);
        }

        /// @copydoc finite_field::add()
        value_type packed_add(value_type a, value_type b) const
        {
            return a ^ b;
        }

        /// @copydoc finite_field::subtract()
        value_type packed_subtract(value_type a, value_type b) const
        {
            return a ^ b;
        }

    };

}


