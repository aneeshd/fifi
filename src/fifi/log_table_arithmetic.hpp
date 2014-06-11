// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <vector>

#include "is_valid_element.hpp"
#include "binary.hpp"
#include "prime2325.hpp"
#include "sum_modulo.hpp"

namespace fifi
{
    /// Produces an log table for multiplication and division.
    template<class Field, class Super>
    class log_table_arithmetic : public Super
    {
    public:

        /// @copydoc layer::field_type
        typedef Field field_type;

        /// @copydoc layer::value_type
        typedef typename field_type::value_type value_type;

        /// @copydoc layer::order_type
        typedef typename field_type::order_type order_type;

        /// Check for prime2325 field
        static_assert(!std::is_same<prime2325, field_type>::value,
            "This layer does not support the 2^32 - 5 prime field");

        /// Check for binary field
        static_assert(!std::is_same<binary, field_type>::value,
            "This layer does not support the binary field");

    public:

        /// Constructor
        log_table_arithmetic()
        {
            m_log.resize(Field::order, '\0');
            m_antilog.resize(Field::order, '\0');

            // initial value corresponds x^0
            value_type power = 1;

            for (order_type i = 0; i < Field::order - 1; ++i)
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

        /// @copydoc layer::multiply(value_type, value_type) const
        value_type multiply(value_type a, value_type b) const
        {
            assert(is_valid_element<field_type>(a));
            assert(is_valid_element<field_type>(b));

            if (a == 0 || b == 0)
                return 0;

            value_type one = m_log[a];
            value_type two = m_log[b];

            value_type sum = sum_modulo<field_type>(one, two);

            // Notice that we handle the case where sum is equal to
            // 2^m - 1, by remapping this entry in the AntiLog table
            // to 1
            return m_antilog[sum];
        }

        /// @copydoc layer::divide(value_type, value_type) const
        value_type divide(value_type a, value_type b) const
        {
            assert(is_valid_element<field_type>(a));
            assert(is_valid_element<field_type>(b));

            assert(b != 0);

            if (a == 0)
                return 0;

            value_type one = m_log[a];
            value_type two = m_log[b];

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

        /// @copydoc layer::invert(value_type) const
        value_type invert(value_type a) const
        {
            assert(is_valid_element<field_type>(a));
            assert(a != 0);

            value_type power = m_log[a];

            // See log_table_arithmetic::divide
            power = Field::max_value - power;

            return m_antilog[power];
        }

    private:

        /// The Log table
        std::vector<value_type> m_log;

        /// The AntiLog table
        std::vector<value_type> m_antilog;
    };
}
