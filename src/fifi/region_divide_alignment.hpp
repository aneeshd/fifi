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
    /// This layer deals with unaligned buffers in region arithmetics.
    /// The strategy is to divide the computation into two steps:
    ///
    /// 1) In step one we take the data which starts from an unaligned
    /// memory offset and sends it to our basic layer (which does not
    /// impose any alignment requirements).
    ///
    /// 2) In step two we take the remaining buffer which now is
    /// guaranteed to start at an aligned offset and pass it to our
    /// optimized routines.
    /// Requirements:
    /// The layer requires the provided buffers to be of equal alignment, and
    /// furthermore the buffers must be larger than the granularity of the
    /// optimized stack.
    /// These requirements can be handled by region_equal_alignment, and
    /// region_divide_granularity respectively.
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

        /// @copydoc layer::region_add(value_type*, const value_type*,
        ///                            uint32_t) const
        void region_add(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > OptimizedSuper::granularity());

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

        /// @copydoc layer::region_subtract(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_subtract(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > OptimizedSuper::granularity());

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

        /// @copydoc layer::region_multiply(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_multiply(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > OptimizedSuper::granularity());

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

        /// @copydoc layer::region_divide(value_type*, const value_type*,
        ///                               uint32_t) const
        void region_divide(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > OptimizedSuper::granularity());

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

        /// @copydoc layer::region_multiply_constant(value_type*, value_type,
        ///                                          uint32_t) const
        void region_multiply_constant(value_type* dest, value_type constant,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(length > OptimizedSuper::granularity());
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

        /// @copydoc layer::region_multiply_add(value_type*, const value_type*,
        ///                                     value_type, uint32_t) const
        void region_multiply_add(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > OptimizedSuper::granularity());
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

        /// @copydoc layer::region_multiply_subtract(value_type*,
        ///                                          const value_type*,
        ///                                          value_type,
        ///                                          uint32_t) const
        void region_multiply_subtract(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > OptimizedSuper::granularity());
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

    protected:

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
