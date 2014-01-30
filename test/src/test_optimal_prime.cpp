// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/optimal_prime.hpp>
#include <fifi/prime2325.hpp>

#include "helper_test_arithmetic.hpp"

TEST(TestOptimalPrime, prime2325)
{
    fifi::check_all<fifi::optimal_prime<fifi::prime2325> >();
}
