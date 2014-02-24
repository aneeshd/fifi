// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/final.hpp>
#include <fifi/region_dispatcher.hpp>
#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>

#include <gtest/gtest.h>
#include <sak/aligned_allocator.hpp>

namespace fifi
{

    namespace
    {

        template<class Super>
        class dummy : public Super
        {

        public:

            typedef typename Super::field_type field_type;

            typedef typename Super::value_type value_type;

        public:

            void region_add(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                (void)dest;
                (void)src;
                (void)length;
            }
            void region_subtract(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                (void)dest;
                (void)src;
                (void)length;
            }
            void region_divide(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                (void)dest;
                (void)src;
                (void)length;
            }
            void region_multiply(value_type* dest, const value_type* src,
                uint32_t length) const
            {
                (void)dest;
                (void)src;
                (void)length;
            }
            void region_multiply_add(value_type* dest, const value_type* src,
                              value_type constant, uint32_t length) const
            {
                (void)dest;
                (void)src;
                (void)constant;
                (void)length;
            }
            void region_multiply_subtract(value_type* dest,
                const value_type* src, value_type constant,
                uint32_t length) const
            {
                (void)dest;
                (void)src;
                (void)constant;
                (void)length;
            }
        };
    }
}

#include <iostream>

TEST(TestRegionEqualAlignment, api)
{
    std::cout << "TestRegionEqualAlignment NOT IMPLEMENTED" << std::endl;
}
