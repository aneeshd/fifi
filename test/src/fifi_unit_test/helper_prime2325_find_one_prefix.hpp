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
    /// Test that we can find a prefix for a carefully generated
    /// buffer. The values in the buffer are constructed so that only
    /// one unique prefix is guaranteed to exist.
    ///
    /// @param prefix_bits The number of prefix bits to use. This
    /// determines the maximum block length that we can use.
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

        // Here we fill the block of data with a unique value each
        // element making sure that only one prefix exist in the
        // block.
        //
        // This is done in the following way with the shift_prefix we
        // know which bits will be inspected by the prefix search so
        // we shift a number [0:block_length-1] up to the prefix
        //
        // Example (shift_prefix 28) of how the bits are filled:
        //
        // Iteration 0: 0000xxxxxxxxxx
        // Iteration 1: 0001xxxxxxxxxx
        // Iteration 2: 0010xxxxxxxxxx
        // Iteration 3: 0011xxxxxxxxxx
        //
        // and so forth.

        for (uint32_t i = 0; i < block_length; ++i)
        {
            if (i >= skip_value)
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
