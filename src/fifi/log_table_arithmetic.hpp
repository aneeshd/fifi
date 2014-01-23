// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <algorithm>
#include <cmath>
#include <cassert>
#include <cstdint>
#include <vector>

#include "sum_modulo.hpp"

namespace fifi
{
    /// Produces an extended log table for multiplication and division.
    template<class Field, class Super>
    class log_table_arithmetic : public Super
    {
    public:

        /// Typedef of the data type used for each field element
        typedef typename Field::value_type value_type;

        /// Typedef of the data type used for each field element
        typedef typename Field::order_type order_type;

        /// Typedef of the field type used
        typedef Field field_type;

    public:

        /// Constructor
        log_table_arithmetic()
        {
            m_log.resize(Field::order, '\0');
            m_antilog.resize(Field::order, '\0');

            // inital value corresponds x^0
            value_type power = 1;

            for(order_type i = 0; i < Field::order - 1; ++i)
            {
                m_log[power] = i;
                m_antilog[i] = power;

                // The decimal value 2 corresponds to the
                // polynomial element 'x'
                power = Super::multiply(2U, power);
            }

            // This handles the special case where the sum of two
            // exponents hit the maximum value and should be reduced
            // to zero. Instead of doing this we map this entry to
            // the same entry as if the sum had been zero.
            m_antilog[Field::max_value] = 1;

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

            value_type sum = sum_modulo<field_type>(one, two);

            // Notice that we handle the case where sum is equal to
            // 2^m - 1, by remapping this entry in the AntiLog table
            // to 1
            return m_antilog[sum];
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

            // Again we have to do a bit of trickery, since we do not
            // have a good way to handle negative numbers when
            // subtracting them we do the following we realize the
            // inverse element of power representation must be inverse
            // exponent = (2^W - 1) - exponent since inverse exponent
            // + exponent = 2^W - 1 and order mod 2^W - 1 = 0

            // Get inverse of denominator
            two = Field::max_value - two;

            // Now we may simply multiply like before
            value_type sum = sum_modulo<field_type>(one, two);

            // Notice that we handle the case where sum is equal to
            // 2^m - 1, by remapping this entry in the AntiLog table
            // to 1
            return m_antilog[sum];
        }

        /// @copydoc finite_field::invert()
        value_type invert(value_type a) const
        {
            assert(is_valid_element<field_type>(a));
            assert(a != 0);

            value_type power = m_log[a];

            // See log_table<Field>::divide
            power = Field::max_value - power;

            return m_antilog[power];
        }

    public:

        /// The Log table
        std::vector<value_type> m_log;

        /// The AntiLog table
        std::vector<value_type> m_antilog;

    };

}
