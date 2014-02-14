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
#include <fifi/multithreading_region_info.hpp>
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
        multithreading_region_info<Field,
        region_info<Field,
        final<Field> > >
        { };
    }
}

template<class Field, uint32_t Threads>
inline void test_region_info()
{
    SCOPED_TRACE(Threads);

    typedef typename Field::value_type value_type;

    fifi::dummy_stack<Field> stack;

    EXPECT_EQ(1U, stack.threads());

    // The minimum length depends on the number of threads.
    stack.set_length(Threads);

    stack.set_threads(Threads);

    EXPECT_EQ(Threads, stack.threads());

    for (uint32_t i = sizeof(value_type); i < 256; i += sizeof(value_type))
    {
        if (i % Threads != 0)
            continue;

        stack.set_length(i);
        EXPECT_EQ(i, stack.length());
        EXPECT_EQ(fifi::length_to_size<Field>(i), stack.size());
        EXPECT_EQ(i/Threads, stack.slice());

        if (fifi::size_to_length<Field>(i) % Threads != 0)
            continue;

        stack.set_size(i);
        EXPECT_EQ(i, stack.size());
        EXPECT_EQ(fifi::size_to_length<Field>(i), stack.length());
    }
}

TEST(TestMultithreadingRegionInfo, binary)
{
    test_region_info<fifi::binary, 1>();
    test_region_info<fifi::binary, 2>();
    test_region_info<fifi::binary, 3>();
    test_region_info<fifi::binary, 4>();
}

TEST(TestMultithreadingRegionInfo, binary4)
{
    test_region_info<fifi::binary4,1>();
    test_region_info<fifi::binary4,2>();
    test_region_info<fifi::binary4,3>();
    test_region_info<fifi::binary4,4>();
}

TEST(TestMultithreadingRegionInfo, binary8)
{
    test_region_info<fifi::binary8,1>();
    test_region_info<fifi::binary8,2>();
    test_region_info<fifi::binary8,3>();
    test_region_info<fifi::binary8,4>();
}
TEST(TestMultithreadingRegionInfo, binary16)
{
    test_region_info<fifi::binary16,1>();
    test_region_info<fifi::binary16,2>();
    test_region_info<fifi::binary16,3>();
    test_region_info<fifi::binary16,4>();
}

TEST(TestMultithreadingRegionInfo, prime2325)
{
    test_region_info<fifi::prime2325,1>();
    test_region_info<fifi::prime2325,2>();
    test_region_info<fifi::prime2325,3>();
    test_region_info<fifi::prime2325,4>();
}
