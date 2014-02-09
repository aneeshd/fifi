// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <fifi/simple_online.hpp>
#include <fifi/optimal_prime.hpp>
#include <fifi/is_packed_constant.hpp>

namespace fifi
{

    template<class Field>
    struct reference_selector
    {
        typedef fifi::simple_online<Field> reference_field;
    };

    template<>
    struct reference_selector<prime2325>
    {
        typedef fifi::optimal_prime<prime2325> reference_field;
    };


    /// This helper can be used to produce reference calculations to
    /// check the implementation of region arithmetics.
    template<class Field>
    class helper_region_reference
    {
    public:

        /// The field type
        typedef Field field_type;

        /// The value type
        typedef typename field_type::value_type value_type;

    public:

        /// Multiply a region with a constant using packed arithmetics
        void region_multiply_constant(
            value_type* dest, value_type constant) const
        {
            assert(dest != 0);
            assert(is_packed_constant<field_type>(constant));
            assert(m_length > 0);

            for(uint32_t i = 0; i < m_length; ++i)
            {
                dest[i] = m_refernce.packed_multiply(dest[i], constant);
            }
        }

        /// Set the size of the region
        void set_length(uint32_t length)
        {
            assert(length > 0);
            m_length = length;
        }

    private:

        /// Store the length of the region
        uint32_t m_length;

        /// Our reference
        typename reference_selector<Field>::reference_field m_refernce;

    };

}

