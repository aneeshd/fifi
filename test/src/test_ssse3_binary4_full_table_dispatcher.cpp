// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/ssse3_binary4_full_table_dispatcher.hpp>

#include <gtest/gtest.h>
#include <sak/aligned_allocator.hpp>

#include "helper_test_arithmetic.hpp"
#include "helper_test_packed_arithmetic.hpp"
#include "helper_test_region_arithmetic.hpp"

namespace fifi
{

    namespace
    {

        template<class Field>
        class dummy_layer
        {
        public:

            typedef Field field_type;
            typedef typename field_type::value_type value_type;

        public:

            void region_multiply_constant(
                value_type* dest, value_type constant, uint32_t length) const
            {
                (void) dest;
                (void) constant;
                (void) length;
            }

            uint32_t granularity() const
            {
                return 1U;
            }

            uint32_t alignment() const
            {
                return 1U;
            }
        };

        template<class Field>
        class dummy_stack :
            public ssse3_binary4_full_table_dispatcher<Field,
                   dummy_layer<Field> >
        { };
    }
}

// TEST(TestSSE3Binary4RegionArithmetic, region_add)
// {
//     fifi::check_region_add<fifi::ssse3_binary4_full_table>();
// }

// TEST(TestSSE3Binary4RegionArithmetic, region_subtract)
// {
//     fifi::check_region_subtract<fifi::ssse3_binary4_full_table>();
// }

// TEST(TestSSE3Binary4RegionArithmetic, region_multiply)
// {
//     fifi::check_region_multiply<fifi::ssse3_binary4_full_table>();
// }

// TEST(TestSSE3Binary4RegionArithmetic, region_divide)
// {
//     fifi::check_region_divide<fifi::ssse3_binary4_full_table>();
// }

TEST(TestSSE3Binary4FullTableDispacther, api)
{
    fifi::dummy_stack<fifi::binary4> stack;

    typedef fifi::binary4::value_type value_type;

    typedef std::vector<value_type, sak::aligned_allocator<value_type> >
        aligned_vector;

    aligned_vector data(stack.granularity());
    value_type constant = fifi::pack<fifi::binary4>(2);

    stack.region_multiply_constant(&data[0], constant, data.size());
    stack.region_multiply_constant(&data[0], constant, data.size());
    stack.region_multiply_constant(&data[0], constant, data.size());
    stack.region_multiply_constant(&data[0], constant, data.size());

}

// TEST(TestSSE3Binary4RegionArithmetic, region_multiply_add)
// {
//     fifi::check_region_multiply_add<fifi::ssse3_binary4_full_table>();
// }

// TEST(TestSSE3Binary4RegionArithmetic, region_multiply_subtract)
// {
//     fifi::check_region_multiply_subtract<fifi::ssse3_binary4_full_table>();
// }
