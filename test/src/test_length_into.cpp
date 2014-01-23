// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/length_into.hpp>

namespace fifi
{

    // Put dummy layers and tests classes in an anonymous namespace
    // to avoid violations of ODF (one-definition-rule) in other
    // translation units
    namespace
    {

        template<class Super>
        struct dummy_super : Super
        { };

        struct dummy_final
        { };
    }
}

TEST(TestLengthInto, api)
{
    fifi::dummy_super<fifi::length_into<fifi::dummy_final>> stack;

    for(uint32_t i = 0; i < 10; ++i)
    {
        stack.set_length(i);
        EXPECT_EQ(i, stack.length());
    }
}
