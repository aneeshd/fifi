// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing


#include <gtest/gtest.h>

#include <fifi/finite_field.h>
#include <fifi/fifi_utils.h>

TEST(TestFifiUtils, bytes_needed)
{
    EXPECT_EQ(fifi::bytes_needed<fifi::binary>(1), 1);
    EXPECT_EQ(fifi::bytes_needed<fifi::binary>(7), 1);
    EXPECT_EQ(fifi::bytes_needed<fifi::binary>(12), 2);
    EXPECT_EQ(fifi::bytes_needed<fifi::binary>(345), 44);
    EXPECT_EQ(fifi::bytes_needed<fifi::binary>(1024), 128);
    EXPECT_EQ(fifi::bytes_needed<fifi::binary>(1025), 129);

    EXPECT_EQ(fifi::bytes_needed<fifi::binary8>(7), 7);
    EXPECT_EQ(fifi::bytes_needed<fifi::binary8>(71), 71);

    EXPECT_EQ(fifi::bytes_needed<fifi::binary16>(7), 14);
    EXPECT_EQ(fifi::bytes_needed<fifi::binary16>(743), 1486);
}

TEST(TestFifiUtils, set_value)
{
    uint8_t test[2] = {0,0};

    fifi::set_value<fifi::binary>(&test[0],7,1);
    EXPECT_EQ(test[0],128);

    fifi::set_value<fifi::binary>(&test[0],0,1);
    EXPECT_EQ(test[0],129);

    fifi::set_value<fifi::binary>(&test[0],0,0);
    fifi::set_value<fifi::binary>(&test[0],7,0);
    EXPECT_EQ(test[0],0);

    uint8_t test_8[2] = {0,0};

    fifi::set_value<fifi::binary8>(&test_8[0],0,143);
    EXPECT_EQ(test_8[0],143);
}

TEST(TestFifiUtils, get_value)
{
    uint8_t test[2] = {0,0};

    fifi::set_value<fifi::binary>(&test[0],7,1);
    EXPECT_EQ(fifi::get_value<fifi::binary>(&test[0],7),1);

    uint8_t test_8[2] = {0,0};

    fifi::set_value<fifi::binary8>(&test_8[0],0,43);
    EXPECT_EQ(fifi::get_value<fifi::binary8>(&test_8[0],0),43);

    fifi::set_value<fifi::binary8>(&test_8[0],1,183);
    EXPECT_EQ(fifi::get_value<fifi::binary8>(&test_8[0],1),183);
}

