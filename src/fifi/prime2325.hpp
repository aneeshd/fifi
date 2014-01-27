// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>

namespace fifi
{
/// A binary extension field with 2^32 elements
    // struct binary32
    // {
    //     /// value type typedef
    //     typedef uint32_t value_type;

    //     /// Pointer to a value_type
    //     typedef value_type* value_ptr;

    //     /// Reference to a value_type
    //     typedef value_type& value_ref;

    //     /// @return the max value
    //     static value_type max_value()
    //     { return 4294967295U; }

    //     /// @return the min value
    //     static value_type min_value()
    //     { return 0; }

    //     /// @return the order
    //     static uint64_t order()
    //     { return 4294967296ULL; }

    //     /// @return the degree
    //     static uint32_t degree()
    //     { return 32; }

    // };

    /// Prime field 2^32 - 5 Practical implementations may use the
    /// mapping algorithm which was proposed by Crowley et al. and
    /// which allows an efficient mapping of arbitarty binary data to
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

        /// @param block_length the length of a block @return the
        /// length of the prefix in bits needed to ensure that given
        /// the block length (i.e. the number of 32 bit values) there
        /// exists a bit prefix not available in the data
        static uint32_t prefix_length(uint32_t block_length);
    };
}
