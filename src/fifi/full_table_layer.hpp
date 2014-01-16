// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <algorithm>
#include <cmath>
#include <cassert>
#include <stdint.h>
#include <vector>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace fifi
{
    /// Produces a full lookup table of the multiplication and division operations.
    /// The full look-up table works fine for the 2^8 binary extension field.
    /// However, for higher field sizes it will most likely not work due to the very
    /// high memory requirements.
    template<class Field, class Super>
    class full_table_layer : public Super
    {
    public:

        /// Typedef of the data type used for each field element
        typedef typename Field::value_type value_type;

        /// Typedef of the field type used
        typedef Field field_type;

    public:

        /// Constructor
        full_table_layer()
        {
            m_multtable.resize(Field::order * Field::order, '\0');
            m_divitable.resize(Field::order * Field::order, '\0');

            for(uint32_t i = 0; i < Field::order; ++i)
            {
                int offset = i * Field::order;

                for(uint32_t j = 0; j < Field::order; ++j)
                {
                    m_multtable[offset + j] = Super::multiply(i,j);

                    if(j == 0) // Cannot divide by zero
                        continue;

                    m_divitable[offset + j] = Super::divide(i,j);
                }
            }
        }

        /// @copydoc finite_field::multiply()
        value_type multiply(value_type element_one, value_type element_two) const
        {
            return m_multtable[(element_one << Field::degree) + element_two];
        }

        /// @copydoc finite_field::divide()
        value_type divide(value_type numerator, value_type denominator) const
        {
            return m_divitable[(numerator << Field::degree) + denominator];
        }

        /// @copydoc finite_field::invert()
        value_type invert(value_type element) const
        {
            return divide(1, element);
        }

    public:

        /// The multiplication table.
        std::vector<value_type> m_multtable;

        /// The division table
        std::vector<value_type> m_divitable;

    };

}


