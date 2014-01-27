// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary8.hpp>
#include <gtest/gtest.h>

TEST(test_binary8, binary8)
{
    EXPECT_EQ(fifi::binary8::value_type(255), fifi::binary8::max_value);
    EXPECT_EQ(fifi::binary8::value_type(0), fifi::binary8::min_value);
    EXPECT_EQ(fifi::binary8::order_type(256), fifi::binary8::order);
    EXPECT_EQ(fifi::binary8::degree_type(8), fifi::binary8::degree);
    EXPECT_EQ(fifi::binary8::value_type(29), fifi::binary8::prime);
}
