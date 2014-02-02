// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/prime2325_bitmap.hpp>

#include "helper_prime2325_find_a_prefix.hpp"
#include "helper_prime2325_find_one_prefix.hpp"

TEST(TestPrime2325Bitmap, prefix_bitmap)
{
    uint32_t block_length = 255;
    std::vector<uint32_t> data(block_length, 0);

    // Set some of the top 8 bits
    data[0] = 0x01000000;
    data[1] = 0x02000000;

    fifi::prime2325_bitmap p(block_length);

    EXPECT_EQ(p.m_mapping_bits, 32U);
    EXPECT_EQ(p.m_shift_prefix, 24U);

    uint32_t prefix = p.find_prefix(sak::storage(data));

    // Our data contains three values
    EXPECT_NE(0x00000000U, prefix);
    EXPECT_NE(0x01000000U, prefix);
    EXPECT_NE(0x02000000U, prefix);
}

TEST(TestPrime2325Bitmap, find_one_prefix)
{
    fifi::helper_prime2325_find_one_prefix<fifi::prime2325_bitmap>(7);
    fifi::helper_prime2325_find_one_prefix<fifi::prime2325_bitmap>(8);
    fifi::helper_prime2325_find_one_prefix<fifi::prime2325_bitmap>(9);
    fifi::helper_prime2325_find_one_prefix<fifi::prime2325_bitmap>(10);

    uint32_t bits = (rand() % 20) + 1;
    fifi::helper_prime2325_find_one_prefix<fifi::prime2325_bitmap>(bits);
}

/// Tests the size_needed function for the prime2325_bitmap
TEST(TestPrime2325Bitmap, size_needed_bitmap)
{
    // The size returned is in bytes. We need one bit
    // per possible field value. For a block length of 255
    // we need 8 bits that gives 256 different field values
    // that is 256 / 8 = 32
    EXPECT_EQ(fifi::prime2325_bitmap::size_needed(127), 16U);
    EXPECT_EQ(fifi::prime2325_bitmap::size_needed(128), 32U);
    EXPECT_EQ(fifi::prime2325_bitmap::size_needed(254), 32U);
    EXPECT_EQ(fifi::prime2325_bitmap::size_needed(255), 32U);

    // 512 = need 10 bits = 1024 different field values, this gives
    // 1024 / 8 = 128 bytes
    EXPECT_EQ(fifi::prime2325_bitmap::size_needed(512), 128U);
}

/// For different block sizes find a prefix
TEST(TestPrime2325Bitmap, find_a_prefix)
{

    fifi::helper_prime2325_find_a_prefix<fifi::prime2325_bitmap>(7);
    fifi::helper_prime2325_find_a_prefix<fifi::prime2325_bitmap>(8);
    fifi::helper_prime2325_find_a_prefix<fifi::prime2325_bitmap>(9);
    fifi::helper_prime2325_find_a_prefix<fifi::prime2325_bitmap>(512);

    uint32_t bits = (rand() % 200000) + 1;
    fifi::helper_prime2325_find_a_prefix<fifi::prime2325_bitmap>(bits);
}
