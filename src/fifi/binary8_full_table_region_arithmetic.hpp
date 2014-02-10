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

    template<class Field, class Super>
    class binary8_full_table_region_arithmetic : public Super
    { };

    template<class Super>
    class binary8_full_table_region_arithmetic<fifi::binary8, Super>
        : public Super
    {
    public:

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

    public:

        /// @copydoc region_arithmetic::region_multiply_add(value_type*,
        ///              value_type*, value_type)
        void region_multiply_add(value_type* dest, const value_type* src,
                          value_type constant) const
        {
            assert(dest != 0);
            assert(src != 0);
            assert(Super::length() > 0);

            if (constant == 0)
                return;

            // In the multiplication table the constant is used to identify
            // the row number. Therefore the constant is used as an offset,
            // and all possible results can then be accessed on the following
            // number of indices.
            const value_type *offset =
                &Super::m_multtable[(constant << binary8::degree)];

            for (uint32_t i = 0; i < Super::length(); ++i)
            {
                value_type v = offset[src[i]];
                dest[i] = Super::packed_add(v, dest[i]);
            }
        }

        /// @copydoc region_arithmetic::region_multiply_subtract(value_type*,
        ///              value_type*, value_type)
        void region_multiply_subtract(value_type* dest, const value_type* src,
            value_type constant) const
        {
            // In the binary extension fields add and subtract are the same
            region_multiply_add(dest, src, constant);
        }
    };
}
