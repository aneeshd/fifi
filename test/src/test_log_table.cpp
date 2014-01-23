// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/log_table.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>

#include "expected_results.hpp"

template<class Field>
inline void test_log_table()
{
    check_results_multiply<fifi::log_table<Field> >();
    check_results_invert<fifi::log_table<Field> >();
    check_results_divide<fifi::log_table<Field> >();
    check_results_add<fifi::log_table<Field> >();
    check_results_subtract<fifi::log_table<Field> >();
    check_random<fifi::log_table<Field> >();
}

TEST(TestLogTable, api)
{
   test_log_table<fifi::binary4>();
   test_log_table<fifi::binary8>();
   test_log_table<fifi::binary16>();
}
