// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/label.hpp>
#include <fifi/final_label.hpp>

#include <gtest/gtest.h>

#include <iostream>

namespace fifi
{
    namespace
    {
        struct final
        { };

        template<class Super>
        struct test1 : Super
        {
            uint32_t test() const
            {
                return 1;
            }
        };

        template<class Super>
        struct test2 : Super
        {
            uint32_t test() const
            {
                return 2;
            }
        };

        template<class Super>
        struct test3 : Super
        {
            uint32_t test() const
            {
                return 3;
            }
        };

        template<class Super>
        struct test4 : Super
        {
            uint32_t test() const
            {
                return 4;
            }
        };

        template<uint32_t Label, class Super>
        struct dummy1_or_goto : Super
        {
            uint32_t goto1(bool jump) const
            {
                if (jump)
                    return Super::template get_label<Label>().test();
                else
                    return Super::test();
            }
        };

        template<uint32_t Label, class Super>
        struct dummy2_or_goto : Super
        {
            uint32_t goto2(bool jump) const
            {
                if (jump)
                    return Super::template get_label<Label>().test();
                else
                    return Super::test();
            }
        };

        class dummy_stack : public
            dummy2_or_goto<2,
            test4<
            dummy1_or_goto<1,
            test3<
            label<1,
            test2<
            label<2,
            test1<
            final_label<final>> > > > > > > >
        { };
    }
}

TEST(TestLabel, label)
{
    fifi::dummy_stack stack;
    EXPECT_EQ(3U, stack.goto1(false));
    EXPECT_EQ(2U, stack.goto1(true));
    EXPECT_EQ(4U, stack.goto2(false));
    EXPECT_EQ(1U, stack.goto2(true));
}
