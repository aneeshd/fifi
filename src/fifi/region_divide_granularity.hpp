// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>

namespace fifi
{
    /// This is a convenience layer for region arithmetics which guarantees
    /// that the optimized operations are only called on buffer fragments
    /// which have the required granularity, i.e. their length is a multiple
    /// of the granularity.
    template<class Super>
    class region_divide_granularity : public Super
    {
    public:

        /// Access to the "basic" layers in the stack
        typedef typename Super::BasicSuper BasicSuper;

        /// Access to the "optimized" layers in the stack
        typedef typename Super::OptimizedSuper OptimizedSuper;

        /// The field type
        typedef typename Super::field_type field_type;

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

    public:

        region_divide_granularity()
        {
            // The basic granularity needs to be one, i.e., without requirements
            assert(BasicSuper::granularity() == 1U);

            // The granularity needs to be a power of two
            assert((OptimizedSuper::granularity() &
                   (OptimizedSuper::granularity() - 1)) == 0);
        }

        /// @copydoc layer::region_add(value_type*, const value_type*,
        ///                            uint32_t) const
        void region_add(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);

            uint32_t optimized, tail;
            split_length(length, &optimized, &tail);

            if (optimized > 0)
            {
                Super::region_add(dest, src, optimized);
            }

            if (tail > 0)
            {
                BasicSuper::region_add(dest + optimized, src + optimized, tail);
            }
        }

        /// @copydoc layer::region_subtract(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_subtract(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);

            uint32_t optimized, tail;
            split_length(length, &optimized, &tail);

            if (optimized > 0)
            {
                Super::region_subtract(dest, src, optimized);
            }

            if (tail > 0)
            {
                BasicSuper::region_subtract(
                    dest + optimized, src + optimized, tail);
            }
        }

        /// @copydoc layer::region_multiply(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_multiply(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);

            uint32_t optimized, tail;
            split_length(length, &optimized, &tail);

            if (optimized > 0)
            {
                Super::region_multiply(dest, src, optimized);
            }

            if (tail > 0)
            {
                BasicSuper::region_multiply(
                    dest + optimized, src + optimized, tail);
            }
        }

        /// @copydoc layer::region_divide(value_type*, const value_type*,
        ///                               uint32_t) const
        void region_divide(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);

            uint32_t optimized, tail;
            split_length(length, &optimized, &tail);

            if (optimized > 0)
            {
                Super::region_divide(dest, src, optimized);
            }

            if (tail > 0)
            {
                BasicSuper::region_divide(
                    dest + optimized, src + optimized, tail);
            }
        }

        /// @copydoc layer::region_multiply_constant(value_type*, value_type,
        ///                                          uint32_t) const
        void region_multiply_constant(value_type* dest, value_type constant,
            uint32_t length) const
        {
            assert(dest != 0);

            uint32_t optimized, tail;
            split_length(length, &optimized, &tail);

            if (optimized > 0)
            {
                Super::region_multiply_constant(dest, constant, optimized);
            }

            if (tail > 0)
            {
                BasicSuper::region_multiply_constant(
                    dest + optimized, constant, tail);
            }
        }

        /// @copydoc layer::region_multiply_add(value_type*, const value_type*,
        ///                                     value_type, uint32_t) const
        void region_multiply_add(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);

            uint32_t optimized, tail;
            split_length(length, &optimized, &tail);

            if (optimized > 0)
            {
                Super::region_multiply_add(dest, src, constant, optimized);
            }

            if (tail > 0)
            {
                BasicSuper::region_multiply_add(
                    dest + optimized, src + optimized, constant, tail);
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

            uint32_t optimized, tail;
            split_length(length, &optimized, &tail);

            if (optimized > 0)
            {
                Super::region_multiply_subtract(dest, src, constant, optimized);
            }

            if (tail > 0)
            {
                BasicSuper::region_multiply_subtract(
                    dest + optimized, src + optimized, constant, tail);
            }
        }

    protected:

        /// Given a specific length, this function splits the buffer to
        /// two fragments: the optimized fragment will have a length
        /// which is guarenteed to be a multiple of the granularity, and
        /// the tail fragment will contain the remaining data.
        /// As an example SSSE3 SIMD works 16 bytes at a
        /// time for the binary4 field this corresponds to a
        /// granularity of 16 (containing 32 binary4 field
        /// elements). If we pass a length of 50 to this function, the
        /// length of the optimized fragment will be 48 and the tail will
        /// contain the remaining 2 value_type values (which must be processed
        /// by a layer with a lower granularity requirement).
        ///
        /// @param length The length in value_type elements
        /// @param optimized The number of value_type elements which are a
        /// multiple of the granularity
        /// @param tail The number of remaining value_type elements
        void split_length(uint32_t length, uint32_t* optimized,
            uint32_t* tail) const
        {
            assert(length > 0);

            uint32_t granularity = OptimizedSuper::granularity();
            assert(granularity > 0);

            // The granularity mask is used instead of a modulo and subtraction
            // since this part is performance critical
            uint32_t mask = granularity - 1;
            *optimized = length & ~mask;
            *tail = length & mask;
        }
    };
}
