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
    /// The region_divide_alignment layer
    template<class Super>
    class region_divide_alignment : public Super
    {
    public:

        /// Access to the "basic" layers in the stack
        typedef typename Super::BasicSuper BasicSuper;

        /// Access to the "optimized" layers in the stack
        typedef typename Super::OptimizedSuper OptimizedSuper;

        /// @copydoc layer::field_type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename Super::value_type value_type;

    public:

        void region_add(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            auto unaligned = unaligned_head(dest);
            if (unaligned != 0)
            {
                BasicSuper::region_add(dest, src, unaligned);
            }

            auto rest = length - unaligned;
            if (rest != 0)
            {
                Super::region_add(dest + unaligned, src + unaligned, rest);
            }
        }

        void region_subtract(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            auto unaligned = unaligned_head(dest);
            if (unaligned != 0)
            {
                BasicSuper::region_subtract(dest, src, unaligned);
            }

            auto rest = length - unaligned;
            if (rest != 0)
            {
                Super::region_subtract(dest + unaligned, src + unaligned, rest);
            }
        }

        void region_multiply(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            auto unaligned = unaligned_head(dest);
            if (unaligned != 0)
            {
                BasicSuper::region_multiply(dest, src, unaligned);
            }

            auto rest = length - unaligned;
            if (rest != 0)
            {
                Super::region_multiply(dest + unaligned, src + unaligned, rest);
            }
        }

        void region_divide(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            auto unaligned = unaligned_head(dest);
            if (unaligned != 0)
            {
                BasicSuper::region_divide(dest, src, unaligned);
            }

            auto rest = length - unaligned;
            if (rest != 0)
            {
                Super::region_divide(dest + unaligned, src + unaligned, rest);
            }
        }

        void region_multiply_constant(value_type* dest, value_type constant,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            auto unaligned = unaligned_head(dest);
            if (unaligned != 0)
            {
                BasicSuper::region_multiply_constant(dest, constant,
                    unaligned);
            }

            auto rest = length - unaligned;
            if (rest != 0)
            {
                Super::region_multiply_constant(dest + unaligned, constant,
                    rest);
            }
        }

        void region_multiply_add(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            auto unaligned = unaligned_head(dest);
            if (unaligned != 0)
            {
                BasicSuper::region_multiply_add(dest, src, constant,
                    unaligned);
            }

            auto rest = length - unaligned;
            if (rest != 0)
            {
                Super::region_multiply_add(dest + unaligned, src + unaligned,
                    constant, rest);
            }
        }

        void region_multiply_subtract(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            auto unaligned = unaligned_head(dest);
            if (unaligned != 0)
            {
                BasicSuper::region_multiply_subtract(dest, src, constant,
                    unaligned);
            }

            auto rest = length - unaligned;
            if (rest != 0)
            {
                Super::region_multiply_subtract(dest + unaligned,
                    src + unaligned, constant, rest);
            }
        }

    private:

        uint32_t unaligned_head(const value_type* data) const
        {
            uint32_t alignment = OptimizedSuper::alignment();
            uint32_t offset = (uintptr_t)data % alignment;
            // Return zero if the data is aligned
            if (offset == 0)
            {
                return 0;
            }
            else
            {
                const uint32_t value_size = sizeof(value_type);

                // Ensure that we do not split a value_type
                // Do not allow offsets that are not multiples of the value_size
                assert(value_size == 1 || (offset % value_size) == 0);
                // Otherwise calculate the number of bytes
                return (alignment - offset) / value_size;
            }
        }
    };
}
