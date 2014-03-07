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

        /// @copydoc layer::region_add(value_type*, const value_type*,
        ///                            uint32_t) const
        void region_add(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            uint32_t mask = (OptimizedSuper::granularity() - 1);
            uint32_t optimized = length & ~mask;

            if (optimized > 0)
            {
                Super::region_add(dest, src, optimized);
            }

            uint32_t tail = length & mask;

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
            assert(src != 0);
            assert(length > 0);

            auto optimizable = granulated_length(length);
            if (optimizable != 0)
            {
                Super::region_subtract(dest, src, optimizable);
            }

            auto rest = length - optimizable;
            if (rest != 0)
            {
                BasicSuper::region_subtract(dest + optimizable,
                    src + optimizable, rest);
            }
        }

        /// @copydoc layer::region_multiply(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_multiply(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src != 0);
            assert(length > 0);

            auto optimizable = granulated_length(length);
            if (optimizable != 0)
            {
                Super::region_multiply(dest, src, optimizable);
            }

            auto rest = length - optimizable;
            if (rest != 0)
            {
                BasicSuper::region_multiply(dest + optimizable,
                    src + optimizable, rest);
            }
        }

        /// @copydoc layer::region_divide(value_type*, const value_type*,
        ///                               uint32_t) const
        void region_divide(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src != 0);
            assert(length > 0);

            auto optimizable = granulated_length(length);
            if (optimizable != 0)
            {
                Super::region_divide(dest, src, optimizable);
            }

            auto rest = length - optimizable;
            if (rest != 0)
            {
                BasicSuper::region_divide(dest + optimizable,
                    src + optimizable, rest);
            }
        }

        /// @copydoc layer::region_multiply_constant(value_type*, value_type,
        ///                                          uint32_t) const
        void region_multiply_constant(value_type* dest, value_type constant,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(length > 0);

            auto optimizable = granulated_length(length);
            if (optimizable != 0)
            {
                Super::region_multiply_constant(dest, constant,
                    optimizable);
            }

            auto rest = length - optimizable;
            if (rest != 0)
            {
                BasicSuper::region_multiply_constant(
                    dest + optimizable, constant, rest);
            }
        }

        /// @copydoc layer::region_multiply_add(value_type*, const value_type*,
        ///                                     value_type, uint32_t) const
        void region_multiply_add(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src != 0);
            assert(length > 0);

            auto optimizable = granulated_length(length);
            if (optimizable != 0)
            {
                Super::region_multiply_add(dest, src, constant,
                    optimizable);
            }

            auto rest = length - optimizable;
            if (rest != 0)
            {
                BasicSuper::region_multiply_add(
                    dest + optimizable, src + optimizable,
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
            assert(src != 0);
            assert(length > 0);

            auto optimizable = granulated_length(length);
            if (optimizable != 0)
            {
                Super::region_multiply_subtract(dest, src, constant,
                    optimizable);
            }

            auto rest = length - optimizable;
            if (rest != 0)
            {
                BasicSuper::region_multiply_subtract(
                    dest + optimizable, src + optimizable,
                    constant, rest);
            }
        }

    protected:

        /// Given a specific length this function return a new length
        /// which is guarenteed to be a multiple of the
        /// granularity. As an example SSSE3 SIMD works 16 bytes at a
        /// time for the binary4 field this corresponds to a
        /// granularity of 16 (containing 32 binary4 field
        /// elements). If we pass a length of 50 to this function we
        /// would return 48 which is the 3 times the granularity. The
        /// remaining two value_type values have to be calculated
        /// using a layer with a lower granularity.
        ///
        /// @param length The length in value_type elements
        /// @return The number of value_type elements which are a multiple of
        /// the granularity
        uint32_t granulated_length(uint32_t length) const
        {
            assert(OptimizedSuper::granularity() != 0);
            assert(length != 0);

            return length - (length % OptimizedSuper::granularity());
        }
    };
}
