// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary_packed_arithmetic.hpp>
#include <fifi/binary_region_arithmetic.hpp>
#include <fifi/binary_simple_online_arithmetic.hpp>
#include <fifi/final.hpp>
#include <fifi/packed_arithmetic.hpp>
#include <fifi/polynomial_degree.hpp>
#include <fifi/prime2325.hpp>
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
        struct dummy_stack_fall_through : public
        binary_region_arithmetic<Field,
        helper_fall_through<Field> >
        { };
    }

    namespace
    {
        template<class Field>
        struct dummy_stack : public
        binary_region_arithmetic<Field,
        region_arithmetic<
        region_info<
        binary_packed_arithmetic<Field,
        packed_arithmetic<
        binary_simple_online_arithmetic<Field,
        simple_online_arithmetic<
        polynomial_degree<
        final<Field> > > > > > > > >
        { };
    }
}
TEST(TestBinaryRegionArithmetic, fall_through_binary)
{
    typedef fifi::dummy_stack_fall_through<fifi::binary> stack;
    typedef typename stack::field_type field_type;
    typedef typename field_type::value_type value_type;

    fifi::capture_calls<value_type> expected_calls;
    stack s;

    {
        // region_multiply_constant

        uint32_t length = 10;
        auto dest_vector = std::vector<value_type>(length);
        auto constant = fifi::pack<field_type>(1);

        s.m_calls.clear();
        expected_calls.clear();

        s.region_multiply_constant(dest_vector.data(), constant, length);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    {
        // region_multiply_add

        uint32_t length = 10;
        auto dest_vector = std::vector<value_type>(length);
        auto src_vector = std::vector<value_type>(length);
        auto constant = fifi::pack<field_type>(1);

        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_region_add(dest_vector.data(), src_vector.data(),
            length);

        s.region_multiply_add(dest_vector.data(), src_vector.data(), constant,
            length);

        EXPECT_EQ(expected_calls, s.m_calls);

        // region_multiply_subtract uses the same implementation.

        s.m_calls.clear();
        s.region_multiply_subtract(dest_vector.data(), src_vector.data(),
            constant, length);
        EXPECT_EQ(expected_calls, s.m_calls);
    }

    // Test that other calls does fall through.
    fifi::test_fall_through_region_add<stack>();
    fifi::test_fall_through_region_subtract<stack>();
    fifi::test_fall_through_region_multiply<stack>();
    fifi::test_fall_through_region_divide<stack>();
}

TEST(TestBinaryRegionArithmetic, fall_through_binary4)
{
    fifi::test_region_fall_through<
        fifi::dummy_stack_fall_through<fifi::binary4>>();
}

TEST(TestBinaryRegionArithmetic, fall_through_binary8)
{
    fifi::test_region_fall_through<
        fifi::dummy_stack_fall_through<fifi::binary8>>();
}

TEST(TestBinaryRegionArithmetic, fall_through_binary16)
{
    fifi::test_region_fall_through<
        fifi::dummy_stack_fall_through<fifi::binary16>>();
}

TEST(TestBinaryRegionArithmetic, multiply_constant)
{
    check_results_region_multiply_constant<fifi::dummy_stack<fifi::binary> >();
}

TEST(TestBinaryRegionArithmetic, multiply_add)
{
    check_results_region_multiply_add<fifi::dummy_stack<fifi::binary> >();
}

TEST(TestBinaryRegionArithmetic, multiply_subtract)
{
    check_results_region_multiply_subtract<fifi::dummy_stack<fifi::binary> >();
}
