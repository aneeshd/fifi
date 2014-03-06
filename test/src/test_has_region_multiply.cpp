// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/has_region_multiply.hpp>
#include <fifi/full_table.hpp>
#include <fifi/simple_online.hpp>

namespace fifi
{
    // Put dummy layers and tests classes in an anonymous namespace
    // to avoid violations of ODF (one-definition-rule) in other
    // translation units
    namespace
    {
        struct dummy_stack
        { };
    }
}

TEST(TestHasRegionMultiply, api)
{
    EXPECT_FALSE(fifi::has_region_multiply<fifi::dummy_stack>::value);

    EXPECT_TRUE(fifi::has_region_multiply<
                    fifi::simple_online<fifi::binary>>::value);

    EXPECT_TRUE(fifi::has_region_multiply<
                    fifi::full_table<fifi::binary8>>::value);

    EXPECT_FALSE(fifi::has_region_multiply<uint32_t>::value);
}



