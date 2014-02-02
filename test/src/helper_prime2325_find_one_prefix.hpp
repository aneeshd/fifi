// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cstdlib>

#include <gtest/gtest.h>

#include <fifi/prime2325.hpp>
#include <fifi/prime2325_prefix_length.hpp>
#include <sak/storage.hpp>
namespace fifi
{
    /// @todo is this a good name? how is this different from find a prefix?

    /// Very simple test we just set a few values and check that we are fine
    template<class Algorithm>
    void helper_prime2325_find_one_prefix(uint32_t prefix_bits)
    {
        // If we have x bits then 2^x gives us the possible
        // values then we make block length 2^x - 1, then there
        // is exactly one missing prefix
        uint32_t block_length = (1 << prefix_bits) - 1;

        std::vector<uint32_t> data(block_length);

        uint8_t skip_value = rand() % block_length;
        uint32_t prefix_length = prime2325_prefix_length(block_length);

        EXPECT_EQ(prefix_bits, prefix_length);

        uint32_t shift_prefix = 32 - prefix_length;

        for(uint32_t i = 0; i < block_length; ++i)
        {
            if(i >= skip_value)
            {
                data[i] = (i+1) << shift_prefix;
            }
            else
            {
                data[i] = i << shift_prefix;
            }
        }

        uint32_t missing_prefix = skip_value << shift_prefix;

        Algorithm p(block_length);

        uint32_t prefix = p.find_prefix(sak::storage(data));

        EXPECT_EQ(missing_prefix, prefix);
    }
}
