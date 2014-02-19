// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/final.hpp>
#include <fifi/region_dispatcher.hpp>

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

            uint32_t granularity() const
            {
                return 2U;
            }

            uint32_t alignment() const
            {
                return 2U;
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

            uint32_t granularity() const
            {
                return 1U;
            }

            uint32_t alignment() const
            {
                return 1U;
            }
        };

        class dummy_stack_enabled :
            public region_dispatcher<binary, dummy_optimization<binary, true>,
                   dummy_base<binary, false> >
        { };

        class dummy_stack_disabled :
            public region_dispatcher<binary, dummy_optimization<binary, false>,
                   dummy_base<binary, true> >
        { };
    }
}

TEST(TestRegionDispatcher, alignment)
{
    fifi::dummy_stack_enabled enabled_stack;
    fifi::dummy_stack_disabled disabled_stack;

    EXPECT_EQ(disabled_stack.alignment(), 1U);
    EXPECT_EQ(enabled_stack.alignment(), 2U);
}

TEST(TestRegionDispatcher, granularity)
{
    fifi::dummy_stack_enabled enabled_stack;
    fifi::dummy_stack_disabled disabled_stack;

    EXPECT_EQ(disabled_stack.granularity(), 1U);
    EXPECT_EQ(enabled_stack.granularity(), 2U);
}

TEST(TestRegionDispatcher, region_multiply_constant)
{
    fifi::dummy_stack_enabled enabled_stack;
    fifi::dummy_stack_disabled disabled_stack;

    typedef typename fifi::binary::value_type value_type;

    uint32_t length = 1;
    std::vector<value_type> dest(length);
    value_type constant = 255;


    enabled_stack.region_multiply_constant(dest.data(),constant,length);
    disabled_stack.region_multiply_constant(dest.data(),constant,length);
}
