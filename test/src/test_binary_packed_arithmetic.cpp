// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary_packed_arithmetic.hpp>
#include <fifi/final.hpp>
#include <fifi/packed_arithmetic.hpp>
#include <fifi/prime2325.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"
#include "helper_fall_through.hpp"

namespace fifi
{
    // Put dummy layers and tests classes in an anonymous namespace
    // to avoid violations of ODF (one-definition-rule) in other
    // translation units
    namespace
    {
        /// We only need on dummy stack here since all calculations
        /// are implemented in the binary_packed_arithmetic layer
        template<class Field>
        struct dummy_stack : public
            binary_packed_arithmetic<Field,
            helper_fall_through<Field> >
        { };
    }
}

TEST(test_binary_packed_arithmetic, fall_through_binary)
{
    typedef fifi::dummy_stack<fifi::binary> stack;
    // The binary field specialization for this layer implements multiply,
    // divide, and invert. Therefore these should not fall through.
    fifi::capture_calls<fifi::binary::value_type> expected_calls;
    stack s;

    s.m_calls.clear();
    expected_calls.clear();
    s.packed_add(0xFF, 0xFF);
    s.packed_multiply(0xFF, 0xFF);
    s.packed_multiply(0xFF, 0xFF);
    s.packed_divide(0xFF, 0xFF);
    s.packed_invert(0xFF);

    EXPECT_EQ(expected_calls, s.m_calls);
}

TEST(test_binary_packed_arithmetic, fall_through_binary4)
{
    fifi::test_fall_through<fifi::dummy_stack<fifi::binary4>>();
}

TEST(test_binary_packed_arithmetic, fall_through_binary8)
{
    fifi::test_fall_through<fifi::dummy_stack<fifi::binary8>>();
}

TEST(test_binary_packed_arithmetic, fall_through_binary16)
{
    fifi::test_fall_through<fifi::dummy_stack<fifi::binary16>>();
}

TEST(test_binary_packed_arithmetic, add)
{
    check_results_packed_add<fifi::dummy_stack<fifi::binary>>();
}

TEST(test_binary_packed_arithmetic, subtract)
{
    check_results_packed_subtract<fifi::dummy_stack<fifi::binary>>();
}

TEST(test_binary_packed_arithmetic, multiply)
{
    check_results_packed_multiply<fifi::dummy_stack<fifi::binary> >();
}

TEST(test_binary_packed_arithmetic, divide)
{
    check_results_packed_divide<fifi::dummy_stack<fifi::binary>>();
}

TEST(test_binary_packed_arithmetic, invert)
{
    check_results_packed_invert<fifi::dummy_stack<fifi::binary>>();
}

