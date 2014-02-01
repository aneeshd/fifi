// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing


#include <gtest/gtest.h>

#include <fifi/fifi_utils.hpp>
#include <fifi/binary.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>
#include <fifi/prime2325.hpp>

TEST(TestFifiUtils, elements_to_size)
{
    EXPECT_EQ(fifi::elements_to_size<fifi::binary>(1), 1U);
    EXPECT_EQ(fifi::elements_to_size<fifi::binary>(7), 1U);
    EXPECT_EQ(fifi::elements_to_size<fifi::binary>(8), 1U);
    EXPECT_EQ(fifi::elements_to_size<fifi::binary>(9), 2U);

    EXPECT_EQ(fifi::elements_to_size<fifi::binary8>(1), 1U);
    EXPECT_EQ(fifi::elements_to_size<fifi::binary8>(9), 9U);

    EXPECT_EQ(fifi::elements_to_size<fifi::binary16>(5), 10U);
    EXPECT_EQ(fifi::elements_to_size<fifi::binary16>(13), 26U);

    EXPECT_EQ(fifi::elements_to_size<fifi::prime2325>(2), 8U);
    EXPECT_EQ(fifi::elements_to_size<fifi::prime2325>(3), 12U);
}

TEST(TestFifiUtils, elements_to_length)
{
    EXPECT_EQ(fifi::elements_to_length<fifi::binary>(7), 1U);
    EXPECT_EQ(fifi::elements_to_length<fifi::binary>(8), 1U);
    EXPECT_EQ(fifi::elements_to_length<fifi::binary>(9), 2U);

    EXPECT_EQ(fifi::elements_to_length<fifi::binary8>(1), 1U);
    EXPECT_EQ(fifi::elements_to_length<fifi::binary8>(9), 9U);

    EXPECT_EQ(fifi::elements_to_length<fifi::binary16>(1), 1U);
    EXPECT_EQ(fifi::elements_to_length<fifi::binary16>(9), 9U);

    EXPECT_EQ(fifi::elements_to_length<fifi::prime2325>(1), 1U);
    EXPECT_EQ(fifi::elements_to_length<fifi::prime2325>(9), 9U);
}

TEST(TestFifiUtils, size_to_length)
{
    EXPECT_EQ(fifi::size_to_length<fifi::binary>(1), 1U);
    EXPECT_EQ(fifi::size_to_length<fifi::binary>(2), 2U);
    EXPECT_EQ(fifi::size_to_length<fifi::binary8>(1), 1U);
    EXPECT_EQ(fifi::size_to_length<fifi::binary8>(2), 2U);
    EXPECT_EQ(fifi::size_to_length<fifi::binary16>(2), 1U);
    EXPECT_EQ(fifi::size_to_length<fifi::binary16>(4), 2U);
    EXPECT_EQ(fifi::size_to_length<fifi::prime2325>(4), 1U);
    EXPECT_EQ(fifi::size_to_length<fifi::prime2325>(8), 2U);
}

TEST(TestFifiUtils, length_to_size)
{
    EXPECT_EQ(fifi::length_to_size<fifi::binary16>(1), 2U);
    EXPECT_EQ(fifi::length_to_size<fifi::binary16>(3), 6U);
    EXPECT_EQ(fifi::length_to_size<fifi::binary16>(7), 14U);
    EXPECT_EQ(fifi::length_to_size<fifi::binary16>(743), 1486U);

    EXPECT_EQ(fifi::length_to_size<fifi::binary8>(1), 1U);
    EXPECT_EQ(fifi::length_to_size<fifi::binary8>(3), 3U);
    EXPECT_EQ(fifi::length_to_size<fifi::binary8>(7), 7U);
    EXPECT_EQ(fifi::length_to_size<fifi::binary8>(71), 71U);

    EXPECT_EQ(fifi::length_to_size<fifi::binary>(1), 1U);
    EXPECT_EQ(fifi::length_to_size<fifi::binary>(3), 1U);
    EXPECT_EQ(fifi::length_to_size<fifi::binary>(7), 1U);
    EXPECT_EQ(fifi::length_to_size<fifi::binary>(12), 2U);
    EXPECT_EQ(fifi::length_to_size<fifi::binary>(345), 44U);
    EXPECT_EQ(fifi::length_to_size<fifi::binary>(1024), 128U);
    EXPECT_EQ(fifi::length_to_size<fifi::binary>(1025), 129U);

    EXPECT_EQ(fifi::length_to_size<fifi::prime2325>(1), 4U);
    EXPECT_EQ(fifi::length_to_size<fifi::prime2325>(2), 8U);
    EXPECT_EQ(fifi::length_to_size<fifi::prime2325>(3), 12U);
    EXPECT_EQ(fifi::length_to_size<fifi::prime2325>(3), 12U);
}

TEST(TestFifiUtils, size_to_elements)
{
    EXPECT_EQ(fifi::size_to_elements<fifi::binary>(1), 8U);
    EXPECT_EQ(fifi::size_to_elements<fifi::binary>(2), 16U);
    EXPECT_EQ(fifi::size_to_elements<fifi::binary8>(1), 1U);
    EXPECT_EQ(fifi::size_to_elements<fifi::binary8>(2), 2U);
    EXPECT_EQ(fifi::size_to_elements<fifi::binary16>(2), 1U);
    EXPECT_EQ(fifi::size_to_elements<fifi::binary16>(4), 2U);
    EXPECT_EQ(fifi::size_to_elements<fifi::prime2325>(4), 1U);
    EXPECT_EQ(fifi::size_to_elements<fifi::prime2325>(8), 2U);
}

TEST(TestFifiUtils, length_to_elements)
{
    EXPECT_EQ(fifi::length_to_elements<fifi::binary>(1), 8U);
    EXPECT_EQ(fifi::length_to_elements<fifi::binary>(9), 72U);

    EXPECT_EQ(fifi::length_to_elements<fifi::binary8>(1), 1U);
    EXPECT_EQ(fifi::length_to_elements<fifi::binary8>(9), 9U);

    EXPECT_EQ(fifi::length_to_elements<fifi::binary16>(1), 1U);
    EXPECT_EQ(fifi::length_to_elements<fifi::binary16>(9), 9U);

    EXPECT_EQ(fifi::length_to_elements<fifi::prime2325>(1), 1U);
    EXPECT_EQ(fifi::length_to_elements<fifi::prime2325>(9), 9U);
}

TEST(TestFifiUtils, set_value_binary)
{
    fifi::binary::value_type test[2] = { 0, 0 };

    fifi::set_value<fifi::binary>(&test[0],7,1);
    EXPECT_EQ(128U, test[0]);
    EXPECT_EQ(0U, test[1]);

    fifi::set_value<fifi::binary>(&test[0],0,1);
    EXPECT_EQ(129U, test[0]);
    EXPECT_EQ(0U, test[1]);

    fifi::set_value<fifi::binary>(&test[0],0,0);
    fifi::set_value<fifi::binary>(&test[0],7,0);
    EXPECT_EQ(0U, test[0]);
    EXPECT_EQ(0U, test[1]);

    fifi::set_value<fifi::binary>(&test[0],8,1);
    EXPECT_EQ(0U, test[0]);
    EXPECT_EQ(1U, test[1]);
}

TEST(TestFifiUtils, set_value_binary4)
{
    fifi::binary4::value_type test[2] = { 0, 0 };

    fifi::set_value<fifi::binary4>(&test[0],1,1);
    EXPECT_EQ(16U, test[0]);
    EXPECT_EQ(0U, test[1]);

    fifi::set_value<fifi::binary4>(&test[0],0,1);
    EXPECT_EQ(17U, test[0]);
    EXPECT_EQ(0U, test[1]);

    fifi::set_value<fifi::binary4>(&test[0],0,0);
    fifi::set_value<fifi::binary4>(&test[0],1,0);
    EXPECT_EQ(0U, test[0]);
    EXPECT_EQ(0U, test[1]);

    fifi::set_value<fifi::binary4>(&test[0],2,1);
    EXPECT_EQ(0U, test[0]);
    EXPECT_EQ(1U, test[1]);
}

TEST(TestFifiUtils, set_value_binary8)
{
    fifi::binary8::value_type test[2] = { 0, 0 };

    fifi::set_value<fifi::binary8>(&test[0],0,1);
    EXPECT_EQ(1U, test[0]);
    EXPECT_EQ(0U, test[1]);

    fifi::set_value<fifi::binary8>(&test[0],1,1);
    EXPECT_EQ(1U, test[0]);
    EXPECT_EQ(1U, test[1]);

    fifi::set_value<fifi::binary8>(&test[0],0,0);
    fifi::set_value<fifi::binary8>(&test[0],1,0);
    EXPECT_EQ(0U, test[0]);
    EXPECT_EQ(0U, test[1]);

    fifi::set_value<fifi::binary8>(&test[0],1,1);
    EXPECT_EQ(0U, test[0]);
    EXPECT_EQ(1U, test[1]);
}

TEST(TestFifiUtils, set_value_binary16)
{
    fifi::binary16::value_type test[2] = { 0, 0 };

    fifi::set_value<fifi::binary16>(&test[0],0,1);
    EXPECT_EQ(1U, test[0]);
    EXPECT_EQ(0U, test[1]);

    fifi::set_value<fifi::binary16>(&test[0],1,1);
    EXPECT_EQ(1U, test[0]);
    EXPECT_EQ(1U, test[1]);

    fifi::set_value<fifi::binary16>(&test[0],0,0);
    fifi::set_value<fifi::binary16>(&test[0],1,0);
    EXPECT_EQ(0U, test[0]);
    EXPECT_EQ(0U, test[1]);

    fifi::set_value<fifi::binary16>(&test[0],1,1);
    EXPECT_EQ(0U, test[0]);
    EXPECT_EQ(1U, test[1]);
}

TEST(TestFifiUtils, set_value_prime2325)
{
    fifi::prime2325::value_type test[2] = { 0, 0 };

    fifi::set_value<fifi::prime2325>(&test[0],0,1);
    EXPECT_EQ(1U, test[0]);
    EXPECT_EQ(0U, test[1]);

    fifi::set_value<fifi::prime2325>(&test[0],1,1);
    EXPECT_EQ(1U, test[0]);
    EXPECT_EQ(1U, test[1]);

    fifi::set_value<fifi::prime2325>(&test[0],0,0);
    fifi::set_value<fifi::prime2325>(&test[0],1,0);
    EXPECT_EQ(0U, test[0]);
    EXPECT_EQ(0U, test[1]);

    fifi::set_value<fifi::prime2325>(&test[0],1,1);
    EXPECT_EQ(0U, test[0]);
    EXPECT_EQ(1U, test[1]);
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
