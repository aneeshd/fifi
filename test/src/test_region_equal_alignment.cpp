// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <vector>
#include <memory>
#include <functional>

#include <gtest/gtest.h>

#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>
#include <fifi/final.hpp>
#include <fifi/region_equal_alignment.hpp>

#include "helper_test_buffer.hpp"

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

        template<class Super>
        class region_dummy : public Super
        {
        public:

            typedef typename Super::field_type field_type;

            typedef typename Super::value_type value_type;

        public:

            void region_add(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                m_add_dest = dest;
                m_add_src = src;
                m_add_length = length;
            }

            void region_subtract(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                m_subtract_dest = dest;
                m_subtract_src = src;
                m_subtract_length = length;
            }

            void region_divide(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                m_divide_dest = dest;
                m_divide_src = src;
                m_divide_length = length;
            }

            void region_multiply(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                m_multiply_dest = dest;
                m_multiply_src = src;
                m_multiply_length = length;
            }

            void region_multiply_constant(value_type* dest, value_type constant,
                uint32_t length) const
            {
                m_multiply_constant_dest = dest;
                m_multiply_constant_constant = constant;
                m_multiply_constant_length = length;
            }

            void region_multiply_add(value_type* dest, const value_type* src,
                value_type constant, uint32_t length) const
            {
                m_multiply_add_dest = dest;
                m_multiply_add_src = src;
                m_multiply_add_constant = constant;
                m_multiply_add_length = length;
            }

            void region_multiply_subtract(value_type* dest,
                const value_type* src, value_type constant,
                uint32_t length) const
            {
                m_multiply_subtract_dest = dest;
                m_multiply_subtract_src = src;
                m_multiply_subtract_constant = constant;
                m_multiply_subtract_length = length;
            }

            uint32_t alignment() const
            {
                return m_alignment;
            }

            uint32_t max_alignment() const
            {
                return m_max_alignment;
            }

            void set_alignment(uint32_t alignment)
            {
                m_alignment = alignment;
            }

            void set_max_alignment(uint32_t max_alignment)
            {
                m_max_alignment = max_alignment;
            }

            void clear_test()
            {
                m_add_dest = 0;
                m_add_src = 0;
                m_add_length = 0;

                m_subtract_dest = 0;
                m_subtract_src = 0;
                m_subtract_length = 0;

                m_divide_dest = 0;
                m_divide_src = 0;
                m_divide_length = 0;

                m_multiply_dest = 0;
                m_multiply_src = 0;
                m_multiply_length = 0;

                m_multiply_constant_dest = 0;
                m_multiply_constant_constant = 0;
                m_multiply_constant_length = 0;

                m_multiply_add_dest = 0;
                m_multiply_add_src = 0;
                m_multiply_add_constant = 0;
                m_multiply_add_length = 0;

                m_multiply_subtract_dest = 0;
                m_multiply_subtract_src = 0;
                m_multiply_subtract_constant = 0;
                m_multiply_subtract_length = 0;
            }

        public:

            mutable value_type* m_add_dest;
            mutable const value_type* m_add_src;
            mutable uint32_t m_add_length;

            mutable value_type* m_subtract_dest;
            mutable const value_type* m_subtract_src;
            mutable uint32_t m_subtract_length;

            mutable value_type* m_divide_dest;
            mutable const value_type* m_divide_src;
            mutable uint32_t m_divide_length;

            mutable value_type* m_multiply_dest;
            mutable const value_type* m_multiply_src;
            mutable uint32_t m_multiply_length;

            mutable value_type* m_multiply_constant_dest;
            mutable value_type m_multiply_constant_constant;
            mutable uint32_t m_multiply_constant_length;

            mutable value_type* m_multiply_add_dest;
            mutable const value_type* m_multiply_add_src;
            mutable value_type m_multiply_add_constant;
            mutable uint32_t m_multiply_add_length;

            mutable value_type* m_multiply_subtract_dest;
            mutable const value_type* m_multiply_subtract_src;
            mutable value_type m_multiply_subtract_constant;
            mutable uint32_t m_multiply_subtract_length;

        private:

            uint32_t m_alignment;
            uint32_t m_max_alignment;
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
    fifi::TestRegionAdd<fifi::binary4>().run_test();
    fifi::TestRegionAdd<fifi::binary8>().run_test();
    fifi::TestRegionAdd<fifi::binary16>().run_test();
}

TEST(TestRegionEqualAlignment, region_subtract)
{
    fifi::TestRegionSubtract<fifi::binary4>().run_test();
    fifi::TestRegionSubtract<fifi::binary8>().run_test();
    fifi::TestRegionSubtract<fifi::binary16>().run_test();
}

TEST(TestRegionEqualAlignment, region_multiply)
{
    fifi::TestRegionMultiply<fifi::binary4>().run_test();
    fifi::TestRegionMultiply<fifi::binary8>().run_test();
    fifi::TestRegionMultiply<fifi::binary16>().run_test();
}

TEST(TestRegionEqualAlignment, region_divide)
{
    fifi::TestRegionDivide<fifi::binary4>().run_test();
    fifi::TestRegionDivide<fifi::binary8>().run_test();
    fifi::TestRegionDivide<fifi::binary16>().run_test();
}