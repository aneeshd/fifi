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
        value_type packed_add(value_type a, value_type b) const
        {
            return Super::add(a, b);
        }

    };

    template<class Super>
    class packed_addition<binary, Super> : public Super
    {
    public:

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

        /// For all binary extension fields the binary
        /// @copydoc finite_field::packed_add()
        value_type packed_add(value_type a, value_type b) const
        {
            return a ^ b;
        }

    };

    template<class Super>
    class packed_addition<binary4, Super> : public Super
    {
    public:

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

        static_assert(std::is_same<value_type, uint8_t>::value,
                      "The code below assumes we use uint8_t as data type "
                      "for the binary4 field");

        /// For all binary extension fields the binary
        /// @copydoc finite_field::packed_add()
        value_type packed_add(value_type a, value_type b) const
        {
            value_type high = Super::add(a >> 4, b >> 4);
            value_type low = Super::add(a & 0xf, b & 0xf);

            return (high << 4) | low;
        }

    };

}
