// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/final.hpp>
#include <fifi/prime2325.hpp>
#include <fifi/region_granularity.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"
/*
namespace fifi
{

    namespace
    {

        template<class Field>
        struct dummy_stack : public region_granularity<final<Field> >
        { };

    }

}

template<class Field>
void test_region_granularity()
{
    fifi::dummy_stack<Field> stack;
    EXPECT_TRUE(stack.size_granularity() > 0);
    EXPECT_TRUE(stack.length_granularity() > 0);
}

TEST(TestRegionGranularity, api)
{
    {
        SCOPED_TRACE("binary");
        test_region_granularity<fifi::binary>();
    }
    {
        SCOPED_TRACE("binary4");
        test_region_granularity<fifi::binary4>();
    }
    {
        SCOPED_TRACE("binary8");
        test_region_granularity<fifi::binary8>();
    }
    {
        SCOPED_TRACE("binary16");
        test_region_granularity<fifi::binary16>();
    }
    {
        SCOPED_TRACE("prime2325");
        test_region_granularity<fifi::prime2325>();
    }
}
*/
