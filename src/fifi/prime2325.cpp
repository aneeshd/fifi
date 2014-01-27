// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>
#include <cassert>

#include "prime2325.hpp"

namespace fifi
{
    const prime2325::value_type prime2325::max_value;
    const prime2325::value_type prime2325::min_value;
    const prime2325::order_type prime2325::order;
    const prime2325::value_type prime2325::prime;
    const uint32_t prime2325::max_block_size;
    const uint32_t prime2325::max_block_length;

    uint32_t prime2325::prefix_length(uint32_t block_length)
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
        // significant bit is topbit.  Create a mask of
        // 0000000..1111..1 where the MSBit is in the topbit position
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
