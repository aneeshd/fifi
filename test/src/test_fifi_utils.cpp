// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing


#include <gtest/gtest.h>

#include <fifi/finite_field.hpp>
#include <fifi/fifi_utils.hpp>

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


TEST(TestFifiUtils, field_elements_contained)
{
    EXPECT_EQ(fifi::field_elements_contained<fifi::binary>(1), 8U);
    EXPECT_EQ(fifi::field_elements_contained<fifi::binary>(2), 16U);
    EXPECT_EQ(fifi::field_elements_contained<fifi::binary8>(1), 1U);
    EXPECT_EQ(fifi::field_elements_contained<fifi::binary8>(2), 2U);
    EXPECT_EQ(fifi::field_elements_contained<fifi::binary16>(2), 1U);
    EXPECT_EQ(fifi::field_elements_contained<fifi::binary16>(4), 2U);
    EXPECT_EQ(fifi::field_elements_contained<fifi::prime2325>(4), 1U);
    EXPECT_EQ(fifi::field_elements_contained<fifi::prime2325>(8), 2U);
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
    EXPECT_EQ(fifi::get_value<fifi::binary>(&test[0], 7), 1U);

    const uint8_t *test_const = test;
    EXPECT_EQ(fifi::get_value<fifi::binary>(&test_const[0], 7), 1U);

    uint8_t test8[2] = {0,0};

    fifi::set_value<fifi::binary8>(&test8[0], 0, 43U);
    EXPECT_EQ(fifi::get_value<fifi::binary8>(&test8[0], 0), 43U);

    fifi::set_value<fifi::binary8>(&test8[0], 1, 183);
    EXPECT_EQ(fifi::get_value<fifi::binary8>(&test8[0], 1), 183U);

    const uint8_t *test8_const = &test8[0];
    EXPECT_EQ(fifi::get_value<fifi::binary8>(&test8_const[0],1), 183U);
}

TEST(TestFifiUtils, swap_values)
{
    uint8_t test[2] = { 0x00, 0xff };

    for (uint32_t i = 0; i < 8; ++i)
    {
        fifi::swap_values<fifi::binary>(&test[0], i, i+8);
    }

    EXPECT_EQ(test[0], 0xff);
    EXPECT_EQ(test[1], 0x00);

    const uint8_t *test_const = &test[0];
    EXPECT_EQ(test_const[0], 0xff);
    EXPECT_EQ(test_const[1], 0x00);

    
    uint8_t test8[2] = { 0x00, 0xff };
    
    fifi::swap_values<fifi::binary8>(&test8[0], 0, 1);
    EXPECT_EQ(test8[0], 0xff);
    EXPECT_EQ(test8[1], 0x00);

    const uint8_t *test8_const = &test8[0];
    EXPECT_EQ(test8_const[0], 0xff);
    EXPECT_EQ(test8_const[1], 0x00);
}

