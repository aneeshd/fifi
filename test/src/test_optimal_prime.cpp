// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/optimal_prime.hpp>
#include <fifi/prime2325.hpp>

#include <gtest/gtest.h>

#include "fifi_unit_test/helper_test_arithmetic.hpp"
#include "fifi_unit_test/helper_test_packed_arithmetic.hpp"
#include "fifi_unit_test/helper_test_region_arithmetic.hpp"

TEST(test_optimal_prime, prime2325)
{
    fifi::check_all<fifi::optimal_prime<fifi::prime2325> >();
}

TEST(test_log_table, packed_prime2325)
{
    fifi::check_packed_all<fifi::optimal_prime<fifi::prime2325>>();
}

TEST(test_log_table, region_prime2325)
{
    fifi::check_region_all<fifi::optimal_prime<fifi::prime2325>>();
}
