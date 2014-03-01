// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>

#include <gtest/gtest.h>

#include <fifi/binary.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>
#include <fifi/final.hpp>
#include <fifi/region_divide_granularity.hpp>

#include "random_constant.hpp"
#include "helper_test_buffer.hpp"
#include "helper_region_dummy.hpp"

namespace fifi
{
    namespace
    {
        template<class Super>
        class dummy_typedef_basic_super : public Super
        {
        public:
            typedef Super BasicSuper;
        };

        template<class Super>
        class dummy_typedef_optimized_super : public Super
        {
        public:
            typedef Super OptimizedSuper;
        };

        template<class Field>
        class dummy_stack : public
            region_divide_granularity<
            dummy_typedef_optimized_super<
            region_dummy<
            dummy_typedef_basic_super<
            region_dummy<
            final<Field> > > > > >
        { };

        template<class Field>
        struct TestOperation
        {
            typedef Field field_type;
            typedef dummy_stack<field_type> stack_type;

            typedef typename field_type::value_type value_type;
            typedef typename stack_type::BasicSuper basic_super;
            typedef typename stack_type::OptimizedSuper optimized_super;

            TestOperation()
            {
                m_value_size = sizeof(value_type);
                // The alignment is measured in bytes
                m_alignment = 16;
                // The granularity is measured in value_types
                m_granularity = 16;
                m_length = 1000;

                m_basic = &m_stack;
                m_optimized = &m_stack;

                m_basic->set_alignment(m_value_size);
                m_optimized->set_alignment(m_alignment);

                m_basic->set_granularity(1U);
                m_optimized->set_granularity(m_granularity);
            }

            void run_test(region_operation operation)
            {
                fifi::helper_test_buffer<value_type> dest_buffer(
                    m_length, m_alignment);
                fifi::helper_test_buffer<value_type> src_buffer(
                    m_length, m_alignment);

                value_type* dest = &dest_buffer.data()[0];
                value_type* src = &src_buffer.data()[0];

                ASSERT_EQ((uintptr_t)dest % m_alignment,
                          (uintptr_t)src  % m_alignment);

                // Test the division of the granulated part and the tail
                for (uint32_t length = 1; length <= m_length; length++)
                {
                    m_optimized->clear_test();
                    m_basic->clear_test();

                    if (operation == region_operation::MULTIPLY_CONSTANT)
                        src = 0;

                    run_operation(operation, dest, src, length);

                    // Calculate the tail that is not granulated correctly
                    uint32_t tail = length % m_granularity;

                    // Calculate the number of granulated values
                    uint32_t optimized = length - tail;

                    if (optimized > 0)
                    {
                        // The optimized implementation processes the
                        // granulated part
                        EXPECT_EQ(m_optimized->m_last_operation, operation);
                        EXPECT_EQ(m_optimized->m_dest, dest);
                        EXPECT_EQ(m_optimized->m_src, src);
                        EXPECT_EQ(m_optimized->m_length, optimized);
                        EXPECT_EQ(m_optimized->m_constant, m_last_constant);
                    }
                    else
                    {
                        // If there is no optimized part, then the optimized
                        // super should not be called
                        EXPECT_EQ(m_optimized->m_last_operation,
                                  region_operation::NONE);
                        EXPECT_EQ(m_optimized->m_dest, nullptr);
                        EXPECT_EQ(m_optimized->m_src, nullptr);
                        EXPECT_EQ(m_optimized->m_length, 0U);
                        EXPECT_EQ(m_optimized->m_constant, 0U);
                    }

                    if (tail > 0)
                    {
                        //The basic implementation runs on the tail
                        EXPECT_EQ(m_basic->m_last_operation, operation);
                        EXPECT_EQ(m_basic->m_dest, dest + optimized);
                        EXPECT_EQ(m_basic->m_src, src + optimized);
                        EXPECT_EQ(m_basic->m_length, tail);
                        EXPECT_EQ(m_basic->m_constant, m_last_constant);
                    }
                    else
                    {
                        // If there is no tail, then the basic super
                        // should not be called
                        EXPECT_EQ(m_basic->m_last_operation,
                                  region_operation::NONE);
                        EXPECT_EQ(m_basic->m_dest, nullptr);
                        EXPECT_EQ(m_basic->m_src, nullptr);
                        EXPECT_EQ(m_basic->m_length, 0U);
                        EXPECT_EQ(m_basic->m_constant, 0U);
                    }
                }
            }

            void run_operation(region_operation operation,
                value_type* dest, value_type* src, uint32_t length)
            {
                m_last_constant = 0;
                switch (operation)
                {
                case region_operation::NONE:
                    assert(0);
                    break;
                case region_operation::ADD:
                    m_stack.region_add(dest, src, length);
                    break;
                case region_operation::SUBTRACT:
                    m_stack.region_subtract(dest, src, length);
                    break;
                case region_operation::MULTIPLY:
                    m_stack.region_multiply(dest, src, length);
                    break;
                case region_operation::DIVIDE:
                    m_stack.region_divide(dest, src, length);
                    break;
                case region_operation::MULTIPLY_CONSTANT:
                    m_last_constant = m_constants.pack();
                    m_stack.region_multiply_constant(
                        dest, m_last_constant, length);
                    break;
                case region_operation::MULTIPLY_ADD:
                    m_last_constant = m_constants.pack();
                    m_stack.region_multiply_add(
                        dest, src, m_last_constant, length);
                    break;
                case region_operation::MULTIPLY_SUBTRACT:
                    m_last_constant = m_constants.pack();
                    m_stack.region_multiply_subtract(
                        dest, src, m_last_constant, length);
                    break;
                default:
                    assert(0);
                    break;
                }
            }

        protected:

            stack_type m_stack;

            basic_super* m_basic;
            optimized_super* m_optimized;

            uint32_t m_value_size;
            uint32_t m_alignment;
            uint32_t m_granularity;
            uint32_t m_length;

            random_constant<field_type> m_constants;
            value_type m_last_constant;
        };

        void check_operation(region_operation operation)
        {
            {
                SCOPED_TRACE("binary");
                TestOperation<binary>().run_test(operation);
            }
            {
                SCOPED_TRACE("binary4");
                TestOperation<binary4>().run_test(operation);
            }
            {
                SCOPED_TRACE("binary8");
                TestOperation<binary8>().run_test(operation);
            }
            {
                SCOPED_TRACE("binary16");
                TestOperation<binary16>().run_test(operation);
            }
        }
    }
}

TEST(TestRegionDivideGranularity, granularity)
{
    fifi::dummy_stack<fifi::binary8> stack;
    fifi::dummy_stack<fifi::binary8>::BasicSuper& basic = stack;
    fifi::dummy_stack<fifi::binary8>::OptimizedSuper& optimized = stack;

    basic.set_granularity(1U);
    optimized.set_granularity(16U);

    EXPECT_EQ(1U, basic.granularity());
    EXPECT_EQ(16U, optimized.granularity());
    EXPECT_EQ(16U, stack.granularity());
}

TEST(TestRegionDivideGranularity, max_granularity)
{
    fifi::dummy_stack<fifi::binary8> stack;
    fifi::dummy_stack<fifi::binary8>::BasicSuper& basic = stack;
    fifi::dummy_stack<fifi::binary8>::OptimizedSuper& optimized = stack;

    basic.set_max_granularity(1U);
    optimized.set_max_granularity(16U);

    EXPECT_EQ(1U, basic.max_granularity());
    EXPECT_EQ(16U, optimized.max_granularity());
    EXPECT_EQ(16U, stack.max_granularity());
}

TEST(TestRegionDivideGranularity, region_add)
{
    fifi::check_operation(fifi::region_operation::ADD);
}

TEST(TestRegionDivideGranularity, region_subtract)
{
    fifi::check_operation(fifi::region_operation::SUBTRACT);
}

TEST(TestRegionDivideGranularity, region_multiply)
{
    fifi::check_operation(fifi::region_operation::MULTIPLY);
}

TEST(TestRegionDivideGranularity, region_divide)
{
    fifi::check_operation(fifi::region_operation::DIVIDE);
}

TEST(TestRegionDivideGranularity, region_multiply_add)
{
    fifi::check_operation(fifi::region_operation::MULTIPLY_ADD);
}

TEST(TestRegionDivideGranularity, region_multiply_subtract)
{
    fifi::check_operation(fifi::region_operation::MULTIPLY_SUBTRACT);
}
