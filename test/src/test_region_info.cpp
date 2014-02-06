// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/fifi_utils.hpp>
#include <fifi/final.hpp>
#include <fifi/prime2325.hpp>
#include <fifi/region_info.hpp>

#include <gtest/gtest.h>

namespace fifi
{

    // Put dummy layers and tests classes in an anonymous namespace
    // to avoid violations of ODF (one-definition-rule) in other
    // translation units
    namespace
    {
        template<class Field>
        struct dummy_stack : public
        region_info<Field,
        final<Field> >
        { };
    }
}

template<class Field>
inline void test_region_info()
{
    typedef typename Field::value_type value_type;

    fifi::dummy_stack<Field> stack;

    for(uint32_t i = sizeof(value_type); i < 256; i += sizeof(value_type))
    {
        stack.set_length(i);
        EXPECT_EQ(i, stack.length());
        EXPECT_EQ(fifi::length_to_size<Field>(i), stack.size());
        stack.set_size(i);
        EXPECT_EQ(i, stack.size());
        EXPECT_EQ(fifi::size_to_length<Field>(i), stack.length());
    }
}

TEST(TestRegionInfo, binary)
{
    test_region_info<fifi::binary>();
}

TEST(TestRegionInfo, binary4)
{
    test_region_info<fifi::binary4>();
}

TEST(TestRegionInfo, binary8)
{
    test_region_info<fifi::binary8>();
}
TEST(TestRegionInfo, binary16)
{
    test_region_info<fifi::binary16>();
}

TEST(TestRegionInfo, prime2325)
{
    test_region_info<fifi::prime2325>();
}
