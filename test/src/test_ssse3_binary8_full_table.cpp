// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <cpuid/cpuinfo.hpp>

#include <fifi/ssse3_binary8_full_table.hpp>

#include "helper_test_arithmetic.hpp"
#include "helper_test_packed_arithmetic.hpp"
#include "helper_test_region_arithmetic.hpp"


TEST(TestSSSE3Binary8FullTable, region_add)
{
    fifi::ssse3_binary8_full_table stack;
    if (stack.enabled())
    {
        check_results_region_add<fifi::ssse3_binary8_full_table>();
    }
}

TEST(TestSSSE3Binary8FullTable, region_subtract)
{
    fifi::ssse3_binary8_full_table stack;
    if (stack.enabled())
    {
        check_results_region_subtract<fifi::ssse3_binary8_full_table>();
    }
}

TEST(TestSSSE3Binary8FullTable, region_multiply_constant)
{
    fifi::ssse3_binary8_full_table stack;
    if (stack.enabled())
    {
        check_results_region_multiply_constant<
            fifi::ssse3_binary8_full_table>();
    }
}

TEST(TestSSSE3Binary8FullTable, region_multiply_add)
{
    fifi::ssse3_binary8_full_table stack;
    if (stack.enabled())
    {
        check_results_region_multiply_add<
            fifi::ssse3_binary8_full_table>();
    }
}

TEST(TestSSSE3Binary8FullTable, region_multiply_subtract)
{
    fifi::ssse3_binary8_full_table stack;
    if (stack.enabled())
    {
        check_results_region_multiply_subtract<
            fifi::ssse3_binary8_full_table>();
    }
}
