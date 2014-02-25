// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <memory>
#include <functional>

#include <fifi/binary8.hpp>
#include <fifi/final.hpp>
#include <fifi/region_equal_alignment.hpp>
#include <gtest/gtest.h>

#include "helper_test_buffer.hpp"

#include <vector>

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
        class dummy : public Super
        {

        public:

            typedef typename Super::field_type field_type;

            typedef typename Super::value_type value_type;

        public:

            void region_add(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                m_region_add_dest = dest;
                m_region_add_src = src;
                m_region_add_length = length;
            }
            void region_subtract(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                m_region_subtract_dest = dest;
                m_region_subtract_src = src;
                m_region_subtract_length = length;
            }
            void region_divide(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                m_region_divide_dest = dest;
                m_region_divide_src = src;
                m_region_divide_length = length;
            }
            void region_multiply(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                m_region_multiply_dest = dest;
                m_region_multiply_src = src;
                m_region_multiply_length = length;
            }
            void region_multiply_add(value_type* dest, const value_type* src,
                              value_type constant, uint32_t length) const
            {
                m_region_multiply_add_dest = dest;
                m_region_multiply_add_src = src;
                m_region_multiply_add_constant = constant;
                m_region_multiply_add_length = length;
            }
            void region_multiply_subtract(value_type* dest,
                const value_type* src, value_type constant,
                uint32_t length) const
            {
                m_region_multiply_subtract_dest = dest;
                m_region_multiply_subtract_src = src;
                m_region_multiply_subtract_constant = constant;
                m_region_multiply_subtract_length = length;
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

            void clear()
            {
                m_region_add_dest = 0;
                m_region_add_src = 0;
                m_region_add_length = 0;

                m_region_subtract_dest = 0;
                m_region_subtract_src = 0;
                m_region_subtract_length = 0;

                m_region_divide_dest = 0;
                m_region_divide_src = 0;
                m_region_divide_length = 0;

                m_region_multiply_dest = 0;
                m_region_multiply_src = 0;
                m_region_multiply_length = 0;

                m_region_multiply_add_dest = 0;
                m_region_multiply_add_src = 0;
                m_region_multiply_add_constant = 0;
                m_region_multiply_add_length = 0;

                m_region_multiply_subtract_dest = 0;
                m_region_multiply_subtract_src = 0;
                m_region_multiply_subtract_constant = 0;
                m_region_multiply_subtract_length = 0;
            }

        public:
            mutable value_type* m_region_add_dest;
            mutable const value_type* m_region_add_src;
            mutable uint32_t m_region_add_length;

            mutable value_type* m_region_subtract_dest;
            mutable const value_type* m_region_subtract_src;
            mutable uint32_t m_region_subtract_length;

            mutable value_type* m_region_divide_dest;
            mutable const value_type* m_region_divide_src;
            mutable uint32_t m_region_divide_length;

            mutable value_type* m_region_multiply_dest;
            mutable value_type* m_region_multiply_src;
            mutable uint32_t m_region_multiply_length;

            mutable value_type* m_region_multiply_add_dest;
            mutable const value_type* m_region_multiply_add_src;
            mutable value_type m_region_multiply_add_constant;
            mutable uint32_t m_region_multiply_add_length;

            mutable value_type* m_region_multiply_subtract_dest;
            mutable const value_type* m_region_multiply_subtract_src;
            mutable value_type m_region_multiply_subtract_constant;
            mutable uint32_t m_region_multiply_subtract_length;

        private:

            uint32_t m_alignment;
            uint32_t m_max_alignment;
        };

        template<class Field>
        class dummy_stack :
            public region_equal_alignment<
                   dummy_typedef_optimized_super<
                   dummy<
                   dummy_typedef_basic_super<
                   dummy<
                   final<Field> > > > > >
        { };
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
    typedef fifi::binary16 field_type;
    typedef typename field_type::value_type value_type;

    uint32_t value_size = sizeof(typename field_type::value_type);
    uint32_t alignment = value_size * 4;
    uint32_t length = alignment * 8;

    fifi::dummy_stack<field_type> stack;
    fifi::dummy_stack<field_type>::BasicSuper& basic = stack;
    fifi::dummy_stack<field_type>::OptimizedSuper& optimized = stack;

    basic.set_alignment(value_size);
    optimized.set_alignment(alignment);

    for (uint32_t i = 1; i < 10; ++i)
    {
        optimized.clear();
        basic.clear();

        uint32_t test_alignment = i * value_size;

        fifi::helper_test_buffer<value_type> dest(length, test_alignment);

        assert(((uintptr_t) dest.data() % test_alignment) == 0);

        fifi::helper_test_buffer<value_type> src(length, test_alignment);

        assert(((uintptr_t) src.data() % test_alignment) == 0);

        ASSERT_EQ((uintptr_t)dest.data() % optimized.alignment(),
                  (uintptr_t)src.data()  % optimized.alignment());

        stack.region_add(dest.data(), src.data(), length);

        EXPECT_EQ(optimized.m_region_add_dest, dest.data());
        EXPECT_EQ(optimized.m_region_add_src, src.data());
        EXPECT_EQ(optimized.m_region_add_length, length);

        EXPECT_EQ(basic.m_region_add_dest, nullptr);
        EXPECT_EQ(basic.m_region_add_src, nullptr);
        EXPECT_EQ(basic.m_region_add_length, 0U);
    }
/*
    for (uint32_t i = 1; i < 10; ++i)
    {
        // To test unalignemnt we need an alignment requirement above 1.
        assert(alignment > 1);

        optimized.clear();
        basic.clear();

        uint32_t align = i*value_size;
        fifi::helper_test_buffer<field_type> dest(length, align, false);
        fifi::helper_test_buffer<field_type> src(length, align+value_size, false);

        EXPECT_FALSE((uintptr_t)dest.data() % optimized.alignment() ==
                  (uintptr_t)src.data()  % optimized.alignment());

        stack.region_add(dest.data(), src.data(), length);

        EXPECT_EQ(basic.m_region_add_dest, dest.data());
        EXPECT_EQ(basic.m_region_add_src, src.data());
        EXPECT_EQ(basic.m_region_add_length, length);

        EXPECT_EQ(optimized.m_region_add_dest, nullptr);
        EXPECT_EQ(optimized.m_region_add_src, nullptr);
        EXPECT_EQ(optimized.m_region_add_length, 0U);
    }
    */
}
