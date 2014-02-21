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

        helper_test_buffer(uint32_t length, bool no_zero = false) :
            m_length(length)
        {
            assert(m_length != 0);
            uint32_t elements = length_to_elements<Field>(m_length);

            m_data.resize(elements_to_length<Field>(elements));

            for (uint32_t i = 0; i < elements; ++i)
            {
                value_type v = rand() % Field::order;
                if (no_zero && v == 0)
                {
                    v++;
                }

                fifi::set_value<Field>(m_data.data(), i, v);
            }
        }

        value_type* data()
        {
            return m_data.data();
        }

        helper_test_buffer& operator=(const helper_test_buffer &other)
        {
            if (this != &other) // protect against invalid self-assignment
                return *this;

            m_length = other.m_length;

            uint32_t elements = length_to_elements<Field>(m_length);

            m_data.resize(elements_to_length<Field>(elements));

            for (int i = 0; i < elements; ++i)
            {
                set_value<Field>(data(), i, get_value<Field>(other.data(), i));
            }

            return *this;
        }

        bool operator==(const helper_test_buffer &other) const
        {
            (void)other;
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
}
