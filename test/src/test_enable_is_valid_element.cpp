// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/enable_is_valid_element.hpp>
#include <fifi/field_types.hpp>

TEST(TestEnableIsValidElement, api)
{
    EXPECT_TRUE(fifi::enable_is_valid_element<fifi::binary>::value);
    EXPECT_TRUE(fifi::enable_is_valid_element<fifi::binary4>::value);
    EXPECT_FALSE(fifi::enable_is_valid_element<fifi::binary8>::value);
    EXPECT_FALSE(fifi::enable_is_valid_element<fifi::binary16>::value);
    // EXPECT_TRUE(fifi::enable_is_valid_element<fifi::binary32>::value);
    EXPECT_TRUE(fifi::enable_is_valid_element<fifi::prime2325>::value);
}

