// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/log_table.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>

#include "helper_test_arithmetic.hpp"

TEST(TestLogTable, binary4)
{
    fifi::check_all<fifi::log_table<fifi::binary4> >();
}

TEST(TestLogTable, binary8)
{
    fifi::check_all<fifi::log_table<fifi::binary8> >();
}

TEST(TestLogTable, binary16)
{
    fifi::check_all<fifi::log_table<fifi::binary16> >();
}
