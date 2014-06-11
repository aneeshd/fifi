// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <limits>
#include <type_traits>

#include "binary.hpp"

namespace fifi
{
    /// Fall through case for other fields
    template<class Field, class Super>
    class binary_packed_arithmetic : public Super
    { };

    /// Specialization for packed arithmetic for the binary field.
    template<class Super>
    class binary_packed_arithmetic<binary, Super> : public Super
    {
    public:

        /// @copydoc layer::value_type
        typedef typename Super::value_type value_type;

        /// Ensure that the stack is also initialized with the binary field
        static_assert(std::is_same<binary, typename Super::field_type>::value,
                      "The field used throughout the stack should match");

    public:

        /// @copydoc layer::packed_add(value_type, value_type)
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

        /// @copydoc layer::packed_multiply(value_type, value_type) const
        value_type packed_multiply(value_type a, value_type b) const
        {
            return a & b;
        }

        /// @copydoc layer::packed_divide(value_type, value_type) const
        value_type packed_divide(value_type a, value_type b) const
        {
            // Division by zero is not allowed so the denominator must
            // be all ones
            assert(b == std::numeric_limits<value_type>::max());

            // Since we can only divide by one the numerator will not change
            return a;
        }

        /// @copydoc layer::packed_invert(value_type) const
        value_type packed_invert(value_type a) const
        {
            // Zero does not have an inverse so the value a should be
            // a vector of all ones
            assert(a == std::numeric_limits<value_type>::max());
            return a;
        }
    };
}
