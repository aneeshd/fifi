// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary8_region_arithmetic_full_table.hpp>
#include <fifi/final.hpp>
#include <fifi/full_table_arithmetic.hpp>
#include <fifi/packed_arithmetic.hpp>
#include <fifi/polynomial_degree.hpp>
#include <fifi/region_arithmetic.hpp>
#include <fifi/region_info.hpp>
#include <fifi/simple_online_arithmetic.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"
#include "helper_catch_all.hpp"
#include "helper_fall_through.hpp"

namespace fifi
{
    namespace
    {
        template<class Field>
        struct fall_through_stack : public
        binary8_region_arithmetic_full_table<Field,
        helper_fall_through<Field> >
        { };
    }

    namespace
    {
        template<class Field>
        struct arithmetic_stack : public
        binary8_region_arithmetic_full_table<Field,
        region_arithmetic<
        region_info<
        packed_arithmetic<
        full_table_arithmetic<
        simple_online_arithmetic<
        polynomial_degree<
        final<Field> > > > > > > >
        { };
    }
}

TEST(TestBinary8RegionArithmeticFullTable, fall_through_binary4)
{
    fifi::test_region_fall_through<fifi::fall_through_stack<fifi::binary4>>();
}

TEST(TestBinary8RegionArithmeticFullTable, fall_through_binary8)
{
    typedef fifi::fall_through_stack<fifi::binary8> stack;
    typedef typename stack::field_type field_type;
    typedef typename field_type::value_type value_type;

    fifi::capture_calls<fifi::binary::value_type> expected_calls;
    stack s;

    {
        // region_multiply_add

        uint32_t length = 10;
        auto dest_vector = std::vector<value_type>(length);
        auto src_vector = std::vector<value_type>(length);
        auto constant = fifi::pack<field_type>(1);

        s.m_calls.clear();
        expected_calls.clear();

        for (uint32_t i = 0; i < length; ++i)
        {
            expected_calls.call_packed_add(dest_vector.data(),
            src_vector.data(), constant, length);
        }


        s.region_multiply_add(dest_vector.data(), src_vector.data(), constant,
            length);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    // Test that other calls does fall through.
    fifi::test_fall_through_region_add<stack>();
    fifi::test_fall_through_region_subtract<stack>();
    fifi::test_fall_through_region_multiply<stack>();
    fifi::test_fall_through_region_divide<stack>();
    fifi::test_fall_through_region_multiply_constant<stack>();
}

TEST(TestBinary8RegionArithmeticFullTable, multiply_add)
{
    check_results_region_multiply_add<
        fifi::arithmetic_stack<fifi::binary8>>();
}

TEST(TestBinary8RegionArithmeticFullTable, multiply_subtract)
{
    check_results_region_multiply_subtract<
        fifi::arithmetic_stack<fifi::binary8>>();
}
