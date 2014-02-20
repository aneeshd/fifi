// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <vector>

#include <fifi/fifi_utils.hpp>

#include <iostream>
#include <string>

namespace fifi
{
    template<class Field>
    class helper_test_buffer
    {

    public:

        typedef typename Field::value_type value_type;

        helper_test_buffer(uint32_t length, uint32_t alignment,
            bool no_zero = false) :
            m_length(length),
            m_alignment(alignment),
            m_offset(0)
        {
            assert(m_length != 0);
            std::cout << "create helper test buffer" << std::endl;
            uint32_t elements = length_to_elements<Field>(m_length);

            std::cout << "elements " << std::to_string(elements) << std::endl;

            m_data.resize(elements_to_length<Field>(elements + m_alignment));

            for(uint32_t i = 0; i < m_alignment; i++)
            {
                if(((((uintptr_t) &m_data[i]) % m_alignment)) == 0)
                {
                    std::cout << "i: " << std::to_string(i) << std::endl;
                    m_offset = i;
                    break;
                }
            }

            for (uint32_t i = 0; i < elements; ++i)
            {
                value_type v = rand() % Field::order;
                if (no_zero && v == 0)
                {
                    v++;
                }

                fifi::set_value<Field>(data(), i, v);
            }
        }

        value_type* data()
        {
            return (value_type*)(((uint8_t*)m_data.data()) + m_offset);
        }

        helper_test_buffer& operator=(const helper_test_buffer &other)
        {
            if (this != &other) // protect against invalid self-assignment
                return *this;

            m_length = other.m_length;
            m_alignment = other.m_alignment;

            uint32_t elements = length_to_elements<Field>(m_length) +
                m_alignment;

            m_data.resize(elements_to_length<Field>(elements));

            for(uint32_t i = 0; i < m_alignment; i++)
            {
                if(((((uintptr_t) &m_data[i]) % m_alignment)) == 0)
                {
                    m_offset = i;
                    break;
                }
            }

            for (int i = 0; i < elements; ++i)
            {
                set_value<Field>(data(), i, get_value<Field>(other.data(), i));
            }

            return *this;
        }

        bool operator==(const helper_test_buffer &other) const
        {
            return true;
        }

        bool operator!=(const helper_test_buffer &other) const
        {
            return !(*this == other);
        }

        uint32_t length() const
        {
            return m_length;
        }

    private:

        uint32_t m_length;
        uint32_t m_alignment;
        std::vector<value_type> m_data;
        uint32_t m_offset;
    };

    SEGMENTATION FAULT

}
