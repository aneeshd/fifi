// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/is_prime2325.hpp>
#include <fifi/binary.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>
#include <fifi/prime2325.hpp>

TEST(TestIsPrime2325, is_prime2325)
{
    EXPECT_FALSE(fifi::is_prime2325<fifi::binary>::value);
    EXPECT_FALSE(fifi::is_prime2325<fifi::binary8>::value);
    EXPECT_FALSE(fifi::is_prime2325<fifi::binary16>::value);
    EXPECT_TRUE(fifi::is_prime2325<fifi::prime2325>::value);
}
