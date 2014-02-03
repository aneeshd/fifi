// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>

#include "is_valid_element.hpp"

namespace fifi
{

    /// @brief This layer implements a simple function for determining
    ///        the degree of a binary extension field polynomial
    ///        representation.
    template<class Super>
    class polynomial_degree : public Super
    {
    public:

        /// The field type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename field_type::value_type value_type;

    public:

        /// @param element A binary extension field element
        /// @return the degree of the polynomial representation of the element.
        uint32_t find_degree(value_type a) const
        {
            assert(is_valid_element<field_type>(a));

            uint32_t degree = 0;

            // Add a check for unsigned or arithmetic shifts
            a >>= 1;

            while(a > 0)
            {
                ++degree;
                a >>= 1;
            }

            return degree;
        }

    };
}
