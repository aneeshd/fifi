// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/prime2325_prefix_length.hpp>


TEST(TestPrime2325PrefixLength, prime2325_prefix_length)
{
    // 2^y => 1 << y

    // In 8 bits we can write 256 distinct bit values so 8 bit should
    // be enough for a block length of 255 etc.
    EXPECT_EQ(fifi::prime2325_prefix_length(127), 7U);
    EXPECT_EQ(fifi::prime2325_prefix_length(128), 8U);
    EXPECT_EQ(fifi::prime2325_prefix_length(255), 8U);
    EXPECT_EQ(fifi::prime2325_prefix_length(256), 9U);
    EXPECT_EQ(fifi::prime2325_prefix_length(511), 9U);
    EXPECT_EQ(fifi::prime2325_prefix_length(512), 10U);
    EXPECT_EQ(fifi::prime2325_prefix_length((1<<29) - 1), 29U);
}
