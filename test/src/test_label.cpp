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
/*
        struct dummy
        {
            template<uint32_t N>
            const dummy& get_this() const
            {
                std::cout << "ASSERT" << std::endl;
                assert(0);
                return *this;
            }
        };

        template<class Super>
        class test1 : public Super
        {
        public:
            uint32_t test() const
            {
                std::cout << "test:1" << std::endl;
                return 1;
            }
        };

        template<class Super>
        class test2 : public Super
        {
        public:
            uint32_t test() const
            {
                std::cout << "test:2" << std::endl;
                return 2;
            }
        };

        template<uint32_t Label, class Super>
        class the_goto : public Super
        {
        public:
            uint32_t test(bool jump) const
            {
                std::cout << "test jmp" << std::endl;
                if(jump)
                {
                    std::cout << "jmp" << std::endl;
                    return Super::template get_this<Label>().test();
                    //Super::test();
                }
                else
                {
                    std::cout << "no jmp" << std::endl;
                    return Super::test();
                }
            }
        };

        class my_stack : public
            the_goto<1,
            test2<
            label<1,
            test1<
            dummy> > > >
        {

        };
*/
    struct dummy
    {

        template<uint32_t SuperLabel>
        const dummy& get_this() const
        {
            assert(false);
            return *this;
        }

        void print() const
        {
            std::cout << "hello in dummy " << std::endl;
        }
    };

    class test : public label<2, label<4, dummy> >
    { };
    }
}

TEST(TestLabel, label)
{
    /*
    fifi::my_stack s;
    std::cout << "test1" << std::endl;
    EXPECT_EQ(1, s.test(true));
    std::cout << "test2" << std::endl;
    EXPECT_EQ(2, s.test(false));
    */
    fifi::test t;
    t.get_this<4>().print();
    t.get_this<2>().print();
}
