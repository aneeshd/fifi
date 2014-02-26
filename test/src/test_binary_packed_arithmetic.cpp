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

template<class Field>
void test_binary_packed_counters()
{
    typedef fifi::dummy_stack<Field> stack;

    // We expect all the packed operations fall through the binary4
    // specializations to the other packed arithmetic function
    fifi::fall_through_counter overall;

    overall.zero_counter();

    overall.m_count_packed_multiply = 1U;
    overall.m_count_packed_divide = 1U;
    overall.m_count_packed_invert = 1U;
    overall.m_count_packed_add = 1U;
    overall.m_count_packed_subtract = 1U;
    fifi::test_packed_counters<stack>(overall);
}

template<>
void test_binary_packed_counters<fifi::binary>()
{
    typedef fifi::dummy_stack<fifi::binary> stack;

    // We expect all the packed operations for binary4 fall through to
    // the standard arithmetic functions
    fifi::fall_through_counter overall;
    overall.zero_counter();

    // All arithmetic functions are implemented directly in
    // binary_packed_arithmetic layer so we don't expect to see
    // any calls for those

    fifi::test_packed_counters<stack>(overall);
}

/// Tests the binary packed arithmetic for fields other than binary
TEST(TestBinaryPackedArithmetic, fall_through)
{
    {
        SCOPED_TRACE("binary");
        test_binary_packed_counters<fifi::binary>();
    }

    {
        SCOPED_TRACE("binary4");
        test_binary_packed_counters<fifi::binary4>();
    }

    {
        SCOPED_TRACE("binary8");
        test_binary_packed_counters<fifi::binary8>();
    }

    {
        SCOPED_TRACE("binary16");
        test_binary_packed_counters<fifi::binary16>();
    }

    {
        SCOPED_TRACE("prime2325");
        test_binary_packed_counters<fifi::prime2325>();
    }
}

TEST(TestBinaryPackedArithmetic, add)
{
    check_results_packed_add<fifi::dummy_stack<fifi::binary>>();
}

TEST(TestBinaryPackedArithmetic, subtract)
{
    check_results_packed_subtract<fifi::dummy_stack<fifi::binary>>();
}

TEST(TestBinaryPackedArithmetic, multiply)
{
    check_results_packed_multiply<fifi::dummy_stack<fifi::binary> >();
}

TEST(TestBinaryPackedArithmetic, divide)
{
    check_results_packed_divide<fifi::dummy_stack<fifi::binary>>();
}

TEST(TestBinaryPackedArithmetic, invert)
{
    check_results_packed_invert<fifi::dummy_stack<fifi::binary>>();
}

