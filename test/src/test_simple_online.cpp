// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/simple_online.hpp>
#include <fifi/field_types.hpp>

#include "expected_results.hpp"

template<class Field>
void test_simple_online()
{
    check_results_multiply<fifi::simple_online<Field> >();
    // check_results_invert<fifi::simple_online<Field> >();
    // check_results_divide<fifi::simple_online<Field> >();
    // check_results_add<fifi::simple_online<Field> >();
    // check_results_subtract<fifi::simple_online<Field> >();
    // check_random<fifi::simple_online<Field> >();
}

//------------------------------------------------------------------
// binary8
//------------------------------------------------------------------

// TEST(TestSimpleOnline, binary8fieldDegree)
// {
//     fifi::simple_online<fifi::binary8> f;

//     EXPECT_EQ( f.find_degree(2), 1U );
//     EXPECT_EQ( f.find_degree(17), 4U );
// }

TEST(TestSimpleOnline, api)
{
    test_simple_online<fifi::binary4>();
    // test_simple_online<fifi::binary8>();
    // test_simple_online<fifi::binary16>();
}

// TEST(TestSimpleOnline, binary8multiply)
// {
//     check_results_multiply<fifi::simple_online<fifi::binary8> >();
// }

// TEST(TestSimpleOnline, binary8invert)
// {
//     check_results_invert<fifi::simple_online<fifi::binary8> >();
// }

// TEST(TestSimpleOnline, binary8divide)
// {
//     check_results_divide<fifi::simple_online<fifi::binary8> >();
// }

// TEST(TestSimpleOnline, binary8add)
// {
//     check_results_add<fifi::simple_online<fifi::binary8> >();
// }

// TEST(TestSimpleOnline, binary8subtract)
// {
//     check_results_subtract<fifi::simple_online<fifi::binary8> >();
// }

// TEST(TestSimpleOnline, binary8randCheck)
// {
//     check_random<fifi::simple_online<fifi::binary8> >();
// }

// //------------------------------------------------------------------
// // binary16
// //------------------------------------------------------------------

// TEST(TestSimpleOnline, binary16multiply)
// {
//     check_results_multiply<fifi::simple_online<fifi::binary16> >();
// }

// TEST(TestSimpleOnline, binary16invert)
// {
//     check_results_invert<fifi::simple_online<fifi::binary16> >();
// }

// TEST(TestSimpleOnline, binary16divide)
// {
//     check_results_divide<fifi::simple_online<fifi::binary16> >();
// }

// TEST(TestSimpleOnline, binary16add)
// {
//     check_results_add<fifi::simple_online<fifi::binary16> >();
// }

// TEST(TestSimpleOnline, binary16subtract)
// {
//     check_results_subtract<fifi::simple_online<fifi::binary16> >();
// }

// TEST(TestSimpleOnline, binary16randCheck)
// {
//     check_random<fifi::simple_online<fifi::binary16> >();
// }

