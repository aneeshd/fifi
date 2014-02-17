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

            auto aligned_start = RealSuper::alignment() - (uintptr_t)dest % RealSuper::alignment();
            auto aligned_length =
                (length - aligned_start) / RealSuper::granularity() * RealSuper::granularity();
            auto aligned_end = aligned_start + aligned_length;


            std::cout << "sizeof(value_type): " << std::to_string(sizeof(value_type)) << std::endl;
            std::cout << "length: " << std::to_string(length) << std::endl;
            std::cout << "dest: " << std::to_string((uintptr_t)dest) << std::endl;

            std::cout << "RealSuper::alignment: " << std::to_string(RealSuper::alignment()) << std::endl;
            std::cout << "RealSuper::granularity: " << std::to_string(RealSuper::granularity()) << std::endl;

            std::cout << "Super::alignment: " << std::to_string(Super::alignment()) << std::endl;
            std::cout << "Super::granularity: " << std::to_string(Super::granularity()) << std::endl;

            std::cout << "aligned_start: " << std::to_string(aligned_start) << std::endl;
            std::cout << "aligned_length: " << std::to_string(aligned_length) << std::endl;
            std::cout << "aligned_end: " << std::to_string(aligned_end) << std::endl;


            if (aligned_start != 0)
            {
                std::cout << "aligned_start" << std::endl;
                Super::region_multiply_constant(dest, constant, aligned_start);
            }

            if (aligned_length != 0)
            {
                std::cout << "aligned_length" << std::endl;
                std::cout << "(uintptr_t)dest mod RealSuper::alignment()): " << (uintptr_t)dest % RealSuper::alignment() << std::endl;
                RealSuper::region_multiply_constant(dest + aligned_start, constant, aligned_length);
            }

            if (length - aligned_end != 0)
            {
                std::cout << "length - aligned_end" << std::endl;
                Super::region_multiply_constant(dest + aligned_end, constant, length - aligned_end);
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
