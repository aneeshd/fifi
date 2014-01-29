// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/prime2325.hpp>
#include <gtest/gtest.h>

TEST(TestPrime2325, prime2325)
{
    EXPECT_EQ(4294967290U, fifi::prime2325::max_value);
    EXPECT_EQ(0U, fifi::prime2325::min_value);
    EXPECT_EQ(4294967291U, fifi::prime2325::order);
    EXPECT_EQ(4294967291U, fifi::prime2325::prime);
    EXPECT_EQ(2147483644U, fifi::prime2325::max_block_size);
    EXPECT_EQ(536870911U, fifi::prime2325::max_block_length);
}

TEST(TestPrime2325, prefix_length)
{
    // 2^y => 1 << y

    // In 8 bits we can write 256 distinct bit values so 8 bit should
    // be enough for a block length of 255 etc.
    EXPECT_EQ(fifi::prime2325::prefix_length(127), 7U);
    EXPECT_EQ(fifi::prime2325::prefix_length(128), 8U);
    EXPECT_EQ(fifi::prime2325::prefix_length(255), 8U);
    EXPECT_EQ(fifi::prime2325::prefix_length(256), 9U);
    EXPECT_EQ(fifi::prime2325::prefix_length(511), 9U);
    EXPECT_EQ(fifi::prime2325::prefix_length(512), 10U);
    EXPECT_EQ(fifi::prime2325::prefix_length((1<<29) - 1), 29U);
}
