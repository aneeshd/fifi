// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/is_packed_constant.hpp>
#include <fifi/prime2325.hpp>

#include <gtest/gtest.h>

template<class Field>
void test_is_packed_constant(typename Field::value_type constant, bool expected)
{
    SCOPED_TRACE(testing::message() << "constant: " << constant);
    EXPECT_EQ(expected, fifi::is_packed_constant<Field>(constant));
}

TEST(TestIsPackedConstant, binary)
{
    test_is_packed_constant<fifi::binary>(0x00, true);
    test_is_packed_constant<fifi::binary>(0xFF, true);
    test_is_packed_constant<fifi::binary>(0xAF, false);
    test_is_packed_constant<fifi::binary>(0xFA, false);
    test_is_packed_constant<fifi::binary>(0x11, false);
    test_is_packed_constant<fifi::binary>(0x22, false);
}

TEST(TestIsPackedConstant, binary4)
{
    test_is_packed_constant<fifi::binary4>(0x00, true);
    test_is_packed_constant<fifi::binary4>(0x11, true);
    test_is_packed_constant<fifi::binary4>(0x22, true);
    test_is_packed_constant<fifi::binary4>(0x33, true);
    test_is_packed_constant<fifi::binary4>(0x44, true);
    test_is_packed_constant<fifi::binary4>(0x55, true);
    test_is_packed_constant<fifi::binary4>(0x66, true);
    test_is_packed_constant<fifi::binary4>(0x77, true);
    test_is_packed_constant<fifi::binary4>(0x88, true);
    test_is_packed_constant<fifi::binary4>(0x99, true);
    test_is_packed_constant<fifi::binary4>(0xAA, true);
    test_is_packed_constant<fifi::binary4>(0xBB, true);
    test_is_packed_constant<fifi::binary4>(0xCC, true);
    test_is_packed_constant<fifi::binary4>(0xDD, true);
    test_is_packed_constant<fifi::binary4>(0xEE, true);
    test_is_packed_constant<fifi::binary4>(0xFF, true);
    test_is_packed_constant<fifi::binary4>(0xF1, false);
    test_is_packed_constant<fifi::binary4>(0xF2, false);
    test_is_packed_constant<fifi::binary4>(0xF3, false);
    test_is_packed_constant<fifi::binary4>(0xF4, false);
    test_is_packed_constant<fifi::binary4>(0xF5, false);
    test_is_packed_constant<fifi::binary4>(0xF6, false);
    test_is_packed_constant<fifi::binary4>(0xF7, false);
    test_is_packed_constant<fifi::binary4>(0xF8, false);
    test_is_packed_constant<fifi::binary4>(0xF9, false);
    test_is_packed_constant<fifi::binary4>(0xFA, false);
    test_is_packed_constant<fifi::binary4>(0xFB, false);
    test_is_packed_constant<fifi::binary4>(0xFC, false);
    test_is_packed_constant<fifi::binary4>(0xFD, false);
    test_is_packed_constant<fifi::binary4>(0xFE, false);
    test_is_packed_constant<fifi::binary4>(0x1F, false);
    test_is_packed_constant<fifi::binary4>(0x2F, false);
    test_is_packed_constant<fifi::binary4>(0x3F, false);
    test_is_packed_constant<fifi::binary4>(0x4F, false);
    test_is_packed_constant<fifi::binary4>(0x5F, false);
    test_is_packed_constant<fifi::binary4>(0x6F, false);
    test_is_packed_constant<fifi::binary4>(0x7F, false);
    test_is_packed_constant<fifi::binary4>(0x8F, false);
    test_is_packed_constant<fifi::binary4>(0x9F, false);
    test_is_packed_constant<fifi::binary4>(0xAF, false);
    test_is_packed_constant<fifi::binary4>(0xBF, false);
    test_is_packed_constant<fifi::binary4>(0xCF, false);
    test_is_packed_constant<fifi::binary4>(0xDF, false);
    test_is_packed_constant<fifi::binary4>(0xEF, false);
    test_is_packed_constant<fifi::binary4>(0xA1, false);
}

TEST(TestIsPackedConstant, binary8)
{
    test_is_packed_constant<fifi::binary8>(0x34, true);
    test_is_packed_constant<fifi::binary8>(0x34, true);
    test_is_packed_constant<fifi::binary8>(0xFF, true);
    test_is_packed_constant<fifi::binary8>(0x00, true);
    test_is_packed_constant<fifi::binary8>(0xFA, true);
}

TEST(TestIsPackedConstant, binary16)
{
    test_is_packed_constant<fifi::binary16>(0x34FA, true);
    test_is_packed_constant<fifi::binary16>(0x34FF, true);
    test_is_packed_constant<fifi::binary16>(0xFFFF, true);
    test_is_packed_constant<fifi::binary16>(0x0000, true);
    test_is_packed_constant<fifi::binary16>(0xFA5D, true);
}

TEST(TestIsPackedConstant, prime2325)
{
    test_is_packed_constant<fifi::prime2325>(0x34FAA5D3, true);
    test_is_packed_constant<fifi::prime2325>(0x34FFFA5D, true);
    test_is_packed_constant<fifi::prime2325>(0xFFFFFFFF, true);
    test_is_packed_constant<fifi::prime2325>(0x00000000, true);
    test_is_packed_constant<fifi::prime2325>(0xFD34A5D3, true);
}
