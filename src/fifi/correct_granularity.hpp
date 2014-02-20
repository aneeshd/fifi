// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>

#include "binary4.hpp"

namespace fifi
{

    /// Fall through for other fields
    template<class Super>
    class correct_granularity : public Super
    {
    public:

        /// The field type
        typedef typename Super::field_type field_type;

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

        void region_multiply_constant(value_type* dest, value_type constant,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));
            // check alignment
            assert((uintptr_t)dest % Super::alignment() == 0);

            uint32_t optimizable_length = length / Super::granularity() * Super::granularity();
            uint32_t leftover_length = length - optimizable_length;

            if (optimizable_length != 0)
            {
                Super::region_multiply_constant(
                    dest, constant, optimizable_length);
            }

            if (leftover_length != 0)
            {
                Super::NamedSuper::region_multiply_constant(
                    dest + optimizable_length, constant, leftover_length);
            }
        }

        static uint32_t granularity()
        {
            return Super::NamedSuper::granularity();
        }
    };
}
