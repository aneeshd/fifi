// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/extended_log_table.hpp>

#include "helper_test_arithmetic.hpp"

#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>


TEST(TestExtendedLogTable, binary4)
{
    fifi::check_all<fifi::extended_log_table<fifi::binary4>>();
}

TEST(TestExtendedLogTable, binary8)
{
    fifi::check_all<fifi::extended_log_table<fifi::binary8>>();
}

TEST(TestExtendedLogTable, binary16)
{
    fifi::check_all<fifi::extended_log_table<fifi::binary16>>();
}
