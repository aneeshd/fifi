// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/simple_online.hpp>
#include <fifi/field_types.hpp>

#include "expected_results.hpp"

template<class Field>
inline void test_simple_online()
{
    check_results_multiply<fifi::simple_online<Field> >();
    check_results_invert<fifi::simple_online<Field> >();
    check_results_divide<fifi::simple_online<Field> >();
    check_results_add<fifi::simple_online<Field> >();
    check_results_subtract<fifi::simple_online<Field> >();
    check_random<fifi::simple_online<Field> >();
}

TEST(TestSimpleOnline, api)
{
    test_simple_online<fifi::binary4>();
    test_simple_online<fifi::binary8>();
    test_simple_online<fifi::binary16>();
}


