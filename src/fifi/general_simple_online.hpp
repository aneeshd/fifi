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

    /// Simple online finite field algorithms - computes the results
    /// on the fly without relying on pre-computed look-up tables etc.
    template<class Super>
    class general_simple_online : public Super
    {
    public:

        /// Typedef of the field type used
        typedef typename Super::field_type field_type;

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

        /// Typedef of the data type used for each field element
        typedef typename field_type::degree_type degree_type;


    public:

        /// @copydoc finite_field::multiply()
        value_type multiply(value_type a, value_type b) const
        {
            assert(is_valid_element<field_type>(a));
            assert(is_valid_element<field_type>(b));

            if((a == 0) || (b == 0))
                return 0;

            value_type high_bit_flag = 0;
            value_type low_bit_flag = 0;

            value_type high_bit_mask = 1U << (field_type::degree - 1);

            value_type result = 0;

            for(degree_type i = 0; i < field_type::degree; ++i)
            {
                low_bit_flag = b & 0x1;

                if( low_bit_flag != 0 )
                {
                    result ^= a;
                }

                high_bit_flag = a & high_bit_mask;

                a <<= 1;
                b >>= 1;

                if( high_bit_flag != 0 )
                {
                    a ^= field_type::prime;
                }
            }

            return result & field_type::max_value;

        }

        /// @copydoc finite_field::divide()
        value_type divide(value_type numerator, value_type denominator) const
        {
            assert(is_valid_element<field_type>(numerator));
            assert(is_valid_element<field_type>(denominator));

            return multiply(invert(denominator), numerator);
        }

        /// @copydoc finite_field::invert()
        value_type invert(value_type a) const
        {
            assert(a != 0); // Zero has no inverse
            assert(is_valid_element<field_type>(a));

            // If element is 1 the inverse is 1, since we had to
            // 'unwrap' the first iteration (see below), we make an
            // explicit check here.
            if(a == 1)
                return 1;

            value_type r_large = field_type::prime;
            value_type r_small = a;

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
        value_type add(value_type a, value_type b) const
        {
            assert(is_valid_element<field_type>(a));
            assert(is_valid_element<field_type>(b));
            return a ^ b;
        }

        /// @copydoc finite_field::subtract()
        value_type subtract(value_type a, value_type b) const
        {
            assert(is_valid_element<field_type>(a));
            assert(is_valid_element<field_type>(b));
            return a ^ b;
        }

    };

}


