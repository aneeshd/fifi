// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <type_traits>

namespace fifi
{
    /// @param a First value from the finite field
    /// @param b Second value from the finite field
    /// @return True if the element is within the valid range, false
    /// otherwise.
    template<class Field, class Value>
    inline typename std::enable_if<Field::is_exact, Value>::type
    sum_modulo(Value a, Value b)
    {
        // This might be a bit tricky, but what we do here is to check
        // for an integer overflow. If an overflow has happened we
        // have to +1 to sum: we may write the sum as (2^m * h) + l,
        // where h is the high-half of the sum and l is the low half.
        // Now we realize that 2^m is congruent to +1 when working mod
        // (2^m -1) So we may write 1 + l if h not equal zero and all
        // we have to do is to +1 to the sum.

        Value sum = a + b;
        sum = sum < a ? sum + 1 : sum;
        return sum;
    }

    /// Specialization for non exact types
    /// @copydoc sum_modulo(value_type, value_type) const
    template<class Field, class Value>
    inline typename std::enable_if<!Field::is_exact, Value>::type
    sum_modulo(Value a, Value b)
    {
        // Here we use the same approach as if the field is exact. We
        // however have to handle one additional case, namely if we do
        // not have a data type overflow but anyway exceed the maximum
        // allowed value in the field.
        Value sum = a + b;
        sum = sum < a ? sum + 1 : sum;

        if (sum > Field::max_value)
        {
            return sum - Field::max_value;
        }
        else
        {
            return sum;
        }
    }
}
