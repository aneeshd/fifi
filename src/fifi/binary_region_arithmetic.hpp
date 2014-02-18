// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>

#include "binary.hpp"
#include "is_packed_constant.hpp"

namespace fifi
{

    template<class Field, class Super>
    class binary_region_arithmetic : public Super
    { };

    template<class Super>
    class binary_region_arithmetic<fifi::binary, Super> : public Super
    {
    public:

        /// @copydoc layer::field_type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename Super::value_type value_type;

    public:

        /// @copydoc layer::region_multiply_constant(value_type* dest,
        ///                                          value_type constant,
        ///                                          uint32_t length) const
        void region_multiply_constant(value_type* dest,
            value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            if (constant == 0)
            {
                std::fill_n(dest, length, 0);
            }
        }

        /// @copydoc layer::region_multiply_add(value_type* dest,
        ///                                     value_type* src,
        ///                                     value_type constant,
        ///                                     uint32_t length) const
        void region_multiply_add(value_type* dest, const value_type* src,
                          value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            if (constant == 0) // Do nothing
            {
                return;
            }
            else // Add the two buffers
            {
                Super::region_add(dest, src, length);
            }
        }

        /// @copydoc layer::region_multiply_subtract(value_type* dest,
        ///                                          value_type* src,
        ///                                          value_type constant,
        ///                                          uint32_t length) const
        void region_multiply_subtract(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            // In the binary extension fields add and subtract are the same
            region_multiply_add(dest, src, constant, length);
        }
    };
}
