// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/final_label.hpp>

#include <gtest/gtest.h>


namespace fifi
{
    namespace
    {
        struct end
        { };

        class dummy : public final_label<end>
        { };
    }
}

// A simple test for a simple class.
TEST(TestFinalLabel, final_label)
{
    fifi::dummy f;
    (void)f;
}
