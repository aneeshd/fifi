// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/binary.hpp>
#include <fifi/region_dispatcher.hpp>
#include "helper_fall_through.hpp"

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
            uint32_t MaxGranularity,
            class Super
        >
        class dummy : public Super
        {
        public:

            typedef Field field_type;
            typedef typename field_type::value_type value_type;

        public:

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

        class dummy_stack :
            public region_dispatcher<
                       dummy<binary, true, 2U, 20U, 4U, 40U, helper_fall_through<binary>>,
                   dummy<binary, false,  1U, 10U, 3U, 30U,
                       helper_fall_through<binary>>
                   >
        { };
    }
}

TEST(TestRegionDispatcher, test_region_dispatcher)
{
    fifi::dummy_stack stack;
    fifi::dummy_stack::BasicSuper& basic = stack;
    fifi::dummy_stack::OptimizedSuper& optimized = stack;

    EXPECT_TRUE(stack.enabled());
    EXPECT_TRUE(optimized.enabled());
    EXPECT_FALSE(basic.enabled());
}
