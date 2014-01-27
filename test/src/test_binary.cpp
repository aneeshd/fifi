// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>
#include <gtest/gtest.h>

#include <fifi/binary.hpp>

TEST(test_binary, binary)
{
    EXPECT_EQ(fifi::binary::value_type(1), fifi::binary::max_value);
    EXPECT_EQ(fifi::binary::value_type(0), fifi::binary::min_value);
    EXPECT_EQ(fifi::binary::order_type(2), fifi::binary::order);
    EXPECT_EQ(uint32_t(8), fifi::binary::bits_per_value);
}
