// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/label.hpp>

#include <gtest/gtest.h>

#include <iostream>

namespace fifi
{
    namespace
    {

        struct final
        { };

        template<class Super>
        class test1 : public Super
        {
        public:
            uint32_t test() const
            {
                return 1;
            }
        };

        template<class Super>
        class test2 : public Super
        {
        public:
            uint32_t test() const
            {
                return 2;
            }
        };

        template<class Super>
        class test3 : public Super
        {
        public:
            uint32_t test() const
            {
                return 3;
            }
        };

        template<class Super>
        class test4 : public Super
        {
        public:
            uint32_t test() const
            {
                return 4;
            }
        };

        template<uint32_t Label, class Super>
        class goto1 : public Super
        {
        public:
            uint32_t run1(bool jump) const
            {
                if(jump)
                {
                    return Super::template get_label<Label>().test();
                }
                else
                {
                    return Super::test();
                }
            }
        };

        template<uint32_t Label, class Super>
        class goto2 : public Super
        {
        public:
            uint32_t run2(bool jump) const
            {
                if(jump)
                {
                    return Super::template get_label<Label>().test();
                }
                else
                {
                    return Super::test();
                }
            }
        };

        class dummy_stack : public
            goto2<2,
            test4<
            goto1<1,
            test3<
            label<1,
            test2<
            label<2,
            test1<
            final> > > > > > > >
        { };
    }
}

TEST(TestLabel, label)
{
    fifi::dummy_stack stack;
    EXPECT_EQ(3, stack.run1(false));
    EXPECT_EQ(2, stack.run1(true));
    EXPECT_EQ(4, stack.run2(false));
    EXPECT_EQ(1, stack.run2(true));
}
