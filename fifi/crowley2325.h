// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#ifndef FIFI_CROWLEY_2325_H
#define FIFI_CROWLEY_2325_H

#include <stdint.h>
#include "field_types.h"

namespace fifi
{

    /// This mapping algorithm was proposed by Cowley et al.
    /// and allows an efficient mapping of arbitarty binary data
    /// to the 2^32 - 5 prime field.
    struct crowley2325
    {
        /// @returns the maximum size in bytes a block can be
        static uint32_t max_block_size();

        /// @returns the maximum size in bytes a block can be
        static uint32_t max_block_length();

        /// @return the prefix length in bits needed for a specific block
        ///         length
        static uint32_t prefix_length(uint32_t block_length);
    };

    inline uint32_t crowley2325::max_block_size()
    {
        // (2^29 - 2) * 4 to get bytes
        return 2147483640U;
    }

    inline uint32_t crowley2325::max_block_length()
    {
        // 2^29 - 2 data words (where every word is 32 bits).
        return 536870910U;
    }

    inline uint32_t crowley2325::prefix_length(uint32_t block_length)
    {
        assert(block_length > 0);
        assert(block_length <= crowley2325::max_block_length());

        // We need enough bits to ensure that we can find a value not
        // present in the block thus the + 1
        block_length += 1;

        // In the absence of a log2 function we simply
        // look for the highest top bit.
        uint32_t log2;
        for(log2 = 31; log2 --> 0;)
        {
            if(block_length >> log2)
                break;
        }

        return log2 + 1;
    }


}

#endif

