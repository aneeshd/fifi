// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/full_table.hpp>

#include <gtest/gtest.h>

#include "helper_test_arithmetic.hpp"
#include "helper_test_packed_arithmetic.hpp"
#include "helper_test_region_arithmetic.hpp"

TEST(test_full_table, binary4)
{
    fifi::check_all<fifi::full_table<fifi::binary4>>();
}

TEST(test_full_table, binary8)
{
    fifi::check_all<fifi::full_table<fifi::binary8>>();
}

TEST(test_full_table, packed_binary4)
{
    fifi::check_packed_all<fifi::full_table<fifi::binary4>>();
}

TEST(test_full_table, packed_binary8)
{
    fifi::check_packed_all<fifi::full_table<fifi::binary8>>();
}

TEST(test_full_table, region_binary4)
{
    fifi::check_region_all<fifi::full_table<fifi::binary4>>();
}

TEST(test_full_table, region_binary8)
{
    fifi::check_region_all<fifi::full_table<fifi::binary8>>();
}
