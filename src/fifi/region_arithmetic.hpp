// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

namespace fifi
{

    /// Region arithmetic makes it easy to perform finite field
    /// arithmetic over memory regions instead of single finite field
    /// elements. Note, that the region arithmetic assumes that the
    /// memory is "packed" i.e. multiple elements per value_type if
    /// possible. See more about packed arithmetic in
    /// packed_arithmetic.hpp.
    /// Also a length is assumed to be available through a call to length
    template<class Super>
    class region_arithmetic : public Super
    {
    public:

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

    public:

        void region_add(value_type* dest, const value_type* src) const
        {
            for(uint32_t i = 0; i < Super::length(); ++i)
            {
                dest[i] = Super::packed_add(dest[i], src[i]);
            }
        }

        void region_subtract(value_type* dest, const value_type* src) const
        {
            for(uint32_t i = 0; i < Super::length(); ++i)
            {
                dest[i] = Super::packed_subtract(dest[i], src[i]);
            }
        }

        void region_divide(value_type* dest, const value_type* src) const
        {
            for(uint32_t i = 0; i < Super::length(); ++i)
            {
                dest[i] = Super::packed_divide(dest[i], src[i]);
            }
        }

        void region_multiply(value_type* dest, const value_type* src) const
        {
            for(uint32_t i = 0; i < Super::length(); ++i)
            {
                dest[i] = Super::packed_multiply(dest[i], src[i]);
            }
        }

        void region_multiply(value_type* dest, value_type constant) const
        {
            for(uint32_t i = 0; i < Super::length(); ++i)
            {
                dest[i] = Super::packed_multiply(dest[i], constant);
            }
        }

        void region_multiply_add(value_type* dest, const value_type* src,
                          value_type constant) const
        {
            for(uint32_t i = 0; i < Super::length(); ++i)
            {
                value_type v = Super::packed_multiply(src[i], constant);
                dest[i] = Super::packed_subtract(dest[i], v);
            }
        }

        void region_multiply_substract(value_type* dest, const value_type* src,
                                value_type constant) const
        {
            for(uint32_t i = 0; i < Super::length(); ++i)
            {
                value_type v = Super::packed_multiply(src[i], constant);
                dest[i] = Super::packed_subtract(dest[i], v);
            }
        }
    };
}
