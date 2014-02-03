// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>
#include <vector>

#include <fifi/prime2325.hpp>
#include <fifi/prime2325_apply_prefix.hpp>

#include <gtest/gtest.h>

#include <sak/storage.hpp>


TEST(TestPrime2325ApplyPrefix, prime2325_apply_prefix)
{
    uint32_t tests = 10;
    std::vector<uint32_t> data(tests);

    for (uint32_t i = 0; i < tests; ++i)
    {
        data[i] = rand() % fifi::prime2325::order;
    }

    uint32_t prefix = rand() % fifi::prime2325::order;

    SCOPED_TRACE(prefix);

    std::vector<uint32_t> original_data = data;

    fifi::apply_prefix(sak::storage(data), prefix);

    for (uint32_t i = 0; i < 10; ++i)
    {
        SCOPED_TRACE(original_data[i]);
        EXPECT_EQ(data[i], original_data[i] ^ prefix);
    }
}
