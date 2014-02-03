// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>

#include "prime2325.hpp"


namespace fifi
{
    template<class Field, class Super>
    class optimal_prime_region_arithmetic : public Super
    { };

    template<class Super>
    class optimal_prime_region_arithmetic<fifi::prime2325, Super> : public Super
    {
    public:

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

    public:

        void region_add(value_type* dest, const value_type* src) const
        {
            assert(dest != 0);
            assert(src != 0);
            assert(Super::length() > 0);

            for(uint32_t i = 0; i < Super::length(); ++i)
            {
                dest[i] = dest[i] + src[i];

                // If dest[i] >= src[i] the we did not have a 32 bit overflow
                //
                //     1 if no overflow
                //     0 if overflow
                //
                // This means that (dest[i] >= src[i]) - 1 becomes:
                //
                //     0 or 0x00000000 if no overflow
                //     -1 or 0xffffffff if overflow
                //
                // An overflow is equivalent to a mod 2^32 since
                // we are working 2^32 - 5 we simply add 5 to
                // compensate
                dest[i] = dest[i] + (5 & ((dest[i] >= src[i]) - 1));

                // Conditional move version
                //dest[i] = dest[i] >= prime2325::prime ?
                //    dest[i] - prime2325::prime : dest[i];

                // The line below does the following:
                // prime2325::prime > dest[i] becomes:
                //
                //     1 if prime is larger
                //     0 if prime is smaller or equal
                //
                // If that means the (prime2325::prime > dest[i]) - 1 becomes:
                //
                //     0 or 0x00000000 if prime is larger
                //     -1 or 0xffffffff if the prime is smaller or equal
                //
                // This mask is then used to determine whether the subtraction
                // with the prime statement is in effect of not
                //
                // Our measurements show that this branch-less version
                // yields a significant performance gain over both the
                // branched and conditional move versions
                dest[i] = dest[i] -
                    (prime2325::prime & ((prime2325::prime > dest[i]) - 1));
            }
        }
        void region_subtract(value_type* dest, const value_type* src) const
        {
            assert(dest != 0);
            assert(src != 0);
            assert(Super::length() > 0);

            for(uint32_t i = 0; i < Super::length(); ++i)
            {
                // If dest[i] >= src[i] then we will not have an underflow
                //
                //     1 if no underflow
                //     0 if underflow
                //
                // This means that (dest[i] >= src[i]) - 1 becomes:
                //
                //     0 or 0x00000000 if no underflow
                //     -1 or 0xffffffff if underflow
                //
                // An underflow is equivalent to a mod 2^32 since
                // we are working 2^32 - 5 we simply subtract 5 to
                // compensate
                dest[i] = (dest[i] - src[i]) - (5 & ((dest[i] >= src[i]) - 1));

                // Different from addition there is no way we can end up
                // above the prime so we don't have to do anything else
            }
        }
    };
}
