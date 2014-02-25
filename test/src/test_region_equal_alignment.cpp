// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/region_equal_alignment.hpp>
#include <fifi/final.hpp>

#include <gtest/gtest.h>

#include <memory>

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
            value_type* m_region_add_dest;
            value_type* m_region_add_src;
            uint32_t m_region_add_length;

            value_type* m_region_subtract_dest;
            value_type* m_region_subtract_src;
            uint32_t m_region_subtract_length;

            value_type* m_region_divide_dest;
            value_type* m_region_divide_src;
            uint32_t m_region_divide_length;

            value_type* m_region_multiply_dest;
            value_type* m_region_multiply_src;
            uint32_t m_region_multiply_length;

            value_type* m_region_multiply_add_dest;
            value_type* m_region_multiply_add_src;
            value_type m_region_multiply_add_constant;
            uint32_t m_region_multiply_add_length;

            value_type* m_region_multiply_subtract_dest;
            value_type* m_region_multiply_subtract_src;
            value_type m_region_multiply_subtract_constant;
            uint32_t m_region_multiply_subtract_length;

        protected:

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
    fifi::dummy_stack<fifi::binary>* stack = new fifi::dummy_stack<fifi::binary>();
    fifi::dummy_stack<fifi::binary>::BasicSuper* basic = stack;
    fifi::dummy_stack<fifi::binary>::OptimizedSuper* optimized = stack;

    basic->set_alignment(1U);
    optimized->set_alignment(16U);

    EXPECT_EQ(1U, basic->alignment());
    EXPECT_EQ(16U, optimized->alignment());
    EXPECT_EQ(16U, stack->alignment());

    delete stack;
}
