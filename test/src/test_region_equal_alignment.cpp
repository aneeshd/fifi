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
#include "helper_fall_through.hpp"
#include "helper_region_info.hpp"

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
            helper_region_info<0,0,0,0,
            helper_fall_through<Field,
            dummy_typedef_basic_super<
            helper_region_info<0,0,0,0,
            helper_fall_through<Field,
            final<Field> > > > > > > >
        { };

        template<class Field>
        struct test_operation
        {
            typedef Field field_type;

            typedef typename field_type::value_type value_type;

            typedef dummy_stack<field_type> stack_type;
            typedef capture_calls<value_type> calls_type;

            typedef typename stack_type::BasicSuper basic_super;
            typedef typename stack_type::OptimizedSuper optimized_super;

            test_operation()
            {
                m_value_size = sizeof(value_type);

                // The alignment is measured in bytes
                m_alignment = 16;
                m_length = 100;
            }

            void run_test()
            {
                fifi::helper_test_buffer<value_type> dest_buffer(
                    m_length, m_alignment);
                fifi::helper_test_buffer<value_type> src_buffer(
                    m_length, m_alignment);

                random_constant<field_type> constants;
                auto constant = constants.pack();

                // If the buffers are aligned, the optimized approach is used.
                for (uint32_t offset = 0; offset < m_length; offset++)
                {
                    SCOPED_TRACE(testing::Message() << "offset:" << offset);
                    value_type* dest = &dest_buffer.data()[offset];
                    value_type* src = &src_buffer.data()[offset];
                    ASSERT_EQ((uintptr_t)dest % m_alignment,
                          (uintptr_t)src  % m_alignment);
                    test(dest, src, constant, true);
                }

                // If the buffers are unaligned, the basic approach is used.
                for (uint32_t offset = 1; offset < m_alignment; offset++)
                {
                    SCOPED_TRACE(testing::Message() << "offset:" << offset);
                    value_type* dest = (value_type*)&dest_buffer.data()[offset];
                    value_type* src = (value_type*)&src_buffer.data()[0];

                    ASSERT_NE((uintptr_t)dest % m_alignment,
                              (uintptr_t)src  % m_alignment);

                    test(dest, src, constant, false);
                }
            }

            void test(value_type* dest, const value_type* src,
                value_type constant, bool aligned)
            {
                run_operation(aligned,
                    std::mem_fn(&stack_type::region_add),
                    std::mem_fn(&calls_type::call_region_add),
                    m_length, dest, src);

                run_operation(aligned,
                    std::mem_fn(&stack_type::region_subtract),
                    std::mem_fn(&calls_type::call_region_subtract),
                    m_length, dest, src);

                run_operation(aligned,
                    std::mem_fn(&stack_type::region_multiply),
                    std::mem_fn(&calls_type::call_region_multiply),
                    m_length, dest, src);

                run_operation(aligned,
                    std::mem_fn(&stack_type::region_divide),
                    std::mem_fn(&calls_type::call_region_divide),
                    m_length, dest, src);

                run_operation(aligned,
                    std::mem_fn(&stack_type::region_multiply_add),
                    std::mem_fn(&calls_type::call_region_multiply_add),
                    m_length, dest, src, constant);

                run_operation(aligned,
                    std::mem_fn(&stack_type::region_multiply_subtract),
                    std::mem_fn(&calls_type::call_region_multiply_subtract),
                    m_length, dest, src, constant);
            }

            template<class Function, class CallFunction, class... Args>
            void run_operation(bool aligned, Function function,
                CallFunction call_function,  uint32_t length, value_type* dest,
                Args&&... args)
            {
                basic_super& basic = m_stack;
                optimized_super& optimized = m_stack;

                basic.set_alignment(m_value_size);
                optimized.set_alignment(m_alignment);

                optimized.clear();
                basic.clear();
                m_basic_calls.clear();
                m_optimized_calls.clear();

                function(m_stack, dest, args..., length);

                if (aligned)
                {
                    call_function(m_optimized_calls, dest, args..., length);
                }
                else
                {
                    call_function(m_basic_calls, dest, args..., length);
                }

                EXPECT_EQ(m_optimized_calls, optimized.m_calls);
                EXPECT_EQ(m_basic_calls, basic.m_calls);
            }

        protected:

            stack_type m_stack;
            calls_type m_basic_calls;
            calls_type m_optimized_calls;

            uint32_t m_value_size;
            uint32_t m_alignment;
            uint32_t m_length;
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

TEST(TestRegionEqualAlignment, all)
{
    {
        SCOPED_TRACE("binary");
        fifi::test_operation<fifi::binary>().run_test();
    }
    {
        SCOPED_TRACE("binary4");
        fifi::test_operation<fifi::binary4>().run_test();
    }
    {
        SCOPED_TRACE("binary8");
        fifi::test_operation<fifi::binary8>().run_test();
    }
    {
        SCOPED_TRACE("binary16");
        fifi::test_operation<fifi::binary16>().run_test();
    }
}
