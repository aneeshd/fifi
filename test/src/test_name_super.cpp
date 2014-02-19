// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>

#include <fifi/name_super.hpp>

#include <gtest/gtest.h>

namespace fifi
{
    namespace
    {
        template<class Super>
        struct test : Super
        {
            uint32_t test_above()
            {
                return Super::func();
            }

            uint32_t test_below()
            {
                return Super::NamedSuper::func();
            }
        };

        template<class Super>
        struct above : Super
        {
            uint32_t func()
            {
                return 1;
            }
        };

        template<class Super>
        struct below : Super
        {
            uint32_t func()
            {
                return 2;
            }
        };

        struct end
        { };

        struct dummy : public
        test<
        above<
        name_super<
        below<end> > > >
        { };
    }
}

TEST(TestNameSuper, name_super)
{
    fifi::dummy stack;
    EXPECT_EQ(stack.test_above(), 1);
    EXPECT_EQ(stack.test_below(), 2);
    EXPECT_EQ(stack.func(), 1);
}
