// Copyright Steinwurf APS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE_1_0.txt or
// http://www.steinwurf.dk/licensing

#include <gtest/gtest.h>

#include <fifi/is_binary.h>

TEST(TestIsBinary, is_binary)
{
    EXPECT_TRUE(fifi::is_binary<fifi::binary>::value == true);
    EXPECT_TRUE(fifi::is_binary<fifi::binary8>::value == false);
    EXPECT_TRUE(fifi::is_binary<fifi::binary16>::value == false);
}
