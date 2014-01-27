// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary4.hpp>
#include <gtest/gtest.h>

TEST(TestBinary4, binary4)
{
    EXPECT_EQ(15U, fifi::binary4::max_value);
    EXPECT_EQ(0U, fifi::binary4::min_value);
    EXPECT_EQ(16U, fifi::binary4::order);
    EXPECT_EQ(4U, fifi::binary4::degree);
    EXPECT_EQ(3U, fifi::binary4::prime);
}
