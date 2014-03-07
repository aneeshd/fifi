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

    /// This layer checks whether two buffers used in region
    /// arithmetics have equal alignment. If the do not then we will
    /// not be able to "adjust" both buffers in a way that they both
    /// become aligned. This can be an issue when using SIMD
    /// acceleration stacks that require alignment.
    template<class Super>
    class region_equal_alignment : public Super
    {
    public:

        /// Typedef to the basic layers i.e. by-passing optimizations
        typedef typename Super::BasicSuper BasicSuper;

        /// Typedef to the optimized layers
        typedef typename Super::OptimizedSuper OptimizedSuper;

        /// @copydoc layer::field_type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename Super::value_type value_type;

    public:

        /// @copydoc layer::region_add(
        ///     value_type*, const value_type*, uint32_t) const
        void region_add(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            if (alignment_is_equal(dest, src))
            {
                Super::region_add(dest, src, length);
            }
            else
            {
                BasicSuper::region_add(dest, src, length);
            }
        }

        /// @copydoc layer::region_subtract(
        ///     value_type*, const value_type*, uint32_t) const
        void region_subtract(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            if (alignment_is_equal(dest, src))
            {
                Super::region_subtract(dest, src, length);
            }
            else
            {
                BasicSuper::region_subtract(dest, src, length);
            }
        }

        /// @copydoc layer::region_divide(
        ///     value_type*, const value_type*, uint32_t) const
        void region_divide(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            if (alignment_is_equal(dest, src))
            {
                Super::region_divide(dest, src, length);
            }
            else
            {
                BasicSuper::region_divide(dest, src, length);
            }
        }

        /// @copydoc layer::region_multiply(
        ///     value_type*, const value_type*, uint32_t) const
        void region_multiply(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            if (alignment_is_equal(dest, src))
            {
                Super::region_multiply(dest, src, length);
            }
            else
            {
                BasicSuper::region_multiply(dest, src, length);
            }
        }

        /// @copydoc layer::region_multiply_add(
        ///     value_type*, const value_type*, value_type, uint32_t) const
        void region_multiply_add(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            if (alignment_is_equal(dest, src))
            {
                Super::region_multiply_add(dest, src, constant, length);
            }
            else
            {
                BasicSuper::region_multiply_add(dest, src, constant, length);
            }
        }

        /// @copydoc layer::region_multiply_subtract(
        ///     value_type*, const value_type*, value_type, uint32_t) const
        void region_multiply_subtract(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            if (alignment_is_equal(dest, src))
            {
                Super::region_multiply_subtract(dest, src, constant, length);
            }
            else
            {
                BasicSuper::region_multiply_subtract(dest, src, constant,
                    length);
            }
        }

    private:

        bool alignment_is_equal(const value_type* dest,
            const value_type* src) const
        {
            return ((uintptr_t)dest % OptimizedSuper::alignment()) ==
                   ((uintptr_t)src  % OptimizedSuper::alignment());
        }
    };
}
