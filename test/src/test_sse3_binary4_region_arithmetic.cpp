// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/sse3_binary4_region_arithmetic.hpp>

#include <gtest/gtest.h>

#include "helper_test_arithmetic.hpp"
#include "helper_test_packed_arithmetic.hpp"
#include "helper_test_region_arithmetic.hpp"


// TEST(TestSSE3Binary4RegionArithmetic, region_add)
// {
//     fifi::check_region_add<fifi::sse3_binary4_region_arithmetic>();
// }

// TEST(TestSSE3Binary4RegionArithmetic, region_subtract)
// {
//     fifi::check_region_subtract<fifi::sse3_binary4_region_arithmetic>();
// }

// TEST(TestSSE3Binary4RegionArithmetic, region_multiply)
// {
//     fifi::check_region_multiply<fifi::sse3_binary4_region_arithmetic>();
// }

// TEST(TestSSE3Binary4RegionArithmetic, region_divide)
// {
//     fifi::check_region_divide<fifi::sse3_binary4_region_arithmetic>();
// }

TEST(TestSSE3Binary4RegionArithmetic, region_multiply_constant)
{
    check_results_region_multiply_constant<
        fifi::sse3_binary4_region_arithmetic>();

    check_results_region_multiply_constant<
        fifi::sse3_binary4_region_arithmetic>();

        check_results_region_multiply_constant<
        fifi::sse3_binary4_region_arithmetic>();
    check_results_region_multiply_constant<
        fifi::sse3_binary4_region_arithmetic>();
    check_results_region_multiply_constant<
        fifi::sse3_binary4_region_arithmetic>();
    check_results_region_multiply_constant<
        fifi::sse3_binary4_region_arithmetic>();
    check_results_region_multiply_constant<
        fifi::sse3_binary4_region_arithmetic>();

}

// TEST(TestSSE3Binary4RegionArithmetic, region_multiply_add)
// {
//     fifi::check_region_multiply_add<fifi::sse3_binary4_region_arithmetic>();
// }

// TEST(TestSSE3Binary4RegionArithmetic, region_multiply_subtract)
// {
//     fifi::check_region_multiply_subtract<fifi::sse3_binary4_region_arithmetic>();
// }
