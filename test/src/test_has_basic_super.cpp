// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/has_basic_super.hpp>
#include <fifi/full_table.hpp>

namespace fifi
{
    // Put dummy layers and tests classes in an anonymous namespace
    // to avoid violations of ODF (one-definition-rule) in other
    // translation units
    namespace
    {
        struct dummy_stack1
        { };

        struct dummy_stack2
        {
            typedef dummy_stack1 BasicSuper;
        };
    }
}

TEST(TestHasBasicSuper, api)
{
    EXPECT_FALSE(fifi::has_basic_super<fifi::dummy_stack1>::value);
    EXPECT_TRUE(fifi::has_basic_super<fifi::dummy_stack2>::value);

    EXPECT_TRUE(fifi::has_basic_super<fifi::full_table<fifi::binary4>>::value);
    EXPECT_TRUE(fifi::has_basic_super<fifi::full_table<fifi::binary8>>::value);
    EXPECT_FALSE(fifi::has_basic_super<uint32_t>::value);
}
