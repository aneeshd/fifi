// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/is_value_type_exact.hpp>
#include <fifi/binary.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>
#include <fifi/prime2325.hpp>

TEST(TestIsValueTypeExact, api)
{
    EXPECT_FALSE(fifi::is_value_type_exact<fifi::binary>::value);
    EXPECT_FALSE(fifi::is_value_type_exact<fifi::binary4>::value);
    EXPECT_TRUE(fifi::is_value_type_exact<fifi::binary8>::value);
    EXPECT_TRUE(fifi::is_value_type_exact<fifi::binary16>::value);
    EXPECT_FALSE(fifi::is_value_type_exact<fifi::prime2325>::value);
}
