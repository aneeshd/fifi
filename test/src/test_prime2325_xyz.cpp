// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/optimal_prime.h>
#include <fifi/field_types.h>
#include <fifi/prime2325_bitmap.h>
#include <fifi/prime2325_binary_search.h>

#include <sak/storage.h>

#include <cmath>
#include <stdexcept>

void print_bits_header()
{
        for(uint32_t i = 32; i--> 0;)
    {
        std::cout << std::setw(2) << i << " ";
    }

    std::cout << std::endl;
}

void print_bits(uint32_t v)
{
    for(uint32_t i = 32; i--> 0;)
    {
        std::cout << std::setw(2) << (v >> i & 0x1) << " ";
    }
    std::cout << std::endl;
}

TEST(test_prime2325, prefix_length)
{
    // 2^y => 1 << y

    // In 8 bits we can write 256 distinct bit values so 8 bit should
    // be enough for a block length of 255 etc.
    EXPECT_EQ(fifi::prime2325::prefix_length(127), 7U);
    EXPECT_EQ(fifi::prime2325::prefix_length(128), 8U);
    EXPECT_EQ(fifi::prime2325::prefix_length(255), 8U);
    EXPECT_EQ(fifi::prime2325::prefix_length(256), 9U);
    EXPECT_EQ(fifi::prime2325::prefix_length((1<<29) - 1), 29U);
}

/// Very simple test we just set a few values and check that we are fine
TEST(test_prime2325, prefix_bitmap)
{
    uint32_t block_length = 255;
    std::vector<uint32_t> data(block_length, 0);

    // Set some of the top 8 bits
    data[0] = 0x01000000;
    data[1] = 0x02000000;

    fifi::prime2325_bitmap p(block_length);

    EXPECT_EQ(p.m_mapping_bits, 32U);
    EXPECT_EQ(p.m_shift_prefix, 24U);

    uint32_t prefix = p.find_prefix(sak::storage_list(data));

    // Our data contains three values
    EXPECT_TRUE(prefix != 0x00000000U);
    EXPECT_TRUE(prefix != 0x01000000U);
    EXPECT_TRUE(prefix != 0x02000000U);
}

/// Select a random value and set all but that one
TEST(test_prime2325, find_prefix)
{
    uint32_t block_size = 255;
    std::vector<uint32_t> data(block_size);

    uint8_t skip_value = rand() % block_size;

    for(uint32_t i = 0; i < block_size; ++i)
    {
        if(i >= skip_value)
        {
            data[i] = (i+1) << 24;
        }
        else
        {
            data[i] = i << 24;
        }
    }

    uint32_t missing_prefix = skip_value << 24;

    fifi::prime2325_bitmap p(block_size);

    uint32_t prefix = p.find_prefix(sak::storage_list(data));

    EXPECT_EQ(missing_prefix, prefix);
}

/// Tests the size_needed function for the prime2325_bitmap
TEST(test_prime2325, size_needed_bitmap)
{
    // The size returned is in bytes. We need one bit
    // per possible field value. For a block length of 255
    // we need 8 bits that gives 256 different field values
    // that is 256 / 8 = 32
    EXPECT_EQ(fifi::prime2325_bitmap::size_needed(127), 16U);
    EXPECT_EQ(fifi::prime2325_bitmap::size_needed(128), 32U);
    EXPECT_EQ(fifi::prime2325_bitmap::size_needed(254), 32U);
    EXPECT_EQ(fifi::prime2325_bitmap::size_needed(255), 32U);
}


/// Select a random value and set all but that one
TEST(test_prime2325, find_prefix_binary_search)
{
    uint32_t block_size = 255;
    std::vector<uint32_t> data(block_size);

    uint8_t skip_value = rand() % block_size;

    for(uint32_t i = 0; i < block_size; ++i)
    {
        if(i >= skip_value)
        {
            data[i] = (i+1) << 24;
        }
        else
        {
            data[i] = i << 24;
        }
    }

    uint32_t missing_prefix = skip_value << 24;
    fifi::prime2325_binary_search p(block_size, 4);

    uint32_t prefix = p.find_prefix(sak::storage_list(data));

    EXPECT_EQ(missing_prefix, prefix);
}




