// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/simple_online.hpp>
#include <fifi/binary.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>
#include <fifi/prime2325.hpp>

#include "helper_test_arithmetic.hpp"

TEST(TestSimpleOnline, add)
{
    fifi::check_add<fifi::simple_online>();
}

TEST(TestSimpleOnline, subtract)
{
    fifi::check_subtract<fifi::simple_online>();
}

TEST(TestSimpleOnline, multiply)
{
    fifi::check_multiply<fifi::simple_online>();
}

TEST(TestSimpleOnline, divide)
{
    fifi::check_divide<fifi::simple_online>();
}

TEST(TestSimpleOnline, invert)
{
    fifi::check_invert<fifi::simple_online>();
}
