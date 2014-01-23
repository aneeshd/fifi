// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

namespace fifi
{
    /// A binary extension field with 2^16 elements
    struct binary16
    {

        /// The data type used for each element
        typedef uint16_t value_type;

        /// Pointer to a value_type
        typedef value_type* value_ptr;

        /// Reference to a value_type
        typedef value_type& value_ref;

        /// The data type used to hold the order of the field
        /// i.e. the number of elements
        typedef uint32_t order_type;

        /// The data type used to hold the degree of the field
        typedef value_type degree_type;

        /// The maximum decimal value of any field element
        const static value_type max_value = 65535;

        /// The minimum decimal value for any field element
        const static value_type min_value = 0;

        /// The field order i.e. number of field elements
        const static order_type order = 65536;

        /// The field degree
        const static degree_type degree = 16;

        /// X^16+X^12+X^3+X+1 = 69643 We do not need the top bit so we
        /// just use: X^12+X^3+X+1 = 4107 We do not need the top bit
        /// since this bit is not representable in the field. Our
        /// algorithms should manage whether it it necessary to reduce
        /// an element, if needed only lower bits of the prime is
        /// needed.
        const static value_type prime = 4107;

    };
}
