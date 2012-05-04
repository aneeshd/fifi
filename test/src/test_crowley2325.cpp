// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/optimal_prime.h>
#include <fifi/field_types.h>
#include <fifi/crowley2325.h>



TEST(test_crowley2325, max_block_size)
{
    fifi::crowley2325 mapping;

    EXPECT_EQ(mapping.max_block_size(), 2147483644U);

}

TEST(test_crowley2325, find_prefix)
{
}

// 2^31 - 1 is also good
// 0111 1111 1111 1111 1111 1111 1111 1111
//
//
// a, b and a xor b
//
// 1000 0001 1001
// 0000 0001


