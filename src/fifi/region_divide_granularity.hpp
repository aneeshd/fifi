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
    class region_divide_granularity : public Super
    {
    public:

        typedef typename Super::BasicSuper BasicSuper;
        typedef typename Super::OptimizedSuper OptimizedSuper;

        /// The field type
        typedef typename Super::field_type field_type;

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

        void region_add(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src != 0);
            assert(length > 0);
            // check alignment
            assert((uintptr_t)dest % OptimizedSuper::alignment() == 0);
            assert((uintptr_t)src % OptimizedSuper::alignment() == 0);

            auto optimizable = granulated_length(length);
            if (optimizable != 0)
            {
                Super::region_add(dest, src, optimizable);
            }

            auto rest = length - optimizable;
            if (rest != 0)
            {
                BasicSuper::region_add(dest + optimizable,
                    src + optimizable, rest);
            }
        }

        void region_subtract(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src != 0);
            assert(length > 0);
            // check alignment
            assert((uintptr_t)dest % OptimizedSuper::alignment() == 0);
            assert((uintptr_t)src % OptimizedSuper::alignment() == 0);

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

        void region_multiply(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src != 0);
            assert(length > 0);
            // check alignment
            assert((uintptr_t)dest % OptimizedSuper::alignment() == 0);
            assert((uintptr_t)src % OptimizedSuper::alignment() == 0);

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

        void region_divide(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src != 0);
            assert(length > 0);
            // check alignment
            assert((uintptr_t)dest % OptimizedSuper::alignment() == 0);
            assert((uintptr_t)src % OptimizedSuper::alignment() == 0);

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

        void region_multiply_constant(value_type* dest, value_type constant,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));
            // check alignment
            assert((uintptr_t)dest % OptimizedSuper::alignment() == 0);

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

        void region_multiply_add(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src != 0);
            assert(length > 0);
            // check alignment
            assert((uintptr_t)dest % OptimizedSuper::alignment() == 0);
            assert((uintptr_t)src % OptimizedSuper::alignment() == 0);

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

        void region_multiply_subtract(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src != 0);
            assert(length > 0);
            // check alignment
            assert((uintptr_t)dest % OptimizedSuper::alignment() == 0);
            assert((uintptr_t)src % OptimizedSuper::alignment() == 0);

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

    private:

        uint32_t granulated_length(uint32_t length) const
        {
            static uint32_t granularity2 = OptimizedSuper::granularity() *
                                           OptimizedSuper::granularity();
            return length / granularity2;
        }
    };
}
