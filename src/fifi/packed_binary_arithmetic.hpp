// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace fifi
{

    template<class Field, class Super>
    class packed_addition : public Super
    {
    public:

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

        /// For all binary extension fields the binary
        /// @copydoc finite_field::packed_add()
        value_type packed_add(value_type element_a, value_type element_b) const
        {
            return element_a ^ element_b;
        }

    };

}
