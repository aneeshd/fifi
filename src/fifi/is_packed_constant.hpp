// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <limits>

#include "binary.hpp"
#include "binary4.hpp"

namespace fifi
{

    /// This function determines whether the given constant is packed or not
    ///
    /// if (fifi::is_packed_constant<fifi::binary4>(0xAA))
    /// {
    ///     std::cout << "The constant is correctly packed" << std::endl;
    /// }
    /// @param constant Field element to be checked if it is packed or not
    /// @return true if constant is packed, otherwise false
    template<class Field>
    inline bool is_packed_constant(typename Field::value_type constant)
    {
        (void) constant;
        return true;
    }

    /// @copydoc is_packed_constant(value_type)
    template<>
    inline bool is_packed_constant<binary>(typename binary::value_type constant)
    {
        return constant == 0 || constant == 255;
    }

    /// @copydoc is_packed_constant(value_type)
    template<>
    inline bool
    is_packed_constant<binary4>(typename binary4::value_type constant)
    {
        return ((constant & 0xF0) >> 4) == (constant & 0x0F);
    }
}
