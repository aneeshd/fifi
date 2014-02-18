// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <type_traits>

namespace fifi
{
    /// @brief This layer implements a simple function for determining
    ///        whether a value is within the valid range of the chosen
    ///        finite field.
    ///        Note: for an explanation of how the enable_if works go here:
    ///        http://stackoverflow.com/q/6972368/660982
    template<class Super>
    class sum_modulo : public Super
    {
    public:

        /// @copydoc layer::field_type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename field_type::value_type value_type;

    public:

        /// @param v The value from the finite field
        /// @return True if the element is within the valid range, false otherwise.
        template<class T = field_type>
        inline typename std::enable_if<T::is_exact,
            typename T::value_type>::type
        calculate_sum_modulo(value_type a, value_type b) const
        {
            // This might be a bit tricky, but what we do here is to
            // check for an integer overflow. If an overflow has
            // happened we have to +1 to sum: we may write the sum as
            // (2^m * h) + l, where h is the high-half of the sum and
            // l is the low half.  Now we realize that 2^m is
            // congruent to +1 when working mod (2^m -1) So we may
            // write (1 * h) + l, now we realize that h must also be 1
            // since we had an overflow thus: If we had an overflow
            // all we have to do is to +1 to the sum.

            value_type sum = a + b;
            sum = sum < a ? sum + 1 : sum;
            return sum;
        }

        /// specialization for non exact types
        /// @copydoc calculate_sum_modulo(value_type, value_type)
        template<class T = field_type>
        inline typename std::enable_if<!T::is_exact,
            typename T::value_type>::type
        calculate_sum_modulo(value_type a, value_type b) const
        {
            value_type sum = a + b;
            sum = sum < a ? sum + 1 : sum;
            if (sum > field_type::max_value)
            {
                return sum - field_type::max_value;
            }
            else
            {
                return sum;
            }
        }
    };
}
