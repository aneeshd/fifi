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
#include <fifi/region_divide_alignment.hpp>

#include "capture_calls.hpp"
#include "helper_fall_through.hpp"
#include "helper_region_info.hpp"
#include "helper_test_buffer.hpp"
#include "random_constant.hpp"

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
            region_divide_alignment<
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
                // The alignment is measured in bytes
                m_alignment = 16;

            }

            void run_test()
            {
                auto length = 100;

                fifi::helper_test_buffer<value_type> dest_buffer(
                    length, m_alignment);
                fifi::helper_test_buffer<value_type> src_buffer(
                    length, m_alignment);

                random_constant<field_type> constants;
                auto constant = constants.pack();

                // Test the division of the unaligned head and the aligned part
                for (uint32_t offset = 0; offset < length; offset++)
                {
                    value_type* dest = &dest_buffer.data()[offset];
                    value_type* src = &src_buffer.data()[offset];

                    ASSERT_EQ((uintptr_t)dest % m_alignment,
                              (uintptr_t)src  % m_alignment);

                    uint32_t test_length = length - offset;
                    SCOPED_TRACE(testing::Message() << "offset: "
                                                    << offset);
                    SCOPED_TRACE(testing::Message() << "test_length: "
                                                    << test_length);
                    {
                        SCOPED_TRACE("region_add");
                        run_operation(
                            std::mem_fn(&stack_type::region_add),
                            std::mem_fn(&calls_type::call_region_add),
                            test_length, dest, src);
                    }
                    {
                        SCOPED_TRACE("region_subtract");
                        run_operation(
                            std::mem_fn(&stack_type::region_subtract),
                            std::mem_fn(&calls_type::call_region_subtract),
                            test_length, dest, src);
                    }
                    {
                        SCOPED_TRACE("region_multiply");
                        run_operation(
                            std::mem_fn(&stack_type::region_multiply),
                            std::mem_fn(&calls_type::call_region_multiply),
                            test_length, dest, src);
                    }
                    {
                        SCOPED_TRACE("region_divide");
                        run_operation(
                            std::mem_fn(&stack_type::region_divide),
                            std::mem_fn(&calls_type::call_region_divide),
                            test_length, dest, src);
                    }
                    {
                        SCOPED_TRACE("region_multiply_constant");
                        run_operation(
                            std::mem_fn(&stack_type::region_multiply_constant),
                            std::mem_fn(&calls_type::call_region_multiply_constant),
                            test_length, dest, constant);
                    }
                    {
                        SCOPED_TRACE("region_multiply_add");
                        run_operation(
                            std::mem_fn(&stack_type::region_multiply_add),
                            std::mem_fn(&calls_type::call_region_multiply_add),
                            test_length, dest, src, constant);
                    }
                    {
                        SCOPED_TRACE("region_multiply_subtract");
                        run_operation(
                            std::mem_fn(&stack_type::region_multiply_subtract),
                            std::mem_fn(&calls_type::call_region_multiply_subtract),
                            test_length, dest, src, constant);
                    }
                }
            }

            template<class Function, class CallFunction, class... Args>
            void run_operation(Function function, CallFunction call_function,
                uint32_t length, value_type* dest, Args&&... args)
            {
                auto value_size = sizeof(value_type);

                basic_super& basic = m_stack;
                optimized_super& optimized = m_stack;

                basic.set_alignment(value_size);
                optimized.set_alignment(m_alignment);

                optimized.clear();
                basic.clear();
                m_basic_calls.clear();
                m_optimized_calls.clear();

                function(m_stack, dest, args..., length);

                uint32_t modulo = (uintptr_t)dest % m_alignment;
                // If there is no unaligned head
                if (modulo == 0)
                {
                    // The optimized implementation processes the entire
                    // buffer
                    call_function(m_optimized_calls, dest, args..., length);
                }
                else
                {
                    // Otherwise the buffer is divided to 2 parts
                    uint32_t unaligned =
                        (m_alignment - modulo) / value_size;

                    //The basic implementation runs on the unaligned head
                    call_function(m_basic_calls, dest, args..., unaligned);

                    // Calculate the number of remaining values
                    uint32_t rest = length - unaligned;

                    if (rest > 0)
                    {
                        // The optimized implementation processes the
                        // second part
                        second_part_helper(
                            call_function, unaligned, rest, dest, args...);
                    }

                }

                EXPECT_EQ(m_optimized_calls, optimized.m_calls);
                EXPECT_EQ(m_basic_calls, basic.m_calls);
            }


            // Helper function to have a common api for all region arithmetics
            template<class CallFunction, class... Args>
            void second_part_helper(CallFunction call_function,
                uint32_t unaligned, uint32_t length, value_type* dest,
                const value_type* src, Args&&... args)
            {
                call_function(m_optimized_calls, dest + unaligned,
                    src + unaligned, args..., length);
            }

            // Helper function to have a common api for all region arithmetics
            // specialized for multiply_constant
            template<class CallFunction>
            void second_part_helper(CallFunction call_function,
                uint32_t unaligned, uint32_t length, value_type* dest,
                value_type constant)
            {
                call_function(m_optimized_calls, dest + unaligned, constant,
                    length);
            }

        protected:

            stack_type m_stack;
            calls_type m_basic_calls;
            calls_type m_optimized_calls;

            uint32_t m_alignment;
        };
    }
}

TEST(TestRegionDivideAlignment, alignment)
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

TEST(TestRegionDivideAlignment, max_alignment)
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

TEST(TestRegionDivideAlignment, all)
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
