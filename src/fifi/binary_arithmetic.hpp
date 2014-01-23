// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

#include "fifi_utils.hpp"
#include "is_valid_element.hpp"

namespace fifi
{

    template<class Super>
    class binary_arithmetic : public Super
    {
    public:

        /// Typedef of the data type used for each field element
        typedef typename Super::field_type field_type;

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

        /// @copydoc finite_field::add()
        value_type add(value_type element_a, value_type element_b) const
        {
            assert(is_valid_element<field_type>(element_a));
            assert(is_valid_element<field_type>(element_b));
            return element_a ^ element_b;
        }

        /// @copydoc finite_field::subtract()
        value_type subtract(value_type element_a, value_type element_b) const
        {
            assert(is_valid_element<field_type>(element_a));
            assert(is_valid_element<field_type>(element_b));
            return element_a ^ element_b;
        }
    };

}
