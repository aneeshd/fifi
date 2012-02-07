// Copyright Steinwurf APS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE_1_0.txt or
// http://www.steinwurf.dk/licensing
#ifndef FIFI_FULL_TABLE_H
#define FIFI_FULL_TABLE_H

#include <algorithm>
#include <cmath>
#include <cassert>
#include <stdint.h>
#include <vector>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include "simple_online.h"
#include "binary_extension_field.h"

namespace fifi
{
    
    // Produces a full lookup table of the multiplication and division operations.
    // The full look-up table works fine for the 2^8 binary extension field.
    // However, for higher field sizes it will most likely not work due to the very
    // high memory requirements.
    template<class Field>
    class full_table : public binary_extension_field<Field>
    {        
    public:

        // Typedef of the data type used for each field element
        typedef typename Field::value_type value_type;

        // Typedef of the field type used
        typedef Field field_type;
        
    public:

        // Constructor
        full_table();
        
        // Performs the field multiplication
        // @param element_one, the first field element
        // @param element_one, the second field element
        // @return the result after multiplication
        value_type multiply(value_type element_one, value_type element_two) const;

        // Performs the field division
        // @param numerator, the numerator field element
        // @param denominator, the denominator field element
        // @return the result after division
        value_type divide(value_type numerator, value_type denominator) const;

        // Operator performing the field inversion
        // @param element, the field element to be inverted
        // @return the result after inversion
        value_type invert(value_type element) const;
        
    public:

        // The multiplication table.
        std::vector<value_type> m_multtable;

        // The division table
        std::vector<value_type> m_divitable;

        // Assess to the simple online algorithms
        using binary_extension_field<Field>::m_simple_online;
    };

    template<class Field>
    full_table<Field>::full_table()
    {
        m_multtable.resize(Field::order * Field::order, '\0');
        m_divitable.resize(Field::order * Field::order, '\0');

        for(uint32_t i = 0; i < Field::order; ++i)
        {
            int offset = i * Field::order;

            for(uint32_t j = 0; j < Field::order; ++j)
            {
                m_multtable[offset + j] = m_simple_online.multiply(i,j);

                if(j == 0) // Cannot divide by zero
                    continue;

                m_divitable[offset + j] = m_simple_online.divide(i,j);
            }
        }
    }

    template<class Field>
    inline typename full_table<Field>::value_type
    full_table<Field>::multiply(value_type element_one, value_type element_two) const
    {
        return m_multtable[(element_one << Field::degree) + element_two];
    }

    template<class Field>
    inline typename full_table<Field>::value_type
    full_table<Field>::divide(value_type numerator, value_type denominator) const
    {
        return m_divitable[(numerator << Field::degree) + denominator];
    }

    template<class Field>
    inline typename full_table<Field>::value_type
    full_table<Field>::invert(value_type element) const
    {
        return divide(1, element);
    }

}

#endif

