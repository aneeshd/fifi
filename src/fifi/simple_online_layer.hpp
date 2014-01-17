// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

#include "fifi_utils.hpp"
#include "can_pack.hpp"

namespace fifi
{
    /// The is_packable is true if the value_type used can contain
    /// multiple field elements
    template<class Field>
    struct is_packable
    {
        typedef typename Field::value_type value_type;

        const static bool value =
            !(Field::max_value == std::numeric_limits<value_type>::max());
    };

    template<class Field>
    typename std::enable_if<enable_is_valid_element<Field>::value, bool>::type
    is_valid_element(typename Field::value_type v)
    {
        return v < Field::max_value;
    }

    template<class Field>
    typename std::enable_if<!enable_is_valid_element<Field>::value, bool>::type
    is_valid_element(typename Field::value_type v)
    {
        (void) v;
        return true;
    }


    /// Simple online finite field algorithms - computes the results
    /// on the fly without relying on pre-computed look-up tables etc.
    template<class Field, class Super>
    class simple_online_layer : public Super
    {
    public:

        /// Typedef of the data type used for each field element
        typedef typename Field::value_type value_type;

        /// Typedef of the data type used for each field element
        typedef typename Field::degree_type degree_type;

        /// Typedef of the field type used
        typedef Field field_type;

    public:

        /// @copydoc finite_field::multiply()
        value_type multiply(value_type element_a, value_type element_b) const
        {
            if((element_a == 0) || (element_b == 0))
                return 0;

            value_type high_bit_flag = 0;
            value_type low_bit_flag = 0;

            value_type high_bit_mask = 1U << (field_type::degree - 1);

            value_type result = 0;

            for(degree_type i = 0; i < field_type::degree; ++i)
            {
                low_bit_flag = element_b & 0x1;

                if( low_bit_flag != 0 )
                {
                    result ^= element_a;
                }

                high_bit_flag = element_a & high_bit_mask;

                element_a <<= 1;
                element_b >>= 1;

                if( high_bit_flag != 0 )
                {
                    element_a ^= field_type::prime;
                }
            }

            return result & field_type::max_value;

        }

        /// @copydoc finite_field::divide()
        value_type divide(value_type numerator, value_type denominator) const
        {
            return multiply(invert(denominator), numerator);
        }

        /// @copydoc finite_field::invert()
        value_type invert(value_type element) const
        {
            assert(element != 0);
            assert(is_valid_element<field_type>(element));

            // If element is 1 the inverse is 1, since we had to
            // 'unwrap' the first iteration (see below), we make an
            // explicit check here.
            if(element == 1)
                return 1;

            value_type r_large = field_type::prime;
            value_type r_small = element;

            value_type y_large = 0;
            value_type y_small = 1;

            // Since we cannot use the element data type to represent
            // the field polynomial we would not get a correct degree
            // calculation in the first iteration. Thus we perform the
            // first iteration of the algorithm here with the correct
            // prime degree. In the following iterations of the
            // algorithm the degree of r_large, which initially holds
            // our polynomial will be representable in value_type
            int32_t j = field_type::degree - Super::find_degree(r_small);

            assert(j > 0);

            r_large ^= (r_small << j);
            y_large ^= (y_small << j);

            r_large &= field_type::max_value;
            y_large &= field_type::max_value;

            while(r_large != 1)
            {
                assert(r_large > 1);

                j = Super::find_degree(r_large) - Super::find_degree(r_small);

                if(j < 0)
                {
                    std::swap(r_large, r_small);
                    std::swap(y_large, y_small);

                    j = std::abs(j);
                }

                r_large ^= (r_small << j);
                y_large ^= (y_small << j);

                r_large &= field_type::max_value;
                y_large &= field_type::max_value;

            }

            return y_large;
        }

        /// @copydoc finite_field::add()
        value_type add(value_type element_a, value_type element_b) const
        {
            return element_a ^ element_b;
        }

        /// @copydoc finite_field::subtract()
        value_type subtract(value_type element_a, value_type element_b) const
        {
            return element_a ^ element_b;
        }

    };


    /// Simple online finite field algorithms - computes the results
    /// on the fly without relying on pre-computed look-up tables etc.
    template<class Super>
    class simple_online_layer<binary, Super> : public Super
    {
    public:

        /// Typedef of the data type used for each field element
        typedef binary::value_type value_type;

        /// Typedef of the data type used for each field element
        typedef binary::degree_type degree_type;

        /// Typedef of the field type used
        typedef binary field_type;

    public:

        /// @copydoc finite_field::multiply()
        value_type multiply(value_type element_a, value_type element_b) const
        {
            return element_a & element_b;
        }

        /// @copydoc finite_field::divide()
        value_type divide(value_type numerator, value_type denominator) const
        {
            assert(denominator != 0);
            return numerator & denominator;
        }

        /// @copydoc finite_field::invert()
        value_type invert(value_type element) const
        {
            assert(element != 0);
            return element;
        }

        /// @copydoc finite_field::add()
        value_type add(value_type element_a, value_type element_b) const
        {
            return element_a ^ element_b;
        }

        /// @copydoc finite_field::subtract()
        value_type subtract(value_type element_a, value_type element_b) const
        {
            return element_a ^ element_b;
        }

    };




}


