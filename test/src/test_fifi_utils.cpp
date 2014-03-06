// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary8.hpp>
#include <fifi/fifi_utils.hpp>
#include <fifi/prime2325.hpp>

#include <gtest/gtest.h>

TEST(test_fifi_utils, elements_to_size)
{
    {
        SCOPED_TRACE("binary");
        EXPECT_EQ(1U, fifi::elements_to_size<fifi::binary>(1));
        EXPECT_EQ(1U, fifi::elements_to_size<fifi::binary>(7));
        EXPECT_EQ(1U, fifi::elements_to_size<fifi::binary>(8));
        EXPECT_EQ(2U, fifi::elements_to_size<fifi::binary>(9));
    }

    {
        SCOPED_TRACE("binary4");
        EXPECT_EQ(1U, fifi::elements_to_size<fifi::binary4>(1));
        EXPECT_EQ(4U, fifi::elements_to_size<fifi::binary4>(7));
        EXPECT_EQ(4U, fifi::elements_to_size<fifi::binary4>(8));
        EXPECT_EQ(5U, fifi::elements_to_size<fifi::binary4>(9));
    }

    {
        SCOPED_TRACE("binary8");
        EXPECT_EQ(1U, fifi::elements_to_size<fifi::binary8>(1));
        EXPECT_EQ(9U, fifi::elements_to_size<fifi::binary8>(9));
    }

    {
        SCOPED_TRACE("binary16");
        EXPECT_EQ(10U, fifi::elements_to_size<fifi::binary16>(5));
        EXPECT_EQ(26U, fifi::elements_to_size<fifi::binary16>(13));
    }

    {
        SCOPED_TRACE("prime2325");
        EXPECT_EQ(8U, fifi::elements_to_size<fifi::prime2325>(2));
        EXPECT_EQ(12U, fifi::elements_to_size<fifi::prime2325>(3));
    }
}

TEST(test_fifi_utils, elements_to_length)
{
    {
        SCOPED_TRACE("binary");
        EXPECT_EQ(1U, fifi::elements_to_length<fifi::binary>(7));
        EXPECT_EQ(1U, fifi::elements_to_length<fifi::binary>(8));
        EXPECT_EQ(2U, fifi::elements_to_length<fifi::binary>(9));
    }
    {
        SCOPED_TRACE("binary4");
        EXPECT_EQ(4U, fifi::elements_to_length<fifi::binary4>(7));
        EXPECT_EQ(4U, fifi::elements_to_length<fifi::binary4>(8));
        EXPECT_EQ(5U, fifi::elements_to_length<fifi::binary4>(9));
    }
    {
        SCOPED_TRACE("binary8");
        EXPECT_EQ(1U, fifi::elements_to_length<fifi::binary8>(1));
        EXPECT_EQ(9U, fifi::elements_to_length<fifi::binary8>(9));
        EXPECT_EQ(100U, fifi::elements_to_length<fifi::binary8>(100));
    }
    {
        SCOPED_TRACE("binary16");
        EXPECT_EQ(1U, fifi::elements_to_length<fifi::binary16>(1));
        EXPECT_EQ(9U, fifi::elements_to_length<fifi::binary16>(9));
        EXPECT_EQ(100U, fifi::elements_to_length<fifi::binary16>(100));
    }
    {
        SCOPED_TRACE("prime2325");
        EXPECT_EQ(1U, fifi::elements_to_length<fifi::prime2325>(1));
        EXPECT_EQ(9U, fifi::elements_to_length<fifi::prime2325>(9));
        EXPECT_EQ(100U, fifi::elements_to_length<fifi::prime2325>(100));
}}

TEST(test_fifi_utils, size_to_length)
{
    {
        SCOPED_TRACE("binary");
        EXPECT_EQ(1U, fifi::size_to_length<fifi::binary>(1));
        EXPECT_EQ(2U, fifi::size_to_length<fifi::binary>(2));
    }

    {
        SCOPED_TRACE("binary4");
        EXPECT_EQ(1U, fifi::size_to_length<fifi::binary4>(1));
        EXPECT_EQ(2U, fifi::size_to_length<fifi::binary4>(2));
    }

    {
        SCOPED_TRACE("binary8");
        EXPECT_EQ(1U, fifi::size_to_length<fifi::binary8>(1));
        EXPECT_EQ(2U, fifi::size_to_length<fifi::binary8>(2));
    }

    {
        SCOPED_TRACE("binary16");
        EXPECT_EQ(1U, fifi::size_to_length<fifi::binary16>(2));
        EXPECT_EQ(2U, fifi::size_to_length<fifi::binary16>(4));
    }

    {
        SCOPED_TRACE("prime2325");
        EXPECT_EQ(1U, fifi::size_to_length<fifi::prime2325>(4));
        EXPECT_EQ(2U, fifi::size_to_length<fifi::prime2325>(8));
    }
}

TEST(test_fifi_utils, length_to_size)
{
    {
        SCOPED_TRACE("binary");
        EXPECT_EQ(1U, fifi::length_to_size<fifi::binary>(1));
        EXPECT_EQ(1U, fifi::length_to_size<fifi::binary>(3));
        EXPECT_EQ(1U, fifi::length_to_size<fifi::binary>(7));
        EXPECT_EQ(2U, fifi::length_to_size<fifi::binary>(12));
        EXPECT_EQ(44U, fifi::length_to_size<fifi::binary>(345));
        EXPECT_EQ(128U, fifi::length_to_size<fifi::binary>(1024));
        EXPECT_EQ(129U, fifi::length_to_size<fifi::binary>(1025));
    }
    {
        SCOPED_TRACE("binary4");
        EXPECT_EQ(1U, fifi::length_to_size<fifi::binary4>(1));
        EXPECT_EQ(1U, fifi::length_to_size<fifi::binary4>(2));
        EXPECT_EQ(2U, fifi::length_to_size<fifi::binary4>(3));
        EXPECT_EQ(2U, fifi::length_to_size<fifi::binary4>(4));
        EXPECT_EQ(173U, fifi::length_to_size<fifi::binary4>(345));
        EXPECT_EQ(512U, fifi::length_to_size<fifi::binary4>(1024));
        EXPECT_EQ(513U, fifi::length_to_size<fifi::binary4>(1025));
    }
    {
        SCOPED_TRACE("binary8");
        EXPECT_EQ(1U, fifi::length_to_size<fifi::binary8>(1));
        EXPECT_EQ(3U, fifi::length_to_size<fifi::binary8>(3));
        EXPECT_EQ(7U, fifi::length_to_size<fifi::binary8>(7));
        EXPECT_EQ(71U, fifi::length_to_size<fifi::binary8>(71));
    }
    {
        SCOPED_TRACE("binary16");
        EXPECT_EQ(2U, fifi::length_to_size<fifi::binary16>(1));
        EXPECT_EQ(6U, fifi::length_to_size<fifi::binary16>(3));
        EXPECT_EQ(14U, fifi::length_to_size<fifi::binary16>(7));
        EXPECT_EQ(1486U, fifi::length_to_size<fifi::binary16>(743));
    }
    {
        SCOPED_TRACE("prime2325");
        EXPECT_EQ(4U, fifi::length_to_size<fifi::prime2325>(1));
        EXPECT_EQ(8U, fifi::length_to_size<fifi::prime2325>(2));
        EXPECT_EQ(12U, fifi::length_to_size<fifi::prime2325>(3));
        EXPECT_EQ(12U, fifi::length_to_size<fifi::prime2325>(3));
    }
}

TEST(test_fifi_utils, size_to_elements)
{
    {
        SCOPED_TRACE("binary");
        EXPECT_EQ(8U, fifi::size_to_elements<fifi::binary>(1));
        EXPECT_EQ(16U, fifi::size_to_elements<fifi::binary>(2));
    }

    {
        SCOPED_TRACE("binary4");
        EXPECT_EQ(2U, fifi::size_to_elements<fifi::binary4>(1));
        EXPECT_EQ(4U, fifi::size_to_elements<fifi::binary4>(2));
    }

    {
        SCOPED_TRACE("binary8");
        EXPECT_EQ(1U, fifi::size_to_elements<fifi::binary8>(1));
        EXPECT_EQ(2U, fifi::size_to_elements<fifi::binary8>(2));
    }

    {
        SCOPED_TRACE("binary16");
        EXPECT_EQ(1U, fifi::size_to_elements<fifi::binary16>(2));
        EXPECT_EQ(2U, fifi::size_to_elements<fifi::binary16>(4));
    }

    {
        SCOPED_TRACE("prime2325");
        EXPECT_EQ(1U, fifi::size_to_elements<fifi::prime2325>(4));
        EXPECT_EQ(2U, fifi::size_to_elements<fifi::prime2325>(8));
    }
}

TEST(test_fifi_utils, length_to_elements)
{
    {
        SCOPED_TRACE("binary");
        EXPECT_EQ(8U, fifi::length_to_elements<fifi::binary>(1));
        EXPECT_EQ(72U, fifi::length_to_elements<fifi::binary>(9));
    }

    {
        SCOPED_TRACE("binary4");
        EXPECT_EQ(2U, fifi::length_to_elements<fifi::binary4>(1));
        EXPECT_EQ(18U, fifi::length_to_elements<fifi::binary4>(9));
    }

    {
        SCOPED_TRACE("binary8");
        EXPECT_EQ(1U, fifi::length_to_elements<fifi::binary8>(1));
        EXPECT_EQ(9U, fifi::length_to_elements<fifi::binary8>(9));
    }

    {
        SCOPED_TRACE("binary16");
        EXPECT_EQ(1U, fifi::length_to_elements<fifi::binary16>(1));
        EXPECT_EQ(9U, fifi::length_to_elements<fifi::binary16>(9));
    }

    {
        SCOPED_TRACE("prime2325");
        EXPECT_EQ(1U, fifi::length_to_elements<fifi::prime2325>(1));
        EXPECT_EQ(9U, fifi::length_to_elements<fifi::prime2325>(9));
    }
}

TEST(test_fifi_utils, set_value_binary)
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

TEST(test_fifi_utils, set_value_binary4)
{
    fifi::binary4::value_type test[2] = { 0, 0 };

    fifi::set_value<fifi::binary4>(&test[0],0,1);
    EXPECT_EQ(1U, test[0]);
    EXPECT_EQ(0U, test[1]);

    fifi::set_value<fifi::binary4>(&test[0],0,0);
    EXPECT_EQ(0U, test[0]);
    EXPECT_EQ(0U, test[1]);

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

    fifi::set_value<fifi::binary4>(&test[0],0,0);
    fifi::set_value<fifi::binary4>(&test[0],1,0);
    fifi::set_value<fifi::binary4>(&test[0],2,0);
    fifi::set_value<fifi::binary4>(&test[0],3,0);
    EXPECT_EQ(0U, test[0]);
    EXPECT_EQ(0U, test[1]);

    fifi::set_value<fifi::binary4>(&test[0],0,15);
    fifi::set_value<fifi::binary4>(&test[0],1,15);
    fifi::set_value<fifi::binary4>(&test[0],2,1);
    EXPECT_EQ(255U, test[0]);
    EXPECT_EQ(1U, test[1]);
}

TEST(test_fifi_utils, set_value_binary8)
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

TEST(test_fifi_utils, set_value_binary16)
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

TEST(test_fifi_utils, set_value_prime2325)
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

TEST(test_fifi_utils, get_value_binary)
{
    fifi::binary::value_type test[2] = { 0, 0 };

    fifi::set_value<fifi::binary>(&test[0],7,1);

    EXPECT_EQ(1U, fifi::get_value<fifi::binary>(&test[0], 7));

    const fifi::binary::value_type* test_const = test;
    EXPECT_EQ(1U, fifi::get_value<fifi::binary>(&test_const[0], 7));
}

TEST(test_fifi_utils, get_value_binary4)
{
    fifi::binary4::value_type test[2] = { 0, 0 };

    fifi::set_value<fifi::binary4>(&test[0], 0, 15);
    EXPECT_EQ(15U, test[0]);
    EXPECT_EQ(15U, fifi::get_value<fifi::binary4>(&test[0], 0));

    fifi::set_value<fifi::binary4>(&test[0], 1, 4);
    EXPECT_EQ(79U, test[0]);
    EXPECT_EQ(4U, fifi::get_value<fifi::binary4>(&test[0], 1));

    const fifi::binary4::value_type* test_const = &test[0];
    EXPECT_EQ(4U, fifi::get_value<fifi::binary4>(&test_const[0],1));
}

TEST(test_fifi_utils, get_value_binary8)
{
    fifi::binary8::value_type test[2] = { 0, 0 };

    fifi::set_value<fifi::binary8>(&test[0], 0, 43U);
    EXPECT_EQ(43U, fifi::get_value<fifi::binary8>(&test[0], 0));

    fifi::set_value<fifi::binary8>(&test[0], 1, 183);
    EXPECT_EQ(183U, fifi::get_value<fifi::binary8>(&test[0], 1));

    const fifi::binary8::value_type* test_const = &test[0];
    EXPECT_EQ(183U, fifi::get_value<fifi::binary8>(&test_const[0],1));
}

TEST(test_fifi_utils, get_value_binary16)
{
    fifi::binary16::value_type test[2] = { 0, 0 };

    fifi::set_value<fifi::binary16>(&test[0], 0, 610);
    EXPECT_EQ(610U, fifi::get_value<fifi::binary16>(&test[0], 0));

    fifi::set_value<fifi::binary16>(&test[0], 1, 1873);
    EXPECT_EQ(1873U, fifi::get_value<fifi::binary16>(&test[0], 1));

    const fifi::binary16::value_type* test_const = &test[0];
    EXPECT_EQ(1873U, fifi::get_value<fifi::binary16>(&test_const[0],1));
}

TEST(test_fifi_utils, swap_values_binary)
{
    fifi::binary::value_type test[2] = { 0x00, 0xff };

    for (uint32_t i = 0; i < 8; ++i)
    {
        fifi::swap_values<fifi::binary>(&test[0], i, i+8);
    }

    EXPECT_EQ(0xff, test[0]);
    EXPECT_EQ(0x00, test[1]);

    const fifi::binary::value_type* test_const = &test[0];
    EXPECT_EQ(0xff, test_const[0]);
    EXPECT_EQ(0x00, test_const[1]);
}

TEST(test_fifi_utils, swap_values_binary4)
{
    fifi::binary4::value_type test[2] = { 0x00, 0xff };

    for (uint32_t i = 0; i < 2; ++i)
    {
        fifi::swap_values<fifi::binary4>(&test[0], i, i+2);
    }

    EXPECT_EQ(0xff, test[0]);
    EXPECT_EQ(0x00, test[1]);

    const fifi::binary4::value_type* test_const = &test[0];
    EXPECT_EQ(0xff, test_const[0]);
    EXPECT_EQ(0x00, test_const[1]);
}

TEST(test_fifi_utils, swap_values_binary8)
{
    fifi::binary8::value_type test[2] = { 0x00, 0xff };

    fifi::swap_values<fifi::binary8>(&test[0], 0, 1);
    EXPECT_EQ(0xff, test[0]);
    EXPECT_EQ(0x00, test[1]);

    const fifi::binary8::value_type* test_const = &test[0];
    EXPECT_EQ(0xff, test_const[0]);
    EXPECT_EQ(0x00, test_const[1]);
}

TEST(test_fifi_utils, pack)
{
    {
        SCOPED_TRACE("binary");
        EXPECT_EQ(0U, fifi::pack<fifi::binary>(0));
        EXPECT_EQ(255U, fifi::pack<fifi::binary>(1));
    }

    {
        SCOPED_TRACE("binary4");
        EXPECT_EQ(0x11, fifi::pack<fifi::binary4>(1));
        EXPECT_EQ(0x22, fifi::pack<fifi::binary4>(2));
        EXPECT_EQ(0x33, fifi::pack<fifi::binary4>(3));
        EXPECT_EQ(0x44, fifi::pack<fifi::binary4>(4));
        EXPECT_EQ(0x55, fifi::pack<fifi::binary4>(5));
        EXPECT_EQ(0x66, fifi::pack<fifi::binary4>(6));
        EXPECT_EQ(0x77, fifi::pack<fifi::binary4>(7));
        EXPECT_EQ(0x88, fifi::pack<fifi::binary4>(8));
        EXPECT_EQ(0x99, fifi::pack<fifi::binary4>(9));
        EXPECT_EQ(0xAA, fifi::pack<fifi::binary4>(10));
        EXPECT_EQ(0xBB, fifi::pack<fifi::binary4>(11));
        EXPECT_EQ(0xCC, fifi::pack<fifi::binary4>(12));
        EXPECT_EQ(0xDD, fifi::pack<fifi::binary4>(13));
        EXPECT_EQ(0xEE, fifi::pack<fifi::binary4>(14));
        EXPECT_EQ(0xFF, fifi::pack<fifi::binary4>(15));
    }

    {
        SCOPED_TRACE("binary8");
        EXPECT_EQ(1U, fifi::pack<fifi::binary8>(1));
        EXPECT_EQ(9U, fifi::pack<fifi::binary8>(9));
    }

    {
        SCOPED_TRACE("binary16");
        EXPECT_EQ(1U, fifi::pack<fifi::binary16>(1));
        EXPECT_EQ(9U, fifi::pack<fifi::binary16>(9));
    }

    {
        SCOPED_TRACE("prime2325");
        EXPECT_EQ(1U, fifi::pack<fifi::prime2325>(1));
        EXPECT_EQ(9U, fifi::pack<fifi::prime2325>(9));
    }
}
