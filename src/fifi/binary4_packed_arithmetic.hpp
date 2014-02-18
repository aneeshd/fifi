// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <type_traits>

#include "binary4.hpp"

namespace fifi
{

    /// Fall through case for other fields
    template<class Field, class Super>
    class binary4_packed_arithmetic : public Super
    { };

    /// Specialization for packed arithmetic for the binary4 field.
    template<class Super>
    class binary4_packed_arithmetic<binary4, Super> : public Super
    {
    public:

        /// @copydoc layer::value_type
        typedef typename Super::value_type value_type;

        /// Ensure that the stack is also initialized with the binary4 field
        static_assert(std::is_same<binary4, typename Super::field_type>::value,
                      "The field used throughout the stack should match");

        /// In the code below we assume that the value_type used for
        /// binary4 is the uint8_t so lets add a check to make sure we
        /// catch it if it changes.
        static_assert(std::is_same<value_type, uint8_t>::value,
                      "The code below assumes we use uint8_t as data type "
                      "for the binary4 field");

    public:

        /// @copydoc layer::packed_multiply(value_type, value_type) const
        value_type packed_multiply(value_type a, value_type b) const
        {
            value_type high = Super::multiply(a >> 4, b >> 4);
            value_type low = Super::multiply(a & 0xf, b & 0xf);

            return (high << 4) | low;
        }

        /// @copydoc layer::packed_divide(value_type, value_type) const
        value_type packed_divide(value_type numerator,
                                 value_type denominator) const
        {
            value_type high = Super::divide(
                numerator >> 4, denominator >> 4);

            value_type low = Super::divide(
                numerator & 0xf, denominator & 0xf);

            return (high << 4) | low;
        }

        /// @copydoc layer::packed_invert(value_type) const
        value_type packed_invert(value_type a) const
        {
            value_type high = Super::invert(a >> 4);
            value_type low = Super::invert(a & 0xf);

            return (high << 4) | low;
        }

        /// @copydoc layer::packed_add(value_type, value_type) const
        value_type packed_add(value_type a, value_type b) const
        {
            return a ^ b;
        }

        /// @copydoc layer::packed_subtract(value_type, value_type) const
        value_type packed_subtract(value_type a, value_type b) const
        {
            // In the binary extension fields add and subtract are the same
            return packed_add(a, b);
        }

    };

}
