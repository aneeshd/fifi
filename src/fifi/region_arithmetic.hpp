// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>

#include "is_packed_constant.hpp"

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

        /// @copydoc layer::field_type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename Super::value_type value_type;

    public:

        /// @copydoc layer::region_add(value_type*, const value_type*,
        ///                            uint32_t) const
        void region_add(value_type* dest, const value_type* src,
                        uint32_t length) const
        {
            assert(dest != 0);
            assert(src != 0);
            assert(length > 0);

            for (uint32_t i = 0; i < length; ++i)
            {
                dest[i] = Super::packed_add(dest[i], src[i]);
            }
        }

        /// @copydoc layer::region_subtract(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_subtract(value_type* dest, const value_type* src,
                             uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            for (uint32_t i = 0; i < length; ++i)
            {
                dest[i] = Super::packed_subtract(dest[i], src[i]);
            }
        }

        /// @copydoc layer::region_divide(value_type*, const value_type*,
        ///                               uint32_t) const
        void region_divide(value_type* dest, const value_type* src,
                           uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            for (uint32_t i = 0; i < length; ++i)
            {
                dest[i] = Super::packed_divide(dest[i], src[i]);
            }
        }

        /// @copydoc layer::region_multiply(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_multiply(value_type* dest, const value_type* src,
                             uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            for (uint32_t i = 0; i < length; ++i)
            {
                dest[i] = Super::packed_multiply(dest[i], src[i]);
            }
        }

        /// @copydoc layer::region_multiply_constant(value_type*, value_type,
        ///                                          uint32_t) const
        void region_multiply_constant(value_type* dest, value_type constant,
                                      uint32_t length) const
        {
            assert(dest != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            for (uint32_t i = 0; i < length; ++i)
            {
                dest[i] = Super::packed_multiply(dest[i], constant);
            }
        }

        /// @copydoc layer::region_multiply_add(value_type*, const value_type*,
        ///                                     value_type, uint32_t) const
        void region_multiply_add(value_type* dest,
                                 const value_type* src,
                                 value_type constant,
                                 uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            for (uint32_t i = 0; i < length; ++i)
            {
                value_type v = Super::packed_multiply(src[i], constant);
                dest[i] = Super::packed_add(dest[i], v);
            }
        }

        /// @copydoc layer::region_multiply_subtract(value_type*,
        ///                                          const value_type*,
        ///                                          value_type,
        ///                                          uint32_t) const
        void region_multiply_subtract(value_type* dest,
                                      const value_type* src,
                                      value_type constant,
                                      uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            for (uint32_t i = 0; i < length; ++i)
            {
                value_type v = Super::packed_multiply(src[i], constant);
                dest[i] = Super::packed_subtract(dest[i], v);
            }
        }



    };
}
