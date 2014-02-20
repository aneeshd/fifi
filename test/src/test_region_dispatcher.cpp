// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/final.hpp>
#include <fifi/region_dispatcher.hpp>
#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>

#include <gtest/gtest.h>
#include <sak/aligned_allocator.hpp>


namespace fifi
{

    namespace
    {

        template<class Field, bool Enabled>
        class dummy_optimization
        {
        public:

            typedef Field field_type;
            typedef typename field_type::value_type value_type;

        public:

            void region_multiply_constant(value_type* dest, value_type constant,
                uint32_t length) const
            {
                (void) dest;
                (void) constant;
                (void) length;
                EXPECT_TRUE(Enabled);
            }

            uint32_t alignment() const
            {
                return 3U;
            }

            uint32_t max_alignment() const
            {
                return 30U;
            }

            uint32_t granularity() const
            {
                return 4U;
            }

            uint32_t max_granularity() const
            {
                return 40U;
            }



            bool enabled() const
            {
                return Enabled;
            }
        };

        template<class Field, bool Enabled>
        class dummy_base
        {
        public:

            typedef Field field_type;
            typedef typename field_type::value_type value_type;

        public:

            void region_multiply_constant(
                value_type* dest, value_type constant, uint32_t length) const
            {
                (void) dest;
                (void) constant;
                (void) length;
                EXPECT_TRUE(Enabled);
            }

            uint32_t alignment() const
            {
                return 1U;
            }

            uint32_t max_alignment() const
            {
                return 10U;
            }

            uint32_t granularity() const
            {
                return 2U;
            }

            uint32_t max_granularity() const
            {
                return 20U;
            }
        };

        class dummy_stack_enabled :
            public region_dispatcher<
                       binary,
                       dummy_optimization<binary, true>,
                       binary,
                   dummy_base<binary, false> >
        { };

        class dummy_stack_disabled1 :
            public region_dispatcher<
                        binary,
                        dummy_optimization<binary, false>,
                        binary,
                   dummy_base<binary, true> >
        { };

        class dummy_stack_disabled2 :
            public region_dispatcher<
                       binary,
                       dummy_optimization<binary, false>,
                       binary16,
                   dummy_base<binary, true> >
        { };
    }
}

TEST(TestRegionDispatcher, alignment)
{
    fifi::dummy_stack_enabled enabled_stack;
    fifi::dummy_stack_disabled1 disabled_stack1;
    fifi::dummy_stack_disabled2 disabled_stack2;

    EXPECT_EQ(disabled_stack1.alignment(), 1U);
    EXPECT_EQ(disabled_stack2.alignment(), 1U);
    EXPECT_EQ(enabled_stack.alignment(), 3U);
}

TEST(TestRegionDispatcher, max_alignment)
{
    fifi::dummy_stack_enabled enabled_stack;
    fifi::dummy_stack_disabled1 disabled_stack1;
    fifi::dummy_stack_disabled2 disabled_stack2;

    EXPECT_EQ(disabled_stack1.max_alignment(), 10U);
    EXPECT_EQ(disabled_stack2.max_alignment(), 10U);
    EXPECT_EQ(enabled_stack.max_alignment(), 30U);
}

TEST(TestRegionDispatcher, granularity)
{
    fifi::dummy_stack_enabled enabled_stack;
    fifi::dummy_stack_disabled1 disabled_stack1;
    fifi::dummy_stack_disabled2 disabled_stack2;

    EXPECT_EQ(disabled_stack1.granularity(), 2U);
    EXPECT_EQ(disabled_stack2.granularity(), 2U);
    EXPECT_EQ(enabled_stack.granularity(), 4U);
}

TEST(TestRegionDispatcher, max_granularity)
{
    fifi::dummy_stack_enabled enabled_stack;
    fifi::dummy_stack_disabled1 disabled_stack1;
    fifi::dummy_stack_disabled2 disabled_stack2;

    EXPECT_EQ(disabled_stack1.max_granularity(), 20U);
    EXPECT_EQ(disabled_stack2.max_granularity(), 20U);
    EXPECT_EQ(enabled_stack.max_granularity(), 40U);
}

TEST(TestRegionDispatcher, region_multiply_constant)
{
    fifi::dummy_stack_enabled enabled_stack;
    fifi::dummy_stack_disabled1 disabled_stack1;
    fifi::dummy_stack_disabled2 disabled_stack2;

    uint32_t length = 1;
    std::vector<uint8_t> dest(length);
    uint8_t constant = 255;


    enabled_stack.region_multiply_constant(dest.data(),constant,length);
    disabled_stack1.region_multiply_constant(dest.data(),constant,length);
    disabled_stack2.region_multiply_constant(dest.data(),constant,length);
}
