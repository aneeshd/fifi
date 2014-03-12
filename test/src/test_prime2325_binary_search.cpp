// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>

#include <fifi/prime2325_binary_search.hpp>

#include <gtest/gtest.h>

#include "fifi_unit_test/helper_prime2325_find_a_prefix.hpp"
#include "fifi_unit_test/helper_prime2325_find_one_prefix.hpp"

TEST(test_prime2325_binary_search, find_one_prefix)
{
    fifi::helper_prime2325_find_one_prefix<fifi::prime2325_binary_search>(7);
    fifi::helper_prime2325_find_one_prefix<fifi::prime2325_binary_search>(8);
    fifi::helper_prime2325_find_one_prefix<fifi::prime2325_binary_search>(9);
    fifi::helper_prime2325_find_one_prefix<fifi::prime2325_binary_search>(10);

    uint32_t bits = (rand() % 20) + 1;
    fifi::helper_prime2325_find_one_prefix<fifi::prime2325_binary_search>(bits);
}

/// Tests the size_needed() function for the prime2325_binary_search
TEST(test_prime2325_binary_search, binary_search_size_needed)
{
    // The size needed for the binary search depends on the
    // block length, the number of passes and the size of the
    // counter. In the below it is assumed that the counter is
    // uint32_t if this changes in the future the test has to
    // be updated

    uint32_t size_of_counter = sizeof(uint32_t);

    // The prefix length for 127 is 7 so space needed will be
    // 2^ceil(7/k_pass) * sizeof(uint32_t)
    EXPECT_EQ(fifi::prime2325_binary_search::size_needed(127, 1),
              128*size_of_counter);

    EXPECT_EQ(fifi::prime2325_binary_search::size_needed(127, 2),
              16*size_of_counter);

    EXPECT_EQ(fifi::prime2325_binary_search::size_needed(127, 3),
              8*size_of_counter);

    EXPECT_EQ(fifi::prime2325_binary_search::size_needed(127, 4),
              4*size_of_counter);

    EXPECT_EQ(fifi::prime2325_binary_search::size_needed(127, 5),
              4*size_of_counter);

    EXPECT_EQ(fifi::prime2325_binary_search::size_needed(127, 6),
              4*size_of_counter);

    EXPECT_EQ(fifi::prime2325_binary_search::size_needed(127, 7),
              2*size_of_counter);

    EXPECT_EQ(fifi::prime2325_binary_search::size_needed(127, 8),
              2*size_of_counter);

    EXPECT_EQ(fifi::prime2325_binary_search::size_needed(127, 20),
              2*size_of_counter);
}

/// For different block sizes find a prefix
TEST(test_prime2325_binary_search, find_a_prefix)
{
    fifi::helper_prime2325_find_a_prefix<fifi::prime2325_binary_search>(7);
    fifi::helper_prime2325_find_a_prefix<fifi::prime2325_binary_search>(8);
    fifi::helper_prime2325_find_a_prefix<fifi::prime2325_binary_search>(9);
    fifi::helper_prime2325_find_a_prefix<fifi::prime2325_binary_search>(512);

    uint32_t bits = (rand() % 200000) + 1;
    fifi::helper_prime2325_find_a_prefix<fifi::prime2325_binary_search>(bits);
}
