// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>
#include <fifi/prime2325.hpp>

#include <fifi/final.hpp>

#include <gtest/gtest.h>

// Simple test for simple class.
TEST(test_final, final)
{
    fifi::final<fifi::binary> f_binary;
    fifi::final<fifi::binary4> f_binary4;
    fifi::final<fifi::binary8> f_binary8;
    fifi::final<fifi::binary16> f_binary16;
    fifi::final<fifi::prime2325> f_prime2325;

    (void)f_binary;
    (void)f_binary4;
    (void)f_binary8;
    (void)f_binary16;
    (void)f_prime2325;
}
