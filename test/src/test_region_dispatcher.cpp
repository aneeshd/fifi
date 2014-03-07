// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/binary.hpp>
#include <fifi/region_dispatcher.hpp>
#include "fifi_unit_test/helper_fall_through.hpp"
#include "fifi_unit_test/helper_region_info.hpp"

namespace fifi
{
    namespace
    {
        template<bool Enabled, class Super>
        class dummy : public Super
        {
        public:

            bool enabled() const
            {
                return Enabled;
            }
        };

        class dummy_stack :
            public region_dispatcher<
                   helper_region_info<
                       /*alignment=*/2U,
                       /*max_alignment=*/20U,
                       /*granularity=*/4U,
                       /*max_granularity=*/40U,
                   dummy<true,
                   helper_fall_through<binary> > >,
                   helper_region_info<
                       /*alignment=*/1U,
                       /*max_alignment=*/10U,
                       /*granularity=*/3U,
                       /*max_granularity=*/30U,
                   helper_fall_through<binary> > >
        { };
    }
}

TEST(test_region_dispatcher, test_region_dispatcher)
{
    fifi::dummy_stack stack;
    fifi::dummy_stack::BasicSuper& basic = stack;
    fifi::dummy_stack::OptimizedSuper& optimized = stack;

    EXPECT_EQ(basic.alignment(), 1U);
    EXPECT_EQ(basic.granularity(), 3U);
    EXPECT_EQ(basic.max_alignment(), 10U);
    EXPECT_EQ(basic.max_granularity(), 30U);
    EXPECT_EQ(optimized.alignment(), 2U);
    EXPECT_EQ(optimized.granularity(), 4U);
    EXPECT_EQ(optimized.max_alignment(), 20U);
    EXPECT_EQ(optimized.max_granularity(), 40U);
    EXPECT_EQ(stack.alignment(), 2U);
    EXPECT_EQ(stack.granularity(), 4U);
    EXPECT_EQ(stack.max_alignment(), 20U);
    EXPECT_EQ(stack.max_granularity(), 40U);
}
