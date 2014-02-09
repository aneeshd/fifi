// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>
#include <iostream>
#include <functional>

#include "is_packed_constant.hpp"
#include "sse3_binary4_region_arithmetic.hpp"

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

        /// We expect the field to be binary4
        static_assert(std::is_same<field_type, binary4>::value,
                      "We expected the Super to use the binary4 field");

    public:

        dispatcher_binary4_sse3_region_arithmetic()
        {
            if(m_ssse3_binary4.has_sse3())
            {
                std::cout << "Has ssse3" << std::endl;
            }
            else
            {
                std::cout << "NO ssse3" << std::endl;
            }

        }

        bool binary4_ssse3() const
        {
            return false;
        }

        void region_multiply_constant(
            value_type* dest, value_type constant) const
        {
            assert(dest != 0);
            assert(Super::length() > 0);
            assert(is_packed_constant<field_type>(constant));

            static auto dispatch = dispatch_region_multiply_constant();

            dispatch(dest, constant);
        }

        void set_length(uint32_t length)
        {
            assert(length > 0);
            m_ssse3_binary4.set_length(length);
            Super::set_length(length);
        }

        uint32_t length_granularity() const
        {
            return std::max(m_ssse3_binary4.length_granularity(),
                            Super::length_granularity());
        }

    private:

        std::function<void (value_type*, value_type)>
        dispatch_region_multiply_constant() const
        {
            using namespace std::placeholders;  // for _1, _2, _3...

            std::cout << "DISPATCH" << std::endl;

            if(m_ssse3_binary4.has_sse3())
            {
                return std::bind(&sse3_binary4_region_arithmetic::region_multiply_constant,
                          &m_ssse3_binary4, _1, _2);
            }
            else
            {
                return std::bind(&Super::region_multiply_constant, (Super*)this, _1, _2);
            }
        }


    private:

        sse3_binary4_region_arithmetic m_ssse3_binary4;

    };
}
