// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>

#include "binary.hpp"
#include "prime2325.hpp"
#include "is_valid_element.hpp"

namespace fifi
{
    /// Produces an extended log table for multiplication and division.
    /// A fall-through specialization for the binary has been added as
    /// the table creation requires arithemetics not supported by that field.
    template<class Super>
    class extended_log_table_arithmetic : public Super
    {
    public:
        static_assert(!std::is_same<prime2325, typename Super::field_type>::value,
              "This layer does not support the 2^32 - 5 prime field");
        static_assert(!std::is_same<binary, typename Super::field_type>::value,
              "This layer does not support the binary field");

        /// The field type
        typedef typename Super::field_type field_type;

        /// Typedef of the data type used for each field element
        typedef typename field_type::value_type value_type;

        /// Typedef of the data type used for each field element
        typedef typename field_type::order_type order_type;

    public:

        /// Constructor
        extended_log_table_arithmetic()
        {
            m_log_data.resize(field_type::order, '\0');
            m_antilog_data.resize((3 * field_type::order) - 5, '\0');

            // Array offsets
            uint32_t low_offset  = 0;
            uint32_t mid_offset  = low_offset + field_type::order - 2;
            uint32_t high_offset = mid_offset + field_type::order - 1;

            // inital value corresponds x^0
            value_type power = 1;

            for(order_type i = 0; i < field_type::order - 1; ++i)
            {
                m_log_data[power] = i;
                m_antilog_data[mid_offset + i] = power;

                // The decimal value 2 corresponds to the
                // polynomial element 'x'
                power = Super::multiply(2U, power);
            }

            for(order_type i = 0; i < field_type::order - 2; ++i)
            {
                m_antilog_data[low_offset  + i] =
                    m_antilog_data[mid_offset + i + 1];

                m_antilog_data[high_offset + i] =
                    m_antilog_data[mid_offset + i];
            }

            // Set the pointers
            m_log = &m_log_data[0];
            m_antilog = &m_antilog_data[0] + field_type::order - 2;
        }

        /// @copydoc finite_field::multiply()
        value_type multiply(value_type a, value_type b) const
        {
            assert(is_valid_element<field_type>(a));
            assert(is_valid_element<field_type>(b));

            if(a == 0 || b == 0)
                return 0;

            value_type one = m_log[a];
            value_type two = m_log[b];

            return m_antilog[one + two];
        }

        /// @copydoc finite_field::divide()
        value_type divide(value_type numerator, value_type denominator) const
        {
            assert(is_valid_element<field_type>(numerator));
            assert(is_valid_element<field_type>(denominator));
            assert(denominator != 0);

            if(numerator == 0)
                return 0;

            value_type one = m_log[numerator];
            value_type two = m_log[denominator];

            return m_antilog[one - two];
        }

        /// @copydoc finite_field::invert()
        value_type invert(value_type a) const
        {
            assert(is_valid_element<field_type>(a));
            assert(a != 0);
            return divide(1, a);
        }

    public:

        /// The Log table
        std::vector<value_type> m_log_data;

        /// Pointer to the Log table data
        value_type *m_log;

        /// The AntiLog table
        std::vector<value_type> m_antilog_data;

        /// Pointer to the AntiLog table data, adjusted so that
        /// negative exponent sums are handled.
        /// I.e. m_antilog[-1] is valid.
        value_type *m_antilog;

    };
}
