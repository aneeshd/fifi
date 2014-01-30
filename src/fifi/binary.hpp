// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <limits>

namespace fifi
{
    /// The binary field, containing the two elements {0,1}. We do not
    /// provide the degree() function since this is not an extension
    /// field.
    struct binary
    {

        /// The data type used for each element
        typedef uint8_t value_type;

        /// Pointer to a value_type
        typedef value_type* value_ptr;

        /// Reference to a value_type
        typedef value_type& value_ref;

        /// The data type used to hold the order of the field i.e. the
        /// number of elements
        typedef uint8_t order_type;

        /// The maximum decimal value of any field element
        const static value_type max_value = 1;

        /// The minimum decimal value for any field element
        const static value_type min_value = 0;

        /// The field order i.e. number of field elements
        const static order_type order = 2;

        /// The number of bits in a value_type
        const static uint32_t bits_per_value =
            std::numeric_limits<binary::value_type>::digits;

    };
}
