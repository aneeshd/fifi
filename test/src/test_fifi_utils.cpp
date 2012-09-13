// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing


#include <gtest/gtest.h>

#include <fifi/finite_field.h>
#include <fifi/fifi_utils.h>

TEST(TestFifiUtils, bytes_needed)
{
    EXPECT_EQ(fifi::bytes_needed<fifi::binary>(1), 1U);
    EXPECT_EQ(fifi::bytes_needed<fifi::binary>(7), 1U);
    EXPECT_EQ(fifi::bytes_needed<fifi::binary>(12), 2U);
    EXPECT_EQ(fifi::bytes_needed<fifi::binary>(345), 44U);
    EXPECT_EQ(fifi::bytes_needed<fifi::binary>(1024), 128U);
    EXPECT_EQ(fifi::bytes_needed<fifi::binary>(1025), 129U);

    EXPECT_EQ(fifi::bytes_needed<fifi::binary8>(7), 7U);
    EXPECT_EQ(fifi::bytes_needed<fifi::binary8>(71), 71U);

    EXPECT_EQ(fifi::bytes_needed<fifi::binary16>(7), 14U);
    EXPECT_EQ(fifi::bytes_needed<fifi::binary16>(743), 1486U);
}


TEST(TestFifiUtils, elements_needed)
{
    EXPECT_EQ(fifi::elements_needed<fifi::binary>(1), 1U);
    EXPECT_EQ(fifi::elements_needed<fifi::binary>(2), 2U);
    EXPECT_EQ(fifi::elements_needed<fifi::binary8>(1), 1U);
    EXPECT_EQ(fifi::elements_needed<fifi::binary8>(2), 2U);
    EXPECT_EQ(fifi::elements_needed<fifi::binary16>(2), 1U);
    EXPECT_EQ(fifi::elements_needed<fifi::binary16>(4), 2U);
    EXPECT_EQ(fifi::elements_needed<fifi::prime2325>(4), 1U);
    EXPECT_EQ(fifi::elements_needed<fifi::prime2325>(8), 2U);
}


TEST(TestFifiUtils, set_value)
{
    uint8_t test[2] = {0,0};

    fifi::set_value<fifi::binary>(&test[0],7,1);
    EXPECT_EQ(test[0],128U);

    fifi::set_value<fifi::binary>(&test[0],0,1);
    EXPECT_EQ(test[0],129U);

    fifi::set_value<fifi::binary>(&test[0],0,0);
    fifi::set_value<fifi::binary>(&test[0],7,0);
    EXPECT_EQ(test[0],0U);

    uint8_t test_8[2] = {0,0};

    fifi::set_value<fifi::binary8>(&test_8[0],0,143);
    EXPECT_EQ(test_8[0],143U);
}

TEST(TestFifiUtils, get_value)
{
    uint8_t test[2] = {0,0};

    fifi::set_value<fifi::binary>(&test[0],7,1);
    EXPECT_EQ(fifi::get_value<fifi::binary>(&test[0],7),1U);

    uint8_t test_8[2] = {0,0};

    fifi::set_value<fifi::binary8>(&test_8[0],0,43U);
    EXPECT_EQ(fifi::get_value<fifi::binary8>(&test_8[0],0),43U);

    fifi::set_value<fifi::binary8>(&test_8[0],1,183);
    EXPECT_EQ(fifi::get_value<fifi::binary8>(&test_8[0],1),183U);
}

