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
    template<class Super>
    class correct_alignment : public Super
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

            auto aligned_start =
                Super::alignment() - (uintptr_t)dest % Super::alignment();

            auto aligned_length = length - aligned_start;

            if (aligned_start != 0)
            {
                Super::NamedSuper::region_multiply_constant(
                    dest, constant, aligned_start);
            }

            if (aligned_length != 0)
            {
                Super::region_multiply_constant(
                    dest + aligned_start, constant, aligned_length);
            }
        }

        uint32_t alignment() const
        {
            return Super::NamedSuper::alignment();
        }
    };
}
