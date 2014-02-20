// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>

#include "is_packed_constant.hpp"

namespace fifi
{

    /// Fall through for other fields
    template<class Field, class Stack, class StackField, class Super>
    class region_dispatcher : public Super
    { };

    /// @todo
    template<class Field, class Stack, class Super>
    class region_dispatcher<Field, Stack, Field, Super>
        : public Super
    {
    public:

        /// The field type
        typedef typename Super::field_type field_type;

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

    public:

        region_dispatcher()
        {
            m_region_multiply_constant = dispatch_region_multiply_constant();
        }

        void region_multiply_constant(value_type* dest, value_type constant,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));
            assert(m_region_multiply_constant);

            m_region_multiply_constant(dest, constant, length);
        }

        uint32_t granularity() const
        {
            if(m_stack.enabled())
            {
                return std::max(m_stack.granularity(),
                                Super::granularity());
            }
            else
            {
                return Super::granularity();
            }
        }

        uint32_t alignment() const
        {
            if(m_stack.enabled())
            {
                return std::max(m_stack.alignment(),
                                Super::alignment());
            }
            else
            {
                return Super::alignment();
            }
        }

        bool enabled() const
        {
            return m_stack.enabled();
        }

    private:

        std::function<void (value_type*, value_type, uint32_t)>
            dispatch_region_multiply_constant() const
        {
            if(m_stack.enabled())
            {
                return std::bind(
                    &Stack::region_multiply_constant,
                    &m_stack,
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

        Stack m_stack;

        std::function<void (value_type*, value_type, uint32_t)>
            m_region_multiply_constant;

    };
}
