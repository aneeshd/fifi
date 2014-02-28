// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/binary.hpp>
#include <fifi/region_dispatcher.hpp>
#include "helper_fall_through.hpp"
#include "helper_region_info.hpp"

namespace fifi
{
    namespace
    {
        template<bool Enabled, class Super>
        class dummy : public Super
        {
        public:
            static bool enabled()
            {
                return Enabled;
            }
        };

        class dummy_stack :
            public region_dispatcher<
                       helper_region_info<binary, 2U, 20U, 4U, 40U,
                           dummy<true,helper_fall_through<binary>>>,
                   helper_region_info<binary, 1U, 10U, 3U, 30U,
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

    EXPECT_EQ(stack.alignment(), 2U);
    EXPECT_EQ(optimized.alignment(), 2U);
    EXPECT_EQ(basic.alignment(), 1U);
}
