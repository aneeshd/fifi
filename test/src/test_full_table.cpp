// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/full_table.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>

#include "helper_test_arithmetic.hpp"
#include "helper_test_packed_arithmetic.hpp"
#include "helper_test_region_arithmetic.hpp"

TEST(TestFullTable, binary4)
{
    fifi::check_all<fifi::full_table<fifi::binary4>>();
}

TEST(TestFullTable, binary8)
{
    fifi::check_all<fifi::full_table<fifi::binary8>>();
}

TEST(TestFullTable, packed_binary4)
{
    fifi::check_packed_all<fifi::full_table<fifi::binary4>>();
}

TEST(TestFullTable, packed_binary8)
{
    fifi::check_packed_all<fifi::full_table<fifi::binary8>>();
}

TEST(TestFullTable, region_binary4)
{
    fifi::check_region_all<fifi::full_table<fifi::binary4>>();
}

TEST(TestFullTable, region_binary8)
{
    fifi::check_region_all<fifi::full_table<fifi::binary8>>();
}
