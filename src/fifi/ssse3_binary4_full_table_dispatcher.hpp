// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>
#include <iostream>
#include <functional>

#include <cpuid/cpuinfo.hpp>

#include "is_packed_constant.hpp"
#include "ssse3_binary4_full_table.hpp"

namespace fifi
{

    /// Fall through for other fields
    template<class Field, class Super>
    class ssse3_binary4_full_table_dispatcher : public Super
    { };


    /// @todo
    template<class Super>
    class ssse3_binary4_full_table_dispatcher<binary4, Super>
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

        ssse3_binary4_full_table_dispatcher()
        {
            m_region_multiply_constant =
                dispatch_region_multiply_constant();
        }

        void region_multiply_constant(
            value_type* dest, value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));
            assert(m_region_multiply_constant);

            m_region_multiply_constant(dest, constant, length);
        }

        uint32_t granularity() const
        {
            if(m_ssse3_binary4.ssse3_binary4_full_table_enabled())
            {
                return std::max(m_ssse3_binary4.granularity(),
                                Super::granularity());
            }
            else
            {
                return Super::granularity();
            }
        }

        uint32_t alignment() const
        {
            if(m_ssse3_binary4.ssse3_binary4_full_table_enabled())
            {
                return std::max(m_ssse3_binary4.alignment(),
                                Super::alignment());
            }
            else
            {
                return Super::alignment();
            }
        }

        bool ssse3_binary4_full_table_enabled() const
        {
            cpuid::cpuinfo info;
            return info.has_ssse3() &&
                   m_ssse3_binary4.ssse3_binary4_full_table_enabled();
        }

    private:

        std::function<void (value_type*, value_type, uint32_t)>
            dispatch_region_multiply_constant() const
        {
            cpuid::cpuinfo info;

            if(info.has_ssse3() &&
               m_ssse3_binary4.ssse3_binary4_full_table_enabled())
            {
                return std::bind(
                    &ssse3_binary4_full_table::region_multiply_constant,
                    &m_ssse3_binary4,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3);
            }
            else
            {
                return std::bind(&Super::region_multiply_constant,
                                 (Super*)this,
                                 std::placeholders::_1,
                                 std::placeholders::_2,
                                 std::placeholders::_3);
            }
        }

    private:

        ssse3_binary4_full_table m_ssse3_binary4;

        std::function<void (value_type*, value_type, uint32_t)>
            m_region_multiply_constant;

    };
}
