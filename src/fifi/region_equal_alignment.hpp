// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>

#include "is_packed_constant.hpp"

#include <iostream>

namespace fifi
{
    template<class Super>
    class region_equal_alignment : public Super
    {
    public:

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
            assert(length > 0);

            if (aligment_is_equal(dest, src))
            {
                Super::region_add(dest, src, length);
            }
            else
            {
                Super::NamedSuper::region_add(dest, src, length);
            }
        }

        /// @copydoc layer::region_subtract(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_subtract(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            if (aligment_is_equal(dest, src))
            {
                Super::region_subtract(dest, src, length);
            }
            else
            {
                Super::NamedSuper::region_subtract(dest, src, length);
            }
        }

        /// @copydoc layer::region_divide(value_type*, const value_type*,
        ///                               uint32_t) const
        void region_divide(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            if (aligment_is_equal(dest, src))
            {
                Super::region_divide(dest, src, length);
            }
            else
            {
                Super::NamedSuper::region_divide(dest, src, length);
            }
        }

        /// @copydoc layer::region_multiply(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_multiply(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            if (aligment_is_equal(dest, src))
            {
                Super::region_multiply(dest, src, length);
            }
            else
            {
                Super::NamedSuper::region_multiply(dest, src, length);
            }
        }

        /// @copydoc layer::region_multiply_add(value_type*, const value_type*,
        ///                                     value_type, uint32_t) const
        void region_multiply_add(value_type* dest, const value_type* src,
                          value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            if (aligment_is_equal(dest, src))
            {
                Super::region_multiply_add(dest, src, constant, length);
            }
            else
            {
                Super::NamedSuper::region_multiply_add(dest, src, constant,
                    length);
            }
        }

        /// @copydoc layer::region_multiply_subtract(value_type*,
        ///                                          const value_type*,
        ///                                          value_type, uint32_t) const
        void region_multiply_subtract(value_type* dest, const value_type* src,
                                value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            if (aligment_is_equal(dest, src))
            {
                Super::region_multiply_subtract(dest, src, constant, length);
            }
            else
            {
                Super::NamedSuper::region_multiply_subtract(dest, src, constant,
                    length);
            }
        }

        static uint32_t alignment()
        {
            std::cout << "This is wrongly placed (it should be in region_divide_alignment)" << std::endl;
            return Super::NamedSuper::alignment();
        }

    private:

        bool aligment_is_equal(const value_type* dest,
            const value_type* src) const
        {
            return ((uintptr_t)dest % Super::alignment()) ==
                   ((uintptr_t)src  % Super::alignment());
        }
    };
}
