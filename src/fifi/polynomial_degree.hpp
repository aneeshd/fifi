// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

namespace fifi
{

    /// @brief This layer implements a simple function for determining
    ///        the degree of a binary extension field polynomial
    ///        representation.
    template<class Field, class Super>
    class polynomial_degree : public Super
    {
    public:

        /// @copydoc layer::value_type
        typedef typename Field::value_type value_type;

        /// @param element A binary extension field element
        /// @return the degree of the polynomial representation of the element.
        uint32_t find_degree(typename Field::value_type element) const
        {
            uint32_t degree = 0;

            // Add a check for unsigned or arithmetic shifts
            element >>= 1;

            while(element > 0)
            {
                ++degree;
                element >>= 1;
            }

            return degree;
        }

    };
}


