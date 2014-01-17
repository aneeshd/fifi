// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

namespace fifi
{

    /// This small helper struct determines whether we should enable
    /// the checks for valid field elements. This is only a concert in
    /// cases where multiple finite field elements can be stored per
    /// value_type.  As a small example both the binary and binary4
    /// fields uses uint8_t as the underlying data type, this means
    /// that e.g. binary can store eight bit elements per value and
    /// binary4 can store two.
    ///
    /// if(can_pack<fifi::binary4>::value)
    /// {
    ///     std::cout << "fifi::binary4 can be packed" << std::endl;
    /// }
    ///
    template<class Field>
    struct enable_is_valid_element
    {
        typedef typename Field::value_type value_type;

        const static bool value =
            !(Field::max_value == std::numeric_limits<value_type>::max());
    };
    // template<class Field, bool V>
    // struct enable_is_valid_element
    // {
    //     /// The value_type used by the field
    //     typedef typename Field::value_type value_type;

    //     /// If the field's maximum value is not equal to the maximum value
    //     /// of the data type then multiple elements can be packed
    //     const static bool value =
    //         !(Field::max_value == std::numeric_limits<value_type>::max());

    //     typedef typename std::enable_if<value == V, bool>::type type;
    // };

}


