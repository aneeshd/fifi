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

            static uint32_t alignment()
            {
                return 3U;
            }

            static uint32_t max_alignment()
            {
                return 30U;
            }

            static uint32_t granularity()
            {
                return 4U;
            }

            static uint32_t max_granularity()
            {
                return 40U;
            }

            static bool enabled()
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

            static uint32_t alignment()
            {
                return 1U;
            }

            static uint32_t max_alignment()
            {
                return 10U;
            }

            static uint32_t granularity()
            {
                return 2U;
            }

            static uint32_t max_granularity()
            {
                return 20U;
            }
        };

        class dummy_stack_enabled :
            public region_dispatcher<dummy_optimization<binary, true>,
                   dummy_base<binary, false> >
        { };

        class dummy_stack_disabled :
            public region_dispatcher<dummy_optimization<binary, false>,
                   dummy_base<binary, true> >
        { };
    }
}

TEST(TestRegionDispatcher, alignment)
{
    fifi::dummy_stack_disabled disabled_stack;
    fifi::dummy_stack_enabled enabled_stack;

    EXPECT_EQ(disabled_stack.alignment(), 1U);
    EXPECT_EQ(enabled_stack.alignment(), 3U);
}

TEST(TestRegionDispatcher, max_alignment)
{
    fifi::dummy_stack_disabled disabled_stack;
    fifi::dummy_stack_enabled enabled_stack;

    EXPECT_EQ(disabled_stack.max_alignment(), 10U);
    EXPECT_EQ(enabled_stack.max_alignment(), 30U);
}

TEST(TestRegionDispatcher, granularity)
{
    fifi::dummy_stack_disabled disabled_stack;
    fifi::dummy_stack_enabled enabled_stack;

    EXPECT_EQ(disabled_stack.granularity(), 2U);
    EXPECT_EQ(enabled_stack.granularity(), 4U);
}

TEST(TestRegionDispatcher, max_granularity)
{
    fifi::dummy_stack_disabled disabled_stack;
    fifi::dummy_stack_enabled enabled_stack;

    EXPECT_EQ(disabled_stack.max_granularity(), 20U);
    EXPECT_EQ(enabled_stack.max_granularity(), 40U);
}

TEST(TestRegionDispatcher, region_multiply_constant)
{
    fifi::dummy_stack_enabled enabled_stack;
    fifi::dummy_stack_disabled disabled_stack;

    uint32_t length = 1;
    std::vector<uint8_t> dest(length);
    uint8_t constant = 255;


    disabled_stack.region_multiply_constant(dest.data(),constant,length);
    enabled_stack.region_multiply_constant(dest.data(),constant,length);
}
