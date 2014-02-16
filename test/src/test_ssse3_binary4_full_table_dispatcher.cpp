// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/ssse3_binary4_full_table_dispatcher.hpp>

#include <gtest/gtest.h>

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
                value_type* dest, value_type constant) const
            {
                assert(0);
            }

            uint32_t length_granularity() const
            {
                return 1U;
            }

            uint32_t length() const
            {
                return m_length;
            }

            void set_length(uint32_t length)
            {
                m_length = length;
            }

            uint32_t m_length;

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

    std::vector<value_type> data(stack.length_granularity());
    value_type constant = fifi::pack<fifi::binary4>(2);

    stack.set_length(data.size());

    stack.region_multiply_constant(&data[0], constant);
    stack.region_multiply_constant(&data[0], constant);
    stack.region_multiply_constant(&data[0], constant);
    stack.region_multiply_constant(&data[0], constant);

}

// TEST(TestSSE3Binary4RegionArithmetic, region_multiply_add)
// {
//     fifi::check_region_multiply_add<fifi::ssse3_binary4_full_table>();
// }

// TEST(TestSSE3Binary4RegionArithmetic, region_multiply_subtract)
// {
//     fifi::check_region_multiply_subtract<fifi::ssse3_binary4_full_table>();
// }
