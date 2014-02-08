// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>

#include "is_packed_constant.hpp"

namespace fifi
{

    /// Fall through for other fields
    template<class Field, class Super>
    class dispatcher_binary4_sse3_region_arithmetic : public Super
    { };


    /// @todo
    template<class Super>
    class dispatcher_binary4_sse3_region_arithmetic<binary4, Super>
        : public Super
    {
    public:

        /// The field type
        typedef typename Super::field_type field_type;

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

        /// We expect the value_type to be uint8_t
        static_assert(std::is_same<field_type, uint8_t>::value,
                      "We expect uint8_t as value_type in this specialization");

    public:

        // binary4_sse_region_arithmetic()
        // {
        //     if(has_sse3 && Super::has_sse3())
        //     {
        //         m_multiply = &sse3_region_multiply_constant;
        //     }
        //     else
        //     {
        //         m_multiply = Super::region_multiply_constant;

        // void region_add(value_type* dest, const value_type* src) const
        // {
        //     assert(dest != 0);
        //     assert(src  != 0);
        //     assert(Super::length() > 0);

        //     for(uint32_t i = 0; i < Super::length(); ++i)
        //     {
        //         dest[i] = Super::packed_add(dest[i], src[i]);
        //     }

        // }

        // void region_subtract(value_type* dest, const value_type* src) const
        // {
        //     assert(dest != 0);
        //     assert(src  != 0);
        //     assert(Super::length() > 0);
        //     for(uint32_t i = 0; i < Super::length(); ++i)
        //     {
        //         dest[i] = Super::packed_subtract(dest[i], src[i]);
        //     }
        // }

        // void region_divide(value_type* dest, const value_type* src) const
        // {
        //     assert(dest != 0);
        //     assert(src  != 0);
        //     assert(Super::length() > 0);
        //     for(uint32_t i = 0; i < Super::length(); ++i)
        //     {
        //         dest[i] = Super::packed_divide(dest[i], src[i]);
        //     }
        // }

        // void region_multiply(value_type* dest, const value_type* src) const
        // {
        //     assert(dest != 0);
        //     assert(src  != 0);
        //     assert(Super::length() > 0);
        //     for(uint32_t i = 0; i < Super::length(); ++i)
        //     {
        //         dest[i] = Super::packed_multiply(dest[i], src[i]);
        //     }
        // }

        // void region_multiply_constant(
        //     value_type* dest, value_type constant) const
        // {
        //     assert(dest != 0);
        //     assert(Super::length() > 0);
        //     assert(is_packed_constant<field_type>(constant));
        //     for(uint32_t i = 0; i < Super::length(); ++i)
        //     {
        //         dest[i] = Super::packed_multiply(dest[i], constant);
        //     }
        // }

        // void region_multiply_add(value_type* dest, const value_type* src,
        //                   value_type constant) const
        // {
        //     assert(dest != 0);
        //     assert(src  != 0);
        //     assert(Super::length() > 0);
        //     assert(is_packed_constant<field_type>(constant));
        //     for(uint32_t i = 0; i < Super::length(); ++i)
        //     {
        //         value_type v = Super::packed_multiply(src[i], constant);
        //         dest[i] = Super::packed_add(dest[i], v);
        //     }
        // }

        // void region_multiply_subtract(value_type* dest, const value_type* src,
        //                         value_type constant) const
        // {
        //     assert(dest != 0);
        //     assert(src  != 0);
        //     assert(Super::length() > 0);
        //     assert(is_packed_constant<field_type>(constant));
        //     for(uint32_t i = 0; i < Super::length(); ++i)
        //     {
        //         value_type v = Super::packed_multiply(src[i], constant);
        //         dest[i] = Super::packed_subtract(dest[i], v);
        //     }
        // }
    };
}
