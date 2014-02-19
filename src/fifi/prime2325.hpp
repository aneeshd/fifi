// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

namespace fifi
{
    /// Prime field 2^32 - 5 Practical implementations may use the
    /// mapping algorithm which was proposed by Crowley et al. and
    /// which allows an efficient mapping of arbitrary binary data to
    /// the 2^32 - 5 prime field.
    struct prime2325
    {

        /// The data type used for each element
        typedef uint32_t value_type;

        /// Pointer to a value_type
        typedef value_type* value_ptr;

        /// Reference to a value_type
        typedef value_type& value_ref;

        /// The data type used to hold the order of the field
        /// i.e. the number of elements
        typedef uint32_t order_type;

        /// The data type used to hold the degree of the field
        typedef uint32_t degree_type;

        /// The maximum decimal value of any field element
        const static value_type max_value = 4294967290U;

        /// The minimum decimal value for any field element
        const static value_type min_value = 0;

        /// The field order i.e. number of field elements
        const static order_type order = 4294967291U;

        /// The prime number used i.e. (2^32 - 5)
        const static value_type prime = 4294967291U;

        /// When use with the Crowley mapping algorithm
        /// the maximum size in bytes a block can be
        /// (2^29 - 1) * 4 to get bytes
        const static uint32_t max_block_size = 2147483644U;

        /// When use with the Crowley mapping algorithm the maximum
        /// size in bytes a block can be 2^29 - 1 data words (where a
        /// word is 32 bits).
        const static uint32_t max_block_length = 536870911U;

        /// A boolean determining whether the fields value type is exact
        const static bool is_exact = false;
    };
}
