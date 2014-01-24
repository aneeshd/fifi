// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <limits>

namespace fifi
{

    /// This small helper struct determines whether we should enable
    /// the checks for valid field elements. This is only a concern in
    /// cases where multiple finite field elements can be stored per
    /// value_type. As a small example both the binary and binary4
    /// fields uses uint8_t as the underlying data type, this means
    /// that we should check that variables from those fields are
    /// within the valid range of the field. On the other hand
    /// variables from e.g. binary8 cannot contains illegal values
    /// since the field value requires the entire data type.
    ///
    /// if(fifi::is_value_type_exact<fifi::binary4>::value)
    /// {
    ///     std::cout << "fifi::binary4 should be checked" << std::endl;
    /// }
    ///
    template<class Field>
    struct is_value_type_exact
    {
        typedef typename Field::value_type value_type;

        const static bool value =
            (Field::max_value == std::numeric_limits<value_type>::max());
    };

}
