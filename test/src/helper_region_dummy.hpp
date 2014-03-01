// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

#include <fifi/binary.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>

#include "expected_results.hpp"

namespace fifi
{
    template<class Super>
    class region_dummy : public Super
    {
    public:

        typedef typename Super::field_type field_type;

        typedef typename Super::value_type value_type;

    public:

        void region_add(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            m_add_dest = dest;
            m_add_src = src;
            m_add_length = length;
        }

        void region_subtract(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            m_subtract_dest = dest;
            m_subtract_src = src;
            m_subtract_length = length;
        }

        void region_divide(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            m_divide_dest = dest;
            m_divide_src = src;
            m_divide_length = length;
        }

        void region_multiply(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            m_multiply_dest = dest;
            m_multiply_src = src;
            m_multiply_length = length;
        }

        void region_multiply_constant(value_type* dest, value_type constant,
            uint32_t length) const
        {
            m_multiply_constant_dest = dest;
            m_multiply_constant_constant = constant;
            m_multiply_constant_length = length;
        }

        void region_multiply_add(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            m_multiply_add_dest = dest;
            m_multiply_add_src = src;
            m_multiply_add_constant = constant;
            m_multiply_add_length = length;
        }

        void region_multiply_subtract(value_type* dest,
            const value_type* src, value_type constant,
            uint32_t length) const
        {
            m_multiply_subtract_dest = dest;
            m_multiply_subtract_src = src;
            m_multiply_subtract_constant = constant;
            m_multiply_subtract_length = length;
        }

        uint32_t alignment() const
        {
            return m_alignment;
        }

        uint32_t max_alignment() const
        {
            return m_max_alignment;
        }

        void set_alignment(uint32_t alignment)
        {
            m_alignment = alignment;
        }

        void set_max_alignment(uint32_t max_alignment)
        {
            m_max_alignment = max_alignment;
        }

        void clear_test()
        {
            m_add_dest = 0;
            m_add_src = 0;
            m_add_length = 0;

            m_subtract_dest = 0;
            m_subtract_src = 0;
            m_subtract_length = 0;

            m_divide_dest = 0;
            m_divide_src = 0;
            m_divide_length = 0;

            m_multiply_dest = 0;
            m_multiply_src = 0;
            m_multiply_length = 0;

            m_multiply_constant_dest = 0;
            m_multiply_constant_constant = 0;
            m_multiply_constant_length = 0;

            m_multiply_add_dest = 0;
            m_multiply_add_src = 0;
            m_multiply_add_constant = 0;
            m_multiply_add_length = 0;

            m_multiply_subtract_dest = 0;
            m_multiply_subtract_src = 0;
            m_multiply_subtract_constant = 0;
            m_multiply_subtract_length = 0;
        }

    public:

        mutable value_type* m_add_dest;
        mutable const value_type* m_add_src;
        mutable uint32_t m_add_length;

        mutable value_type* m_subtract_dest;
        mutable const value_type* m_subtract_src;
        mutable uint32_t m_subtract_length;

        mutable value_type* m_divide_dest;
        mutable const value_type* m_divide_src;
        mutable uint32_t m_divide_length;

        mutable value_type* m_multiply_dest;
        mutable const value_type* m_multiply_src;
        mutable uint32_t m_multiply_length;

        mutable value_type* m_multiply_constant_dest;
        mutable value_type m_multiply_constant_constant;
        mutable uint32_t m_multiply_constant_length;

        mutable value_type* m_multiply_add_dest;
        mutable const value_type* m_multiply_add_src;
        mutable value_type m_multiply_add_constant;
        mutable uint32_t m_multiply_add_length;

        mutable value_type* m_multiply_subtract_dest;
        mutable const value_type* m_multiply_subtract_src;
        mutable value_type m_multiply_subtract_constant;
        mutable uint32_t m_multiply_subtract_length;

    private:

        uint32_t m_alignment;
        uint32_t m_max_alignment;
    };
}
