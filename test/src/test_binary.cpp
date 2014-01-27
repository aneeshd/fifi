// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <stdint.h>
#include <gtest/gtest.h>

#include <fifi/binary.hpp>

TEST(test_binary, max_value)
{
    uint8_t t1 = fifi::binary::max_value;
    uint8_t t2 = fifi::binary::min_value;
    uint8_t t3 = fifi::binary::order;
    uint8_t t4 = fifi::binary::bits_per_value;
    EXPECT_EQ(1, t1);
    EXPECT_EQ(0, t2);
    EXPECT_EQ(2, t3);
    EXPECT_EQ(8, t4);
    /*
    EXPECT_EQ(1, fifi::binary::max_value);
    EXPECT_EQ(0, fifi::binary::min_value);
    EXPECT_EQ(2, fifi::binary::order);
    EXPECT_EQ(8, fifi::binary::bits_per_value);
    */
}
