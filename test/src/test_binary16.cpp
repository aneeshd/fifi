// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary16.hpp>

#include <gtest/gtest.h>

TEST(TestBinary16, binary16)
{
    EXPECT_EQ(65535U, fifi::binary16::max_value);
    EXPECT_EQ(0U, fifi::binary16::min_value);
    EXPECT_EQ(65536U, fifi::binary16::order);
    EXPECT_EQ(16U, fifi::binary16::degree);
    EXPECT_EQ(4107U, fifi::binary16::prime);
}
