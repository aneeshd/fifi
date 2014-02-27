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

        template
        <
            class Field,
            bool Enabled,
            uint32_t Alignment,
            uint32_t MaxAlignment,
            uint32_t Granularity,
            uint32_t MaxGranularity
        >
        class dummy
        {
        public:

            typedef Field field_type;
            typedef typename field_type::value_type value_type;

        public:

            void region_add(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                (void) dest;
                (void) src;
                (void) length;
                EXPECT_TRUE(Enabled);
            }

            void region_subtract(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                (void) dest;
                (void) src;
                (void) length;
                EXPECT_TRUE(Enabled);
            }

            void region_multiply(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                (void) dest;
                (void) src;
                (void) length;
                EXPECT_TRUE(Enabled);
            }

            void region_divide(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                (void) dest;
                (void) src;
                (void) length;
                EXPECT_TRUE(Enabled);
            }

            void region_multiply_constant(value_type* dest, value_type constant,
                uint32_t length) const
            {
                (void) dest;
                (void) constant;
                (void) length;
                EXPECT_TRUE(Enabled);
            }

            void region_multiply_add(value_type* dest, const value_type* src,
                                     value_type constant,
                                     uint32_t length) const
            {
                (void) dest;
                (void) src;
                (void) constant;
                (void) length;
                EXPECT_TRUE(Enabled);
            }

            void region_multiply_subtract(value_type* dest,
                const value_type* src, value_type constant,
                uint32_t length) const
            {
                (void) dest;
                (void) src;
                (void) constant;
                (void) length;
                EXPECT_TRUE(Enabled);
            }

            static uint32_t alignment()
            {
                return Alignment;
            }

            static uint32_t max_alignment()
            {
                return MaxAlignment;
            }

            static uint32_t granularity()
            {
                return Granularity;
            }

            static uint32_t max_granularity()
            {
                return MaxGranularity;
            }

            static bool enabled()
            {
                return Enabled;
            }
        };

        class dummy_stack_enabled :
            public region_dispatcher<dummy<
                         binary, true,  2U, 20U, 4U, 40U>,
                   dummy<binary, false, 1U, 10U, 3U, 30U> >
        { };

        class dummy_stack_disabled :
            public region_dispatcher<dummy<
                         binary, false, 2U, 20U, 4U, 40U>,
                   dummy<binary, true,  1U, 10U, 3U, 30U> >
        { };
    }
}

TEST(TestRegionDispatcher, alignment)
{
    fifi::dummy_stack_disabled disabled_stack;
    fifi::dummy_stack_enabled enabled_stack;

    EXPECT_EQ(disabled_stack.alignment(), 1U);
    EXPECT_EQ(enabled_stack.alignment(), 2U);
}

TEST(TestRegionDispatcher, max_alignment)
{
    fifi::dummy_stack_disabled disabled_stack;
    fifi::dummy_stack_enabled enabled_stack;

    EXPECT_EQ(disabled_stack.max_alignment(), 10U);
    EXPECT_EQ(enabled_stack.max_alignment(), 20U);
}

TEST(TestRegionDispatcher, granularity)
{
    fifi::dummy_stack_disabled disabled_stack;
    fifi::dummy_stack_enabled enabled_stack;

    EXPECT_EQ(disabled_stack.granularity(), 3U);
    EXPECT_EQ(enabled_stack.granularity(), 4U);
}

TEST(TestRegionDispatcher, max_granularity)
{
    fifi::dummy_stack_disabled disabled_stack;
    fifi::dummy_stack_enabled enabled_stack;

    EXPECT_EQ(disabled_stack.max_granularity(), 30U);
    EXPECT_EQ(enabled_stack.max_granularity(), 40U);
}

TEST(TestRegionDispatcher, region_multiply_constant)
{
    fifi::dummy_stack_enabled enabled_stack;
    fifi::dummy_stack_disabled disabled_stack;

    uint32_t length = 1;
    std::vector<uint8_t> dest(length);
    std::vector<uint8_t> src(length);
    uint8_t constant = 255;

    disabled_stack.region_add(dest.data(), src.data(), length);
    disabled_stack.region_subtract(dest.data(), src.data(), length);
    disabled_stack.region_multiply(dest.data(), src.data(), length);
    disabled_stack.region_divide(dest.data(), src.data(), length);
    disabled_stack.region_multiply_constant(dest.data(), constant, length);
    disabled_stack.region_multiply_add(dest.data(), src.data(), constant,
        length);
    disabled_stack.region_multiply_subtract(dest.data(), src.data(), constant,
        length);

    enabled_stack.region_add(dest.data(), src.data(), length);
    enabled_stack.region_subtract(dest.data(), src.data(), length);

    /// @todo enable this when we've fixed the problem in the dispatcher.
    //enabled_stack.region_multiply(dest.data(), src.data(), length);
    //enabled_stack.region_divide(dest.data(), src.data(), length);

    enabled_stack.region_multiply_constant(dest.data(), constant, length);
    enabled_stack.region_multiply_add(dest.data(), src.data(), constant,
        length);
    enabled_stack.region_multiply_subtract(dest.data(), src.data(), constant,
        length);
}
