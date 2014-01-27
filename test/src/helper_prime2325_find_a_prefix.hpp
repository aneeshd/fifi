// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

#include <gtest/gtest.h>

#include <fifi/prime2325.hpp>
#include <fifi/prime2325_apply_prefix.hpp>

#include <sak/storage.hpp>

namespace fifi
{
    /// @todo is this a good name? how is this different from find one prefix?

    template<class Algorithm>
    void prime2325_find_a_prefix(std::vector<uint32_t> data)
    {
        uint32_t block_length = data.size();
        Algorithm p(block_length);

        uint32_t prefix = p.find_prefix(sak::storage(data));

        // Check that the prefix does not appear in the data
        for(uint32_t i = 0; i < block_length; ++i)
        {
            EXPECT_NE(data[i], prefix);
        }

        // Apply the prefix and test that all values are below the prime
        apply_prefix(sak::storage(data), ~prefix);

        // Check that all values are below the prefix
        for(uint32_t i = 0; i < block_length; ++i)
        {
            EXPECT_TRUE(data[i] < fifi::prime2325::prime);
        }
    }

    template<class Algorithm>
    void helper_prime2325_find_a_prefix(uint32_t block_length)
    {
        {
            std::vector<uint32_t> data(block_length);

            for(uint32_t i = 0; i < block_length; ++i)
            {
                data[i] = rand();
            }

            prime2325_find_a_prefix<Algorithm>(data);
        }

        {
            std::vector<uint32_t> data(block_length, 0xffffffffU);

            prime2325_find_a_prefix<Algorithm>(data);
        }
    }
}