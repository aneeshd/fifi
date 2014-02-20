// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <vector>

#include <fifi/fifi_utils.hpp>

namespace fifi
{
    template<class Field>
    class helper_test_buffer
    {

    public:

        typedef typename Field::value_type value_type;

        helper_test_buffer(uint32_t elements, uint32_t alignment, bool no_zero = false) :
            m_elements(elements),
            m_alignment(alignment)
        {
            uint32_t length = elements_to_length<Field>(m_elements) +
                m_alignment;

            m_data(length);

            for(uint32_t i = 0; i < m_alignment; i++)
            {
                if(((((uintptr_t) &m_data[i]) % m_alignment)) == 0)
                {
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

        value_type* data() const
        {
            return m_data.data() + m_alignment;
        }

        helper_test_buffer& operator=(const helper_test_buffer &other)
        {
            if (this != &other) // protect against invalid self-assignment
                return *this;

            m_elements = other.m_elements;
            m_alignment = other.m_alignment;

            uint32_t length = elements_to_length<Field>(m_elements) +
                m_alignment;

            m_data(length);

            for(uint32_t i = 0; i < m_alignment; i++)
            {
                if(((((uintptr_t) &m_data[i]) % m_alignment)) == 0)
                {
                    m_offset = i;
                    break;
                }
            }

            for (int i = 0; i < m_elements; ++i)
            {
                set_value<Field>(data(), i, get_value<Field>(other.data(), i));
            }

            return *this;
        }

    private:

        uint32_t m_elements;
        uint32_t m_alignment;
        std::vector<value_type> m_data;
        uint32_t m_offset;
    };
}
