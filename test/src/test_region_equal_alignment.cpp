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
#include <fifi/region_equal_alignment.hpp>

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
            region_equal_alignment<
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
                m_length = 100;
                m_size = m_length * m_value_size;

                m_basic = &m_stack;
                m_optimized = &m_stack;

                m_basic->set_alignment(m_value_size);
                m_optimized->set_alignment(m_alignment);
            }

            void run_test(region_operation operation)
            {
                fifi::helper_test_buffer<uint8_t> dest_buffer(
                    m_size, m_alignment);
                fifi::helper_test_buffer<uint8_t> src_buffer(
                    m_size, m_alignment);

                // If the buffers are aligned, the optimized approach is used.
                for (uint32_t offset = 0; offset < m_size; offset++)
                {
                    m_optimized->clear_test();
                    m_basic->clear_test();

                    value_type* dest = (value_type*)&dest_buffer.data()[offset];
                    value_type* src = (value_type*)&src_buffer.data()[offset];

                    ASSERT_EQ((uintptr_t)dest % m_alignment,
                              (uintptr_t)src  % m_alignment);

                    run_operation(operation, dest, src, m_length);

                    EXPECT_EQ(m_optimized->m_last_operation, operation);
                    EXPECT_EQ(m_optimized->m_dest, dest);
                    EXPECT_EQ(m_optimized->m_src, src);
                    EXPECT_EQ(m_optimized->m_length, m_length);
                    EXPECT_EQ(m_optimized->m_constant, m_last_constant);

                    EXPECT_EQ(m_basic->m_last_operation,
                              region_operation::NONE);
                    EXPECT_EQ(m_basic->m_dest, nullptr);
                    EXPECT_EQ(m_basic->m_src, nullptr);
                    EXPECT_EQ(m_basic->m_length, 0U);
                    EXPECT_EQ(m_basic->m_constant, 0U);
                }

                // If the buffers are unaligned, the basic approach is used.
                for (uint32_t offset = 1; offset < m_alignment; offset++)
                {
                    m_optimized->clear_test();
                    m_basic->clear_test();

                    value_type* dest = (value_type*)&dest_buffer.data()[offset];
                    value_type* src = (value_type*)&src_buffer.data()[0];

                    ASSERT_NE((uintptr_t)dest % m_alignment,
                              (uintptr_t)src  % m_alignment);

                    run_operation(operation, dest, src, m_length);

                    EXPECT_EQ(m_optimized->m_last_operation,
                              region_operation::NONE);
                    EXPECT_EQ(m_optimized->m_dest, nullptr);
                    EXPECT_EQ(m_optimized->m_src, nullptr);
                    EXPECT_EQ(m_optimized->m_length, 0U);
                    EXPECT_EQ(m_optimized->m_constant, 0U);

                    EXPECT_EQ(m_basic->m_last_operation, operation);
                    EXPECT_EQ(m_basic->m_dest, dest);
                    EXPECT_EQ(m_basic->m_src, src);
                    EXPECT_EQ(m_basic->m_length, m_length);
                    EXPECT_EQ(m_basic->m_constant, m_last_constant);
                }
            }

            void run_operation(region_operation operation,
                value_type* dest, value_type* src, uint32_t length)
            {
                m_last_constant = 0;
                switch (operation)
                {
                case fifi::region_operation::NONE:
                    assert(0);
                    break;
                case fifi::region_operation::ADD:
                    m_stack.region_add(dest, src, length);
                    break;
                case fifi::region_operation::SUBTRACT:
                    m_stack.region_subtract(dest, src, length);
                    break;
                case fifi::region_operation::MULTIPLY:
                    m_stack.region_multiply(dest, src, length);
                    break;
                case fifi::region_operation::DIVIDE:
                    m_stack.region_divide(dest, src, length);
                    break;
                case fifi::region_operation::MULTIPLY_CONSTANT:
                    // region_multiply_constant operates on a single buffer
                    assert(0);
                    break;
                case fifi::region_operation::MULTIPLY_ADD:
                    m_last_constant = m_constants.pack();
                    m_stack.region_multiply_add(
                        dest, src, m_last_constant, length);
                    break;
                case fifi::region_operation::MULTIPLY_SUBTRACT:
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
            uint32_t m_length;
            uint32_t m_size;

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

TEST(TestRegionEqualAlignment, alignment)
{
    fifi::dummy_stack<fifi::binary8> stack;
    fifi::dummy_stack<fifi::binary8>::BasicSuper& basic = stack;
    fifi::dummy_stack<fifi::binary8>::OptimizedSuper& optimized = stack;

    basic.set_alignment(1U);
    optimized.set_alignment(16U);

    EXPECT_EQ(1U, basic.alignment());
    EXPECT_EQ(16U, optimized.alignment());
    EXPECT_EQ(16U, stack.alignment());
}

TEST(TestRegionEqualAlignment, max_alignment)
{
    fifi::dummy_stack<fifi::binary8> stack;
    fifi::dummy_stack<fifi::binary8>::BasicSuper& basic = stack;
    fifi::dummy_stack<fifi::binary8>::OptimizedSuper& optimized = stack;

    basic.set_max_alignment(1U);
    optimized.set_max_alignment(16U);

    EXPECT_EQ(1U, basic.max_alignment());
    EXPECT_EQ(16U, optimized.max_alignment());
    EXPECT_EQ(16U, stack.max_alignment());
}

TEST(TestRegionEqualAlignment, region_add)
{
    fifi::check_operation(fifi::region_operation::ADD);
}

TEST(TestRegionEqualAlignment, region_subtract)
{
    fifi::check_operation(fifi::region_operation::SUBTRACT);
}

TEST(TestRegionEqualAlignment, region_multiply)
{
    fifi::check_operation(fifi::region_operation::MULTIPLY);
}

TEST(TestRegionEqualAlignment, region_divide)
{
    fifi::check_operation(fifi::region_operation::DIVIDE);
}

TEST(TestRegionEqualAlignment, region_multiply_add)
{
    fifi::check_operation(fifi::region_operation::MULTIPLY_ADD);
}

TEST(TestRegionEqualAlignment, region_multiply_subtract)
{
    fifi::check_operation(fifi::region_operation::MULTIPLY_SUBTRACT);
}
