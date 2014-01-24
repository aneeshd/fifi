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
    std::enable_if<!is_value_type_exact<Field>::value, bool>::type
    is_valid_element(typename Field::value_type v)
    {
        return v <= Field::max_value;
    }

    /// @copydoc is_valid_element(typename Field::value_type v)
    template<class Field>
    inline typename
    std::enable_if<is_value_type_exact<Field>::value, bool>::type
    is_valid_element(typename Field::value_type v)
    {
        (void) v;
        return true;
    }

}
