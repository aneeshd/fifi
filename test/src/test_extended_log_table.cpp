// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/extended_log_table.hpp>

#include "helper_test_arithmetic.hpp"
#include "expected_results.hpp"

TEST(TestExtendedLogTable, add)
{
    fifi::check_add<fifi::extended_log_table>();
}

TEST(TestExtendedLogTable, subtract)
{
    fifi::check_subtract<fifi::extended_log_table>();
}

TEST(TestExtendedLogTable, multiply)
{
    fifi::check_multiply<fifi::extended_log_table>();
}

TEST(TestExtendedLogTable, divide)
{
    fifi::check_divide<fifi::extended_log_table>();
}

TEST(TestExtendedLogTable, invert)
{
    fifi::check_invert<fifi::extended_log_table>();
}

TEST(TestExtendedLogTable, random)
{
    fifi::check_random<fifi::extended_log_table>();
}
