// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>

#include "binary8.hpp"

namespace fifi
{
    /// Fall through case for other fields
    template<class Field, class Super>
    class binary8_region_arithmetic_full_table : public Super
    { };

    /// Specialization for the binary8 field. The layer implements an
    /// optimization for binary8 full table region arithmetics. The
    /// optimization relies on the fact that when multiplying with a
    /// constant this yields a constant offset into the multiplication
    /// table (see below for further details).
    template<class Super>
    class binary8_region_arithmetic_full_table<fifi::binary8, Super>
        : public Super
    {
    public:

        /// @copydoc layer::value_type
        typedef typename Super::value_type value_type;

    public:

        /// @copydoc layer::region_multiply_add(value_type*, value_type*,
        ///                                     value_type, uint32_t) const
        void region_multiply_add(value_type* dest, const value_type* src,
                                 value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src != 0);
            assert(length > 0);

            if (constant == 0)
                return;

            // In the multiplication table the constant is used to identify
            // the row number. Therefore the constant is used as an offset,
            // and all possible results can then be accessed on the following
            // number of indices.
            const value_type* offset =
                &Super::m_multtable[(constant << binary8::degree)];

            for (uint32_t i = 0; i < length; ++i)
            {
                value_type v = offset[src[i]];
                dest[i] = Super::packed_add(v, dest[i]);
            }
        }

        /// @copydoc layer::region_multiply_subtract(value_type*, value_type*,
        ///                                          value_type, uint32_t) const
        void region_multiply_subtract(value_type* dest, const value_type* src,
                                      value_type constant,
                                      uint32_t length) const
        {
            // In the binary extension fields add and subtract are the same
            region_multiply_add(dest, src, constant, length);
        }
    };
}
