// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary16.hpp>
#include <gtest/gtest.h>

TEST(test_binary16, binary16)
{
    EXPECT_EQ(fifi::binary16::value_type(65535), fifi::binary16::max_value);
    EXPECT_EQ(fifi::binary16::value_type(0), fifi::binary16::min_value);
    EXPECT_EQ(fifi::binary16::order_type(65536), fifi::binary16::order);
    EXPECT_EQ(fifi::binary16::degree_type(16), fifi::binary16::degree);
    EXPECT_EQ(fifi::binary16::value_type(4107), fifi::binary16::prime);
}
