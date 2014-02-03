// Copyright Steinwurf ApS 2011-2014.
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
