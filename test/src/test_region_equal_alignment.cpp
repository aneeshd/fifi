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
        class region_dummy : public Super
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

            void region_multiply_constant(value_type* dest, value_type constant,
                uint32_t length) const
            {
                m_region_multiply_constant_dest = dest;
                m_region_multiply_constant_constant = constant;
                m_region_multiply_constant_length = length;
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

            void clear_test()
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

                m_region_multiply_constant_dest = 0;
                m_region_multiply_constant_constant = 0;
                m_region_multiply_constant_length = 0;

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

            mutable value_type* m_region_multiply_constant_dest;
            mutable value_type m_region_multiply_constant_constant;
            mutable uint32_t m_region_multiply_constant_length;

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
                   region_dummy<
                   dummy_typedef_basic_super<
                   region_dummy<
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
    typedef field_type::value_type value_type;

    uint32_t value_size = sizeof(field_type::value_type);
    uint32_t alignment = value_size * 8;
    uint32_t length = alignment * 8;

    fifi::dummy_stack<field_type> stack;
    fifi::dummy_stack<field_type>::BasicSuper& basic = stack;
    fifi::dummy_stack<field_type>::OptimizedSuper& optimized = stack;

    basic.set_alignment(value_size);
    optimized.set_alignment(alignment);

    // Test that when buffers are aligned, the optimized approach is used.
    for (uint32_t test_offset = value_size; test_offset < length;
        test_offset += value_size)
    {
        optimized.clear_test();
        basic.clear_test();

        fifi::helper_test_buffer<value_type> dest_buffer(length,
            optimized.alignment());
        fifi::helper_test_buffer<value_type> src_buffer(length,
            optimized.alignment());

        value_type* dest =
            (value_type*)(((uintptr_t)dest_buffer.data()) + test_offset);
        value_type* src =
            (value_type*)(((uintptr_t)src_buffer.data()) + test_offset);

        ASSERT_EQ((uintptr_t)dest % optimized.alignment(),
                  (uintptr_t)src  % optimized.alignment());

        stack.region_add(dest, src, length);

        EXPECT_EQ(optimized.m_region_add_dest, dest);
        EXPECT_EQ(optimized.m_region_add_src, src);
        EXPECT_EQ(optimized.m_region_add_length, length);

        EXPECT_EQ(basic.m_region_add_dest, nullptr);
        EXPECT_EQ(basic.m_region_add_src, nullptr);
        EXPECT_EQ(basic.m_region_add_length, 0U);

    }

    // Test that when buffers are unaligned, the basic approach is used.
    for (uint32_t test_offset = value_size; test_offset < optimized.alignment();
        test_offset += value_size)
    {
        optimized.clear_test();
        basic.clear_test();

        fifi::helper_test_buffer<value_type> dest_buffer(length,
            optimized.alignment());
        fifi::helper_test_buffer<value_type> src_buffer(length,
            optimized.alignment());

        value_type* dest = (value_type*)(((uintptr_t)dest_buffer.data()) + test_offset);
        value_type* src = (value_type*)(((uintptr_t)src_buffer.data()));

        ASSERT_NE((uintptr_t)dest % optimized.alignment(),
                  (uintptr_t)src  % optimized.alignment());

        stack.region_add(dest, src, length);

        EXPECT_EQ(optimized.m_region_add_dest, nullptr);
        EXPECT_EQ(optimized.m_region_add_src, nullptr);
        EXPECT_EQ(optimized.m_region_add_length, 0U);

        EXPECT_EQ(basic.m_region_add_dest, dest);
        EXPECT_EQ(basic.m_region_add_src, src);
        EXPECT_EQ(basic.m_region_add_length, length);

    }
}

template
<
    class Field,
    class Stack,
    class Function,
    class BasicDestMember,
    class BasicSrcMember,
    class BasicLengthMember,
    class OptimizedDestMember,
    class OptimizedSrcMember,
    class OptimizedLengthMember
>
void gerneric_test(
    Function function,
    BasicDestMember basic_dest_member,
    BasicSrcMember basic_src_member,
    BasicLengthMember basic_length_member,
    OptimizedDestMember optimized_dest_member,
    OptimizedSrcMember optimized_src_member,
    OptimizedLengthMember optimized_length_member)
{
    typedef Field field_type;
    typedef typename field_type::value_type value_type;
    typedef typename Stack::BasicSuper basic_super;
    typedef typename Stack::OptimizedSuper optimized_super;

    uint32_t value_size = sizeof(typename field_type::value_type);
    uint32_t alignment = value_size * 8;
    uint32_t length = alignment * 8;

    Stack stack;

    basic_super& basic = stack;
    optimized_super& optimized = stack;

    basic.set_alignment(value_size);
    optimized.set_alignment(alignment);

    // Test that when buffers are aligned, the optimized approach is used.
    for (uint32_t test_offset = value_size; test_offset < length;
        test_offset += value_size)
    {
        optimized.clear_test();
        basic.clear_test();

        fifi::helper_test_buffer<value_type> dest_buffer(length,
            optimized.alignment());
        fifi::helper_test_buffer<value_type> src_buffer(length,
            optimized.alignment());

        value_type* dest =
            (value_type*)(((uintptr_t)dest_buffer.data()) + test_offset);
        value_type* src =
            (value_type*)(((uintptr_t)src_buffer.data()) + test_offset);

        ASSERT_EQ((uintptr_t)dest % optimized.alignment(),
                  (uintptr_t)src  % optimized.alignment());

        function(stack, dest, src, length);

        EXPECT_EQ(optimized.*optimized_dest_member, dest);
        EXPECT_EQ(optimized.*optimized_src_member, src);
        EXPECT_EQ(optimized.*optimized_length_member, length);

        EXPECT_EQ(basic.*basic_dest_member, nullptr);
        EXPECT_EQ(basic.*basic_src_member, nullptr);
        EXPECT_EQ(basic.*basic_length_member, 0U);

    }

    // Test that when buffers are unaligned, the basic approach is used.
    for (uint32_t test_offset = value_size; test_offset < optimized.alignment();
        test_offset += value_size)
    {
        optimized.clear_test();
        basic.clear_test();

        fifi::helper_test_buffer<value_type> dest_buffer(length,
            optimized.alignment());
        fifi::helper_test_buffer<value_type> src_buffer(length,
            optimized.alignment());

        value_type* dest = (value_type*)(((uintptr_t)dest_buffer.data()) + test_offset);
        value_type* src = (value_type*)(((uintptr_t)src_buffer.data()));

        ASSERT_NE((uintptr_t)dest % optimized.alignment(),
                  (uintptr_t)src  % optimized.alignment());

        function(stack, dest, src, length);

        EXPECT_EQ(optimized.*optimized_dest_member, nullptr);
        EXPECT_EQ(optimized.*optimized_src_member, nullptr);
        EXPECT_EQ(optimized.*optimized_length_member, 0U);

        EXPECT_EQ(basic.*basic_dest_member, dest);
        EXPECT_EQ(basic.*basic_src_member, src);
        EXPECT_EQ(basic.*basic_length_member, length);

    }
}

TEST(TestRegionEqualAlignment, generic)
{
    typedef fifi::binary16 field_type;
    typedef fifi::dummy_stack<field_type> stack;
    typedef stack::OptimizedSuper optimized_stack;
    typedef stack::BasicSuper basic_stack;

    gerneric_test<field_type, stack>(
        std::mem_fn(&stack::region_add),
        &basic_stack::m_region_add_dest,
        &basic_stack::m_region_add_src,
        &basic_stack::m_region_add_length,
        &optimized_stack::m_region_add_dest,
        &optimized_stack::m_region_add_src,
        &optimized_stack::m_region_add_length);
}
