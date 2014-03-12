// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/final.hpp>
#include <fifi/full_table_arithmetic.hpp>
#include <fifi/simple_online_arithmetic.hpp>
#include <fifi/simple_online.hpp>

#include <gtest/gtest.h>

#include "fifi_unit_test/expected_results.hpp"
#include "fifi_unit_test/helper_fall_through.hpp"

namespace fifi
{
    // Put dummy layers and tests classes in an anonymous namespace
    // to avoid violations of ODF (one-definition-rule) in other
    // translation units
    namespace
    {
        template<class Field>
        struct dummy_stack_fall_through : public
            full_table_arithmetic<
            helper_fall_through<Field> >
        { };

        template<class Field>
        struct dummy_stack : public
            full_table_arithmetic<
            simple_online_arithmetic<
            final<Field> > >
        { };
    }
}

template<class Field>
inline void helper_fall_through()
{
    typedef fifi::dummy_stack_fall_through<Field> stack;

    fifi::capture_calls<typename Field::value_type> expected_calls;
    stack s;

    s.m_calls.clear();
    expected_calls.clear();
    s.multiply(1, 1);
    s.divide(1, 1);
    s.invert(1);

    EXPECT_EQ(expected_calls, s.m_calls);

    // Test that other calls does fall through.
    fifi::test_fall_through_add<stack>();
    fifi::test_fall_through_subtract<stack>();
}

template<class Field>
inline void helper_test_table()
{
    typedef fifi::dummy_stack<Field> test_stack;
    typedef fifi::simple_online<Field> reference_stack;

    typedef typename test_stack::value_type value_type;
    test_stack test;
    reference_stack reference;

    for (uint32_t i = 0; i < Field::order; ++i)
    {
        const value_type* multiplication_row = test.multiplication_row(i);
        const value_type* division_row = test.division_row(i);
        for (uint32_t j = 0; j < Field::order; ++j)
        {
            EXPECT_EQ(reference.multiply(i,j), multiplication_row[j]);
            if (j != 0)
                EXPECT_EQ(reference.divide(i,j), division_row[j]);
        }
    }
}

TEST(test_full_table_arithmetic, table)
{
    {
        SCOPED_TRACE("binary4");
        helper_test_table<fifi::binary4>();
    }
    {
        SCOPED_TRACE("binary8");
        helper_test_table<fifi::binary8>();
    }
}

TEST(test_full_table_arithmetic, fall_through)
{
    {
        SCOPED_TRACE("binary4");
        helper_fall_through<fifi::binary4>();
    }
    {
        SCOPED_TRACE("binary8");
        helper_fall_through<fifi::binary8>();
    }
}

TEST(test_full_table_arithmetic, multiply)
{
    {
        SCOPED_TRACE("binary4");
        check_results_multiply<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_multiply<fifi::dummy_stack<fifi::binary8> >();
    }
}

TEST(test_full_table_arithmetic, divide)
{
    {
        SCOPED_TRACE("binary4");
        check_results_divide<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_divide<fifi::dummy_stack<fifi::binary8> >();
    }
}

TEST(test_full_table_arithmetic, invert)
{
    {
        SCOPED_TRACE("binary4");
        check_results_invert<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_invert<fifi::dummy_stack<fifi::binary8> >();
    }
}

TEST(test_full_table_arithmetic, random)
{
    {
        SCOPED_TRACE("binary4");
        check_random_default<fifi::dummy_stack<fifi::binary4> >();
    }
    {
        SCOPED_TRACE("binary8");
        check_random_default<fifi::dummy_stack<fifi::binary8> >();
    }
}
