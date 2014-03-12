// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <type_traits>

#include "prime2325.hpp"

namespace fifi
{
    /// Will inherit from true-type if Field equal fifi::prime2325
    /// Can be used e.g.:
    ///
    ///    if (is_prime2325<field_type>::value)
    ///    {
    ///        /// do something clever
    ///    }
    ///
    template<class Field>
    struct is_prime2325 : public std::is_same<Field, fifi::prime2325>
    { };
}
