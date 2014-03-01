// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <vector>
#include <memory>
#include <functional>

#include <gtest/gtest.h>

#include <fifi/binary.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>
#include <fifi/final.hpp>
#include <fifi/region_equal_alignment.hpp>

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
        class dummy_stack :
            public region_equal_alignment<
                   dummy_typedef_optimized_super<
                   region_dummy<
                   dummy_typedef_basic_super<
                   region_dummy<
                   final<Field> > > > > >
        { };

        template<class Field>
        struct TestOperationBase
        {
            typedef Field field_type;
            typedef dummy_stack<field_type> stack_type;

            typedef typename field_type::value_type value_type;
            typedef typename stack_type::BasicSuper basic_super;
            typedef typename stack_type::OptimizedSuper optimized_super;

            TestOperationBase()
            {
                m_value_size = sizeof(typename field_type::value_type);
                m_alignment = m_value_size * 8;
                m_length = 100;

                m_basic = &m_stack;
                m_optimized = &m_stack;

                m_basic->set_alignment(m_value_size);
                m_optimized->set_alignment(m_alignment);
            }

            void run_test()
            {
                fifi::helper_test_buffer<value_type> dest_buffer(
                    m_length, m_alignment);
                fifi::helper_test_buffer<value_type> src_buffer(
                    m_length, m_alignment);

                // If the buffers are aligned, the optimized approach is used.
                for (uint32_t offset = 0; offset < m_length; offset++)
                {
                    m_optimized->clear_test();
                    m_basic->clear_test();

                    value_type* dest = &dest_buffer.data()[offset];
                    value_type* src = &src_buffer.data()[offset];

                    ASSERT_EQ((uintptr_t)dest % m_alignment,
                              (uintptr_t)src  % m_alignment);

                    test_aligned(dest, src);
                }

                // If the buffers are unaligned, the basic approach is used.
                for (uint32_t offset = 1; offset < m_alignment / m_value_size;
                    offset++)
                {
                    m_optimized->clear_test();
                    m_basic->clear_test();

                    value_type* dest = &dest_buffer.data()[offset];
                    value_type* src = &src_buffer.data()[0];

                    ASSERT_NE((uintptr_t)dest % m_alignment,
                              (uintptr_t)src  % m_alignment);

                    test_unaligned(dest, src);
                }
            }

            virtual void test_aligned(value_type* dest, value_type* src) = 0;

            virtual void test_unaligned(value_type* dest, value_type* src) = 0;

        protected:

            stack_type m_stack;

            basic_super* m_basic;
            optimized_super* m_optimized;

            uint32_t m_value_size;
            uint32_t m_alignment;
            uint32_t m_length;
        };

        template<class Field>
        struct TestRegionAdd : public TestOperationBase<Field>
        {
            typedef typename TestOperationBase<Field>::value_type value_type;

            virtual void test_aligned(value_type* dest, value_type* src)
            {
                this->m_stack.region_add(dest, src, this->m_length);

                EXPECT_EQ(this->m_optimized->m_add_dest, dest);
                EXPECT_EQ(this->m_optimized->m_add_src, src);
                EXPECT_EQ(this->m_optimized->m_add_length, this->m_length);

                EXPECT_EQ(this->m_basic->m_add_dest, nullptr);
                EXPECT_EQ(this->m_basic->m_add_src, nullptr);
                EXPECT_EQ(this->m_basic->m_add_length, 0U);
            }

            virtual void test_unaligned(value_type* dest, value_type* src)
            {
                this->m_stack.region_add(dest, src, this->m_length);

                EXPECT_EQ(this->m_optimized->m_add_dest, nullptr);
                EXPECT_EQ(this->m_optimized->m_add_src, nullptr);
                EXPECT_EQ(this->m_optimized->m_add_length, 0U);

                EXPECT_EQ(this->m_basic->m_add_dest, dest);
                EXPECT_EQ(this->m_basic->m_add_src, src);
                EXPECT_EQ(this->m_basic->m_add_length, this->m_length);
            }
        };

        template<class Field>
        struct TestRegionSubtract : public TestOperationBase<Field>
        {
            typedef typename TestOperationBase<Field>::value_type value_type;

            virtual void test_aligned(value_type* dest, value_type* src)
            {
                this->m_stack.region_subtract(dest, src, this->m_length);

                EXPECT_EQ(this->m_optimized->m_subtract_dest, dest);
                EXPECT_EQ(this->m_optimized->m_subtract_src, src);
                EXPECT_EQ(this->m_optimized->m_subtract_length, this->m_length);

                EXPECT_EQ(this->m_basic->m_subtract_dest, nullptr);
                EXPECT_EQ(this->m_basic->m_subtract_src, nullptr);
                EXPECT_EQ(this->m_basic->m_subtract_length, 0U);
            }

            virtual void test_unaligned(value_type* dest, value_type* src)
            {
                this->m_stack.region_subtract(dest, src, this->m_length);

                EXPECT_EQ(this->m_optimized->m_subtract_dest, nullptr);
                EXPECT_EQ(this->m_optimized->m_subtract_src, nullptr);
                EXPECT_EQ(this->m_optimized->m_subtract_length, 0U);

                EXPECT_EQ(this->m_basic->m_subtract_dest, dest);
                EXPECT_EQ(this->m_basic->m_subtract_src, src);
                EXPECT_EQ(this->m_basic->m_subtract_length, this->m_length);
            }
        };

        template<class Field>
        struct TestRegionMultiply : public TestOperationBase<Field>
        {
            typedef typename TestOperationBase<Field>::value_type value_type;

            virtual void test_aligned(value_type* dest, value_type* src)
            {
                this->m_stack.region_multiply(dest, src, this->m_length);

                EXPECT_EQ(this->m_optimized->m_multiply_dest, dest);
                EXPECT_EQ(this->m_optimized->m_multiply_src, src);
                EXPECT_EQ(this->m_optimized->m_multiply_length, this->m_length);

                EXPECT_EQ(this->m_basic->m_multiply_dest, nullptr);
                EXPECT_EQ(this->m_basic->m_multiply_src, nullptr);
                EXPECT_EQ(this->m_basic->m_multiply_length, 0U);
            }

            virtual void test_unaligned(value_type* dest, value_type* src)
            {
                this->m_stack.region_multiply(dest, src, this->m_length);

                EXPECT_EQ(this->m_optimized->m_multiply_dest, nullptr);
                EXPECT_EQ(this->m_optimized->m_multiply_src, nullptr);
                EXPECT_EQ(this->m_optimized->m_multiply_length, 0U);

                EXPECT_EQ(this->m_basic->m_multiply_dest, dest);
                EXPECT_EQ(this->m_basic->m_multiply_src, src);
                EXPECT_EQ(this->m_basic->m_multiply_length, this->m_length);
            }
        };

        template<class Field>
        struct TestRegionDivide : public TestOperationBase<Field>
        {
            typedef typename TestOperationBase<Field>::value_type value_type;

            virtual void test_aligned(value_type* dest, value_type* src)
            {
                this->m_stack.region_divide(dest, src, this->m_length);

                EXPECT_EQ(this->m_optimized->m_divide_dest, dest);
                EXPECT_EQ(this->m_optimized->m_divide_src, src);
                EXPECT_EQ(this->m_optimized->m_divide_length, this->m_length);

                EXPECT_EQ(this->m_basic->m_divide_dest, nullptr);
                EXPECT_EQ(this->m_basic->m_divide_src, nullptr);
                EXPECT_EQ(this->m_basic->m_divide_length, 0U);
            }

            virtual void test_unaligned(value_type* dest, value_type* src)
            {
                this->m_stack.region_divide(dest, src, this->m_length);

                EXPECT_EQ(this->m_optimized->m_divide_dest, nullptr);
                EXPECT_EQ(this->m_optimized->m_divide_src, nullptr);
                EXPECT_EQ(this->m_optimized->m_divide_length, 0U);

                EXPECT_EQ(this->m_basic->m_divide_dest, dest);
                EXPECT_EQ(this->m_basic->m_divide_src, src);
                EXPECT_EQ(this->m_basic->m_divide_length, this->m_length);
            }
        };

        template<class Field>
        struct TestRegionMultiplyAdd : public TestOperationBase<Field>
        {
            typedef typename TestOperationBase<Field>::value_type value_type;

            virtual void test_aligned(value_type* dest, value_type* src)
            {
                this->m_stack.region_multiply_add(dest, src, 0, this->m_length);

                EXPECT_EQ(this->m_optimized->m_multiply_add_dest, dest);
                EXPECT_EQ(this->m_optimized->m_multiply_add_src, src);
                EXPECT_EQ(
                    this->m_optimized->m_multiply_add_length, this->m_length);

                EXPECT_EQ(this->m_basic->m_multiply_add_dest, nullptr);
                EXPECT_EQ(this->m_basic->m_multiply_add_src, nullptr);
                EXPECT_EQ(this->m_basic->m_multiply_add_length, 0U);
            }

            virtual void test_unaligned(value_type* dest, value_type* src)
            {
                this->m_stack.region_multiply_add(dest, src, 0, this->m_length);

                EXPECT_EQ(this->m_optimized->m_multiply_add_dest, nullptr);
                EXPECT_EQ(this->m_optimized->m_multiply_add_src, nullptr);
                EXPECT_EQ(this->m_optimized->m_multiply_add_length, 0U);

                EXPECT_EQ(this->m_basic->m_multiply_add_dest, dest);
                EXPECT_EQ(this->m_basic->m_multiply_add_src, src);
                EXPECT_EQ(this->m_basic->m_multiply_add_length, this->m_length);
            }
        };

        template<class Field>
        struct TestRegionMultiplySubtract : public TestOperationBase<Field>
        {
            typedef typename TestOperationBase<Field>::value_type value_type;

            virtual void test_aligned(value_type* dest, value_type* src)
            {
                this->m_stack.region_multiply_subtract(
                    dest, src, 0, this->m_length);

                EXPECT_EQ(this->m_optimized->m_multiply_subtract_dest, dest);
                EXPECT_EQ(this->m_optimized->m_multiply_subtract_src, src);
                EXPECT_EQ(this->m_optimized->m_multiply_subtract_length,
                          this->m_length);

                EXPECT_EQ(this->m_basic->m_multiply_subtract_dest, nullptr);
                EXPECT_EQ(this->m_basic->m_multiply_subtract_src, nullptr);
                EXPECT_EQ(this->m_basic->m_multiply_subtract_length, 0U);
            }

            virtual void test_unaligned(value_type* dest, value_type* src)
            {
                this->m_stack.region_multiply_subtract(
                    dest, src, 0, this->m_length);

                EXPECT_EQ(this->m_optimized->m_multiply_subtract_dest, nullptr);
                EXPECT_EQ(this->m_optimized->m_multiply_subtract_src, nullptr);
                EXPECT_EQ(this->m_optimized->m_multiply_subtract_length, 0U);

                EXPECT_EQ(this->m_basic->m_multiply_subtract_dest, dest);
                EXPECT_EQ(this->m_basic->m_multiply_subtract_src, src);
                EXPECT_EQ(this->m_basic->m_multiply_subtract_length,
                          this->m_length);
            }
        };

        template<template<class> class TestOperation>
        void check_operation()
        {
            {
                SCOPED_TRACE("binary");
                TestOperation<binary>().run_test();
            }
            {
                SCOPED_TRACE("binary4");
                TestOperation<binary4>().run_test();
            }
            {
                SCOPED_TRACE("binary8");
                TestOperation<binary8>().run_test();
            }
            {
                SCOPED_TRACE("binary16");
                TestOperation<binary16>().run_test();
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
    fifi::check_operation<fifi::TestRegionAdd>();
}

TEST(TestRegionEqualAlignment, region_subtract)
{
    fifi::check_operation<fifi::TestRegionSubtract>();
}

TEST(TestRegionEqualAlignment, region_multiply)
{
    fifi::check_operation<fifi::TestRegionMultiply>();
}

TEST(TestRegionEqualAlignment, region_divide)
{
    fifi::check_operation<fifi::TestRegionDivide>();
}

TEST(TestRegionEqualAlignment, region_multiply_add)
{
    fifi::check_operation<fifi::TestRegionMultiplyAdd>();
}

TEST(TestRegionEqualAlignment, region_multiply_subtract)
{
    fifi::check_operation<fifi::TestRegionMultiplySubtract>();
}