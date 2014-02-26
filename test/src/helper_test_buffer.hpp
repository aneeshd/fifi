// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <vector>
#include <ostream>
#include <algorithm>

#include <fifi/fifi_utils.hpp>

namespace fifi
{
    /// sizeof(value_type) = 2
    /// alignement = 16
    /// extra = 8
    ///
    /// length = 5
    /// alignement = 8;
    /// ValueType uint16_t
    ///
    ///
    template<class ValueType>
    class helper_test_buffer
    {
    public:

        typedef ValueType value_type;

        helper_test_buffer(uint32_t length, uint32_t alignment) :
            m_length(length),
            m_alignment(alignment),
            m_data_ptr(0)
        {
            // Make sure that the alignment is a multiple of element size
            assert(m_length > 0);
            assert(m_alignment > 0);
            assert((m_alignment % sizeof(value_type)) == 0);

            // Extra length needed to ensure that we can always move
            // the buffer to match the required alignment
            uint32_t extra_length = m_alignment / sizeof(value_type);
            assert(extra_length > 0);

            m_data.resize(length + extra_length);
            assert(((uintptr_t)m_data.data() % sizeof(value_type)) == 0);

            m_data_ptr = find_aligned(m_data.data());

            assert(((uintptr_t)m_data_ptr % m_alignment) == 0);
        }

        helper_test_buffer(const helper_test_buffer &other) :
            m_length(other.m_length),
            m_alignment(other.m_alignment),
            m_data_ptr(0)
        {
            m_data.resize(other.m_data.size());
            m_data_ptr = find_aligned(m_data.data());

            std::copy_n(other.m_data_ptr, m_length, m_data_ptr);
        }

        value_type* find_aligned(value_type* ptr)
        {
            uintptr_t p = reinterpret_cast<uintptr_t>(ptr);
            return (value_type*)(p + (m_alignment - (p % m_alignment)));
        }


        const value_type* data() const
        {
            return m_data_ptr;
        }

        value_type* data()
        {
            return m_data_ptr;
        }

        bool operator==(const helper_test_buffer &other) const
        {
            if(m_length != other.m_length)
                return false;

            return std::equal(m_data_ptr, m_data_ptr + m_length,
                              other.m_data_ptr);
        }

        bool operator!=(const helper_test_buffer &other) const
        {
            return !operator==(other);
        }

        uint32_t length() const
        {
            return m_length;
        }

    private:

        uint32_t m_length;
        uint32_t m_alignment;
        std::vector<ValueType> m_data;
        ValueType* m_data_ptr;
    };

    template<class Field>
    std::ostream& operator<<(std::ostream& os,
        const helper_test_buffer<Field>& buffer)
    {
        os << "[";
        for (uint32_t i = 0; i < buffer.length(); ++i)
        {
            os << (int)buffer.data()[i];
            if(i < buffer.length())
                os  << ", ";
        }
        os << "]";

        return os;
    }

    template<class Field>
    helper_test_buffer<typename Field::value_type> create_random_buffer(
        uint32_t length, uint32_t alignment, bool no_zero)
    {
        typedef typename Field::value_type value_type;

        helper_test_buffer<value_type> buffer(length, alignment);

        uint32_t elements = length_to_elements<Field>(length);

        for (uint32_t i = 0; i < elements; ++i)
        {
            value_type v = rand() % Field::order;

            if (no_zero && v == 0)
            {
                v++;
            }

            fifi::set_value<Field>(buffer.data(), i, v);
        }

        return buffer;
    }
}
