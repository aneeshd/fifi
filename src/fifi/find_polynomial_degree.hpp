// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>

#include "is_valid_element.hpp"

namespace fifi
{
    /// A simple function for determining the degree of a binary extension field
    /// polynomial representation.
    /// @param a A binary extension field element
    /// @return the degree of the polynomial representation of the element.
    template<class Field, class Value>
    inline Value find_polynomial_degree(Value a)
    {
        assert(is_valid_element<Field>(a));

        Value degree = 0;

        // Add a check for unsigned or arithmetic shifts
        a >>= 1;

        while (a > 0)
        {
            ++degree;
            a >>= 1;
        }

        return degree;
    }
}
