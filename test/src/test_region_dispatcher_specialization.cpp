// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/region_dispatcher.hpp>
#include <fifi/binary.hpp>

#include <gtest/gtest.h>

#include "fifi_unit_test/helper_region_info.hpp"

// Put dummy layers and tests classes in an anonymous namespace
// to avoid violations of ODF (one-definition-rule) in other
// translation units
namespace
{
    class dummy_stack
    {
    public:
        using field_type = fifi::binary8;
        using value_type = field_type::value_type;
    };

    // Stack with different field than the dummy stack so it should
    // trigger the empty region_dispatcher_specialization to be used.
    class no_use_stack
    {
    public:
        using field_type = fifi::binary;
    };

    // Stack with same field as the dummy stack so it will be enable the
    // region_dispatcher_specialization
    class use_stack
    {
    public:
        using field_type = fifi::binary8;
    };


}

TEST(region_dispatcher_specialization, api)
{
    fifi::region_dispatcher<no_use_stack, dummy_stack> stack;
    (void)stack;
}


//     template<class Field, bool Enabled>
//     class dummy
//     {
//     public:

//         typedef Field field_type;
//         typedef typename field_type::value_type value_type;

    //     public:

    //         void region_add(value_type* dest, const value_type* src,
    //             uint32_t length) const
    //         {
    //             (void) dest;
    //             (void) src;
    //             (void) length;
    //             EXPECT_TRUE(Enabled);
    //         }

    //         void region_subtract(value_type* dest, const value_type* src,
    //             uint32_t length) const
    //         {
    //             (void) dest;
    //             (void) src;
    //             (void) length;
    //             EXPECT_TRUE(Enabled);
    //         }

    //         void region_multiply(value_type* dest, const value_type* src,
    //             uint32_t length) const
    //         {
    //             (void) dest;
    //             (void) src;
    //             (void) length;
    //             EXPECT_TRUE(Enabled);
    //         }

    //         void region_divide(value_type* dest, const value_type* src,
    //             uint32_t length) const
    //         {
    //             (void) dest;
    //             (void) src;
    //             (void) length;
    //             EXPECT_TRUE(Enabled);
    //         }

    //         void region_multiply_constant(value_type* dest, value_type constant,
    //             uint32_t length) const
    //         {
    //             (void) dest;
    //             (void) constant;
    //             (void) length;
    //             EXPECT_TRUE(Enabled);
    //         }

    //         void region_multiply_add(value_type* dest, const value_type* src,
    //                                  value_type constant,
    //                                  uint32_t length) const
    //         {
    //             (void) dest;
    //             (void) src;
    //             (void) constant;
    //             (void) length;
    //             EXPECT_TRUE(Enabled);
    //         }

    //         void region_multiply_subtract(value_type* dest,
    //             const value_type* src, value_type constant,
    //             uint32_t length) const
    //         {
    //             (void) dest;
    //             (void) src;
    //             (void) constant;
    //             (void) length;
    //             EXPECT_TRUE(Enabled);
    //         }

    //         bool enabled() const
    //         {
    //             return Enabled;
    //         }
    //     };

    //     class dummy_stack_enabled :
    //         public region_dispatcher_specialization_temp<
    //                    binary,
    //                    helper_region_info<
    //                        /*alignment=*/2U,
    //                        /*max_alignment=*/20U,
    //                        /*granularity=*/4U,
    //                        /*max_granularity=*/40U,
    //                    dummy<binary, true>>,
    //                    binary,
    //                    helper_region_info<
    //                        /*alignment=*/1U,
    //                        /*max_alignment=*/10U,
    //                        /*granularity=*/3U,
    //                        /*max_granularity=*/30U,
    //                    dummy<binary, false>>>
    //     { };

    //     class dummy_stack_disabled :
    //         public region_dispatcher_specialization_temp<
    //                    binary,
    //                    helper_region_info<
    //                        /*alignment=*/2U,
    //                        /*max_alignment=*/20U,
    //                        /*granularity=*/4U,
    //                        /*max_granularity=*/40U,
    //                    dummy<binary, false>>,
    //                    binary,
    //                    helper_region_info<
    //                        /*alignment=*/1U,
    //                        /*max_alignment=*/10U,
    //                        /*granularity=*/3U,
    //                        /*max_granularity=*/30U,
    //                    dummy<binary, true>>>
    //     { };
    // }
// }

/// @todo re-enable unit tests

TEST(test_region_dispatcher_specialization, alignment)
{
//     fifi::dummy_stack_disabled disabled_stack;
//     fifi::dummy_stack_enabled enabled_stack;

//     EXPECT_EQ(disabled_stack.alignment(), 1U);
//     EXPECT_EQ(enabled_stack.alignment(), 2U);
}

TEST(test_region_dispatcher_specialization, max_alignment)
{
    // fifi::dummy_stack_disabled disabled_stack;
    // fifi::dummy_stack_enabled enabled_stack;

    // EXPECT_EQ(disabled_stack.max_alignment(), 10U);
    // EXPECT_EQ(enabled_stack.max_alignment(), 20U);
}

TEST(test_region_dispatcher_specialization, granularity)
{
    // fifi::dummy_stack_disabled disabled_stack;
    // fifi::dummy_stack_enabled enabled_stack;

    // EXPECT_EQ(disabled_stack.granularity(), 3U);
    // EXPECT_EQ(enabled_stack.granularity(), 4U);
}

TEST(test_region_dispatcher_specialization, max_granularity)
{
    // fifi::dummy_stack_disabled disabled_stack;
    // fifi::dummy_stack_enabled enabled_stack;

    // EXPECT_EQ(disabled_stack.max_granularity(), 30U);
    // EXPECT_EQ(enabled_stack.max_granularity(), 40U);
}

TEST(test_region_dispatcher_specialization, region_multiply_constant)
{
    // fifi::dummy_stack_enabled enabled_stack;
    // fifi::dummy_stack_disabled disabled_stack;

    // uint32_t length = 1;
    // std::vector<uint8_t> dest(length);
    // std::vector<uint8_t> src(length);
    // uint8_t constant = 255;

    // disabled_stack.region_add(dest.data(), src.data(), length);
    // disabled_stack.region_subtract(dest.data(), src.data(), length);
    // disabled_stack.region_multiply(dest.data(), src.data(), length);
    // disabled_stack.region_divide(dest.data(), src.data(), length);
    // disabled_stack.region_multiply_constant(dest.data(), constant, length);
    // disabled_stack.region_multiply_add(
    //     dest.data(), src.data(), constant, length);
    // disabled_stack.region_multiply_subtract(
    //     dest.data(), src.data(), constant, length);

    // enabled_stack.region_add(dest.data(), src.data(), length);
    // enabled_stack.region_subtract(dest.data(), src.data(), length);
    // enabled_stack.region_multiply(dest.data(), src.data(), length);
    // enabled_stack.region_divide(dest.data(), src.data(), length);
    // enabled_stack.region_multiply_constant(dest.data(), constant, length);
    // enabled_stack.region_multiply_add(
    //     dest.data(), src.data(), constant, length);
    // enabled_stack.region_multiply_subtract(
    //     dest.data(), src.data(), constant, length);
}
