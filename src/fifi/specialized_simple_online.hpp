// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

#include "fifi_utils.hpp"
#include "is_valid_element.hpp"
#include "field_types.hpp"

namespace fifi
{

    /// Fall-through for all other cases than binary
    template<class Field, class Super>
    class specialized_simple_online : public Super
    { };

    /// Specialization for the binary field
    template<class Super>
    class specialized_simple_online<binary, Super> : public Super
    {
    public:

        /// The field type
        typedef typename Super::field_type field_type;

        /// The value type
        typedef typename Super::value_type value_type;

        /// Check that the Super uses the same field
        static_assert(std::is_same<field_type, binary>::value,
            "The field specified in the super codes to not match "
            "the Field parameter");

    public:

        /// @copydoc finite_field::multiply()
        value_type multiply(value_type a, value_type b) const
        {
            assert(is_valid_element<field_type>(a));
            assert(is_valid_element<field_type>(b));

            return a & b;
        }

        /// @copydoc finite_field::divide()
        value_type divide(value_type numerator, value_type denominator) const
        {
            assert(is_valid_element<field_type>(numerator));
            assert(is_valid_element<field_type>(denominator));

            assert(denominator != 0);
            return numerator & denominator;
        }

        /// Zero has no inverse and one is its own inverse
        /// @copydoc finite_field::invert()
        value_type invert(value_type a) const
        {
            assert(is_valid_element<field_type>(a));
            assert(a != 0);
            return a;
        }

    };

}


