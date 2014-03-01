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
    enum class region_operation
    {
        NONE,
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        MULTIPLY_CONSTANT,
        MULTIPLY_ADD,
        MULTIPLY_SUBTRACT
    };

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
            m_last_operation = region_operation::ADD;
            m_dest = dest;
            m_src = src;
            m_length = length;
        }

        void region_subtract(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            m_last_operation = region_operation::SUBTRACT;
            m_dest = dest;
            m_src = src;
            m_length = length;
        }

        void region_divide(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            m_last_operation = region_operation::DIVIDE;
            m_dest = dest;
            m_src = src;
            m_length = length;
        }

        void region_multiply(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            m_last_operation = region_operation::MULTIPLY;
            m_dest = dest;
            m_src = src;
            m_length = length;
        }

        void region_multiply_constant(value_type* dest, value_type constant,
            uint32_t length) const
        {
            m_last_operation = region_operation::MULTIPLY_CONSTANT;
            m_dest = dest;
            m_constant = constant;
            m_length = length;
        }

        void region_multiply_add(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            m_last_operation = region_operation::MULTIPLY_ADD;
            m_dest = dest;
            m_src = src;
            m_constant = constant;
            m_length = length;
        }

        void region_multiply_subtract(value_type* dest,
            const value_type* src, value_type constant,
            uint32_t length) const
        {
            m_last_operation = region_operation::MULTIPLY_SUBTRACT;
            m_dest = dest;
            m_src = src;
            m_constant = constant;
            m_length = length;
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

        uint32_t granularity() const
        {
            return m_granularity;
        }

        uint32_t max_granularity() const
        {
            return m_max_granularity;
        }

        void set_granularity(uint32_t granularity)
        {
            m_granularity = granularity;
        }

        void set_max_granularity(uint32_t max_granularity)
        {
            m_max_granularity = max_granularity;
        }

        void clear_test()
        {
            m_last_operation = region_operation::NONE;

            m_dest = 0;
            m_src = 0;
            m_constant = 0;
            m_length = 0;
        }

    public:

        mutable region_operation m_last_operation;

        mutable value_type* m_dest;
        mutable const value_type* m_src;
        mutable value_type m_constant;
        mutable uint32_t m_length;

    private:

        uint32_t m_alignment;
        uint32_t m_max_alignment;
        uint32_t m_granularity;
        uint32_t m_max_granularity;
    };
}
