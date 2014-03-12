// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/is_binary.hpp>
#include <fifi/prime2325.hpp>

#include <gtest/gtest.h>

TEST(test_is_binary, is_binary)
{
    EXPECT_TRUE(fifi::is_binary<fifi::binary>::value);
    EXPECT_FALSE(fifi::is_binary<fifi::binary4>::value);
    EXPECT_FALSE(fifi::is_binary<fifi::binary8>::value);
    EXPECT_FALSE(fifi::is_binary<fifi::binary16>::value);
    EXPECT_FALSE(fifi::is_binary<fifi::prime2325>::value);
}
