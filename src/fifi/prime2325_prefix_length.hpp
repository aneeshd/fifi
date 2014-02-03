// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>

#include "prime2325.hpp"

namespace fifi
{
    /// @param block_length the length of a block @return the
    /// length of the prefix in bits needed to ensure that given
    /// the block length (i.e. the number of 32 bit values) there
    /// exists a bit prefix not available in the data
    inline uint32_t prime2325_prefix_length(uint32_t block_length)
    {
        assert(block_length > 0);
        assert(block_length <= prime2325::max_block_length);

        // In the absence of a log2 function we look for the highest
        // top bit.
        uint32_t topbit;
        for(topbit = 31; topbit --> 0;)
        {
            if(block_length >> topbit)
                break;
        }

        // How many values can be represented where the most
        // significant bit is top bit.  Create a mask of
        // 0000000..1111..1 where the MSBit is in the top bit position
        uint32_t prefix_values = ~(~0 << topbit) + 1;

        if(prefix_values > block_length)
        {
            return topbit;
        }
        else
        {
            return topbit + 1;
        }
    }
}
