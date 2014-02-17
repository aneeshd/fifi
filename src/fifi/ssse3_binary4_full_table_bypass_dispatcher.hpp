// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>

#include "ssse3_binary4_full_table_dispatcher.hpp"

#include "binary4.hpp"

namespace fifi
{

    /// Fall through for other fields
    template<class Field, class Super>
    class ssse3_binary4_full_table_bypass_dispatcher :
        public ssse3_binary4_full_table_dispatcher<Field, Super>
    {
    };

    template<class Super>
    class ssse3_binary4_full_table_bypass_dispatcher<binary4, Super> :
        public ssse3_binary4_full_table_dispatcher<binary4, Super>
    {
    public:

        typedef ssse3_binary4_full_table_dispatcher<binary4, Super> RealSuper;

        /// The field type
        typedef typename Super::field_type field_type;

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

        /// We expect the field to be binary4
        static_assert(std::is_same<field_type, binary4>::value,
                      "We expected the Super to use the binary4 field");

        void region_multiply_constant(value_type* dest, value_type constant,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(((uintptr_t)dest % Super::alignment()) == 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            uint32_t bypass_length = length % RealSuper::granularity();

            if(bypass_length == 0)
            {
                RealSuper::region_multiply_constant(dest, constant, length);
            }
            else
            {
                Super::region_multiply_constant(dest, constant, length);
            }
        }

        uint32_t length_granularity() const
        {
            return Super::length_granularity();
        }

        uint32_t alignment() const
        {
            return Super::alignment();
        }
    };
}
