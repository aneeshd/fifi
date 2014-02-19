// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <type_traits>

#include "binary.hpp"

namespace fifi
{
    /// Will inherit from true-type if Field equal fifi::binary
    /// Can be used e.g.:
    ///
    ///    if ( is_binary<field_type>::value )
    ///    {
    ///        /// do something clever
    ///    }
    ///
    template<class Field>
    struct is_binary : public std::is_same<Field, fifi::binary>
    { };
}
