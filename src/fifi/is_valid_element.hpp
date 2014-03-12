// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <type_traits>

namespace fifi
{
    /// Checks whether a value is within the valid range of the chosen
    /// finite field
    /// @param v The value from the finite field to check if it is valid
    /// @return True if the element is within the valid range, false otherwise.
    template<class Field>
    inline typename
    std::enable_if<!Field::is_exact, bool>::type
    is_valid_element(typename Field::value_type v)
    {
        return v <= Field::max_value;
    }

    /// @copydoc is_valid_element(value_type)
    template<class Field>
    inline typename
    std::enable_if<Field::is_exact, bool>::type
    is_valid_element(typename Field::value_type v)
    {
        (void) v;
        return true;
    }
}
