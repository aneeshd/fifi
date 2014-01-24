// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <type_traits>

#include "is_value_type_exact.hpp"

namespace fifi
{

    /// Checks whether a value is within the valid range of the chosen
    /// finite field
    /// @param v The value from the finite field
    /// @return True if the element is within the valid range, false otherwise.
    template<class Field>
    inline typename
    std::enable_if<is_value_type_exact<Field>::value,
        typename Field::value_type>::type
    sum_modulo(typename Field::value_type a,typename Field::value_type b)
    {
        // This might be a bit tricky, but what we do here is to
        // check for an integer overflow. If an overflow has
        // happened we have to +1 to sum: we may write the sum as
        // (2^m * h) + l, where h is the high-half of the sum and
        // l is the low half.  Now we realize that 2^m is
        // congurent to +1 when working mod (2^m -1) So we may
        // write (1 * h) + l, now we realize that h must also be 1
        // since we had an overflow thus: If we had an overflow
        // all we have to do is to +1 to the sum.

        typename Field::value_type sum = a + b;
        sum = sum < a ? sum + 1 : sum;
        return sum;
    }

    /// @copydoc is_valid_element(typename Field::value_type v)
    template<class Field>
    inline typename
    std::enable_if<!is_value_type_exact<Field>::value,
        typename Field::value_type>::type
    sum_modulo(typename Field::value_type a,typename Field::value_type b)
    {
        typename Field::value_type sum = a + b;
        sum = sum < a ? sum + 1 : sum;
        sum = sum > Field::max_value ? sum - Field::max_value : sum;

        return sum;
    }

}
