// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/extended_log_table.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>

#include "expected_results.hpp"

template<class Field>
inline void test_extended_log_table()
{
    check_results_multiply<fifi::extended_log_table<Field> >();
    check_results_invert<fifi::extended_log_table<Field> >();
    check_results_divide<fifi::extended_log_table<Field> >();
    check_results_add<fifi::extended_log_table<Field> >();
    check_results_subtract<fifi::extended_log_table<Field> >();
    check_random<fifi::extended_log_table<Field> >();
}

TEST(TestExtendedLogTable, api)
{
   test_extended_log_table<fifi::binary4>();
   test_extended_log_table<fifi::binary8>();
   test_extended_log_table<fifi::binary16>();
}
