// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>
#include <gtest/gtest.h>

#include <fifi/binary.hpp>

TEST(test_binary, binary)
{
    EXPECT_EQ(1U, fifi::binary::max_value);
    EXPECT_EQ(0U, fifi::binary::min_value);
    EXPECT_EQ(2U, fifi::binary::order);
    EXPECT_EQ(8U, fifi::binary::bits_per_value);
}
