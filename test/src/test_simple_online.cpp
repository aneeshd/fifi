// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/simple_online.hpp>

#include <gtest/gtest.h>

#include "fifi_unit_test/helper_test_arithmetic.hpp"
#include "fifi_unit_test/helper_test_packed_arithmetic.hpp"
#include "fifi_unit_test/helper_test_region_arithmetic.hpp"

TEST(test_simple_online, add)
{
    fifi::check_add<fifi::simple_online>();
}

TEST(test_simple_online, subtract)
{
    fifi::check_subtract<fifi::simple_online>();
}

TEST(test_simple_online, multiply)
{
    fifi::check_multiply<fifi::simple_online>();
}

TEST(test_simple_online, divide)
{
    fifi::check_divide<fifi::simple_online>();
}

TEST(test_simple_online, invert)
{
    fifi::check_invert<fifi::simple_online>();
}

TEST(test_simple_online, random)
{
    fifi::check_random<fifi::simple_online>();
}

TEST(test_simple_online, packed_add)
{
    fifi::check_packed_add<fifi::simple_online>();
}

TEST(test_simple_online, packed_subtract)
{
    fifi::check_packed_subtract<fifi::simple_online>();
}

TEST(test_simple_online, packed_multiply)
{
    fifi::check_packed_multiply<fifi::simple_online>();
}

TEST(test_simple_online, packed_divide)
{
    fifi::check_packed_divide<fifi::simple_online>();
}

TEST(test_simple_online, packed_invert)
{
    fifi::check_packed_invert<fifi::simple_online>();
}

TEST(test_simple_online, region_add)
{
    fifi::check_region_add<fifi::simple_online>();
}

TEST(test_simple_online, region_subtract)
{
    fifi::check_region_subtract<fifi::simple_online>();
}

TEST(test_simple_online, region_multiply)
{
    fifi::check_region_multiply<fifi::simple_online>();
}

TEST(test_simple_online, region_divide)
{
    fifi::check_region_divide<fifi::simple_online>();
}

TEST(test_simple_online, region_multiply_constant)
{
    fifi::check_region_multiply_constant<fifi::simple_online>();
}

TEST(test_simple_online, region_multiply_add)
{
    fifi::check_region_multiply_add<fifi::simple_online>();
}

TEST(test_simple_online, region_multiply_subtract)
{
    fifi::check_region_multiply_subtract<fifi::simple_online>();
}
