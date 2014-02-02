// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>
#include <gtest/gtest.h>

#include <fifi/binary.hpp>

TEST(TestBinary, binary)
{
    EXPECT_EQ(1U, fifi::binary::max_value);
    EXPECT_EQ(0U, fifi::binary::min_value);
    EXPECT_EQ(2U, fifi::binary::order);
}
