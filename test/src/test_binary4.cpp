// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary4.hpp>
#include <gtest/gtest.h>

TEST(test_binary4, binary4)
{
    EXPECT_EQ(fifi::binary4::value_type(15), fifi::binary4::max_value);
    EXPECT_EQ(fifi::binary4::value_type(0), fifi::binary4::min_value);
    EXPECT_EQ(fifi::binary4::order_type(16), fifi::binary4::order);
    EXPECT_EQ(fifi::binary4::degree_type(4), fifi::binary4::degree);
    EXPECT_EQ(fifi::binary4::value_type(3), fifi::binary4::prime);
}
