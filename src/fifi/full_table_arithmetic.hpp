// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>
#include <type_traits>
#include <vector>

#include "binary.hpp"
#include "binary16.hpp"
#include "is_valid_element.hpp"
#include "prime2325.hpp"

namespace fifi
{
    /// Produces a full lookup table of the multiplication and
    /// division operations.  The full look-up table works fine for
    /// the 2^8 binary extension field.  However, for higher field
    /// sizes it will most likely not work due to the very high memory
    /// requirements.
    template<class Field, class Super>
    class full_table_arithmetic : public Super
    {
        // Static check for the prime2325 field, the full lookup table
        // only works with binary extension fields
        static_assert(
            !std::is_same<prime2325, typename Super::field_type>::value,
            "This layer does not support the 2^32 - 5 prime field");

        // Check for the binary16 field the full lookup table cannot
        // be used with binary16 due to the excessive amounts of
        // memory it would require to create the look-up table.
        static_assert(
            !std::is_same<binary16, typename Super::field_type>::value,
            "This layer does not support the binary16 field");

        // The full lookup table does not support the binary field
        static_assert(!std::is_same<binary, typename Super::field_type>::value,
            "This layer does not support the binary field");

    public:

        /// Typedef of the data type used for each field element
        typedef typename Field::value_type value_type;

        /// Typedef of the field type used
        typedef Field field_type;

    public:

        /// Constructor
        full_table_arithmetic()
        {
            m_multtable.resize(Field::order * Field::order, '\0');
            m_divitable.resize(Field::order * Field::order, '\0');

            for (uint32_t i = 0; i < Field::order; ++i)
            {
                int offset = i * Field::order;

                for (uint32_t j = 0; j < Field::order; ++j)
                {
                    m_multtable[offset + j] = Super::multiply(i,j);

                    if (j == 0) // Cannot divide by zero
                        continue;

                    m_divitable[offset + j] = Super::divide(i,j);
                }
            }
        }

        /// @copydoc finite_field::multiply()
        value_type multiply(value_type a, value_type b) const
        {
            assert(is_valid_element<field_type>(a));
            assert(is_valid_element<field_type>(b));

            return m_multtable[(a << Field::degree) + b];
        }

        /// @copydoc finite_field::divide()
        value_type divide(value_type numerator, value_type denominator) const
        {
            assert(is_valid_element<field_type>(numerator));
            assert(is_valid_element<field_type>(denominator));

            return m_divitable[(numerator << Field::degree) + denominator];
        }

        /// @copydoc finite_field::invert()
        value_type invert(value_type a) const
        {
            assert(is_valid_element<field_type>(a));

            return divide(1, a);
        }

    public:

        /// The multiplication table.
        std::vector<value_type> m_multtable;

        /// The division table
        std::vector<value_type> m_divitable;
    };
}
