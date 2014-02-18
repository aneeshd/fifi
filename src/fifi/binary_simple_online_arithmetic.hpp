// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>

#include "is_valid_element.hpp"
#include "binary.hpp"

namespace fifi
{

    /// Fall-through for all other cases than binary
    template<class Field, class Super>
    class binary_simple_online_arithmetic : public Super
    { };

    /// Specialization for the binary field
    template<class Super>
    class binary_simple_online_arithmetic<binary, Super> : public Super
    {
    public:

        /// @copydoc layer::field_type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename Super::value_type value_type;

        /// Check that the Super uses the same field
        static_assert(std::is_same<field_type, binary>::value,
            "The field specified in the super codes to not match "
            "the Field parameter");

    public:

        /// @copydoc layer::multiply(value_type, value_type) const
        value_type multiply(value_type a, value_type b) const
        {
            assert(is_valid_element<field_type>(a));
            assert(is_valid_element<field_type>(b));

            return a & b;
        }

        /// @copydoc layer::divide(value_type, value_type) const
        value_type divide(value_type numerator, value_type denominator) const
        {
            assert(is_valid_element<field_type>(numerator));
            assert(is_valid_element<field_type>(denominator));

            assert(denominator != 0);
            return numerator & denominator;
        }

        /// Zero has no inverse and one is its own inverse
        /// @copydoc layer::invert(value_type) const
        value_type invert(value_type a) const
        {
            assert(is_valid_element<field_type>(a));
            assert(a != 0);
            return a;
        }

    };

}
