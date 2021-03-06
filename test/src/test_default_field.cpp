// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <type_traits>

#include <fifi/default_field.hpp>
#include <fifi/extended_log_table.hpp>
#include <fifi/full_table.hpp>
#include <fifi/optimal_prime.hpp>
#include <fifi/simple_online.hpp>

#include <gtest/gtest.h>

TEST(test_default_field, binary_default_field)
{
    bool test= std::is_same<
        fifi::default_field<fifi::binary>::type,
        fifi::simple_online<fifi::binary> >::value;

    EXPECT_TRUE(test);
}

TEST(test_default_field, binary4_default_field)
{
    bool test= std::is_same<
        fifi::default_field<fifi::binary4>::type,
        fifi::full_table<fifi::binary4> >::value;

    EXPECT_TRUE(test);
}

TEST(test_default_field, binary8_default_field)
{
    bool test= std::is_same<
        fifi::default_field<fifi::binary8>::type,
        fifi::full_table<fifi::binary8> >::value;

    EXPECT_TRUE(test);
}

TEST(test_default_field, binary16_default_field)
{
    bool test= std::is_same<
        fifi::default_field<fifi::binary16>::type,
        fifi::extended_log_table<fifi::binary16> >::value;

    EXPECT_TRUE(test);
}

TEST(test_default_field, prime2325_default_field)
{
    bool test= std::is_same<
        fifi::default_field<fifi::prime2325>::type,
        fifi::optimal_prime<fifi::prime2325> >::value;

    EXPECT_TRUE(test);
}
