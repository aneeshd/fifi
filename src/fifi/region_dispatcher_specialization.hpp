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
    /// This class is not to be used in the stacks. Instead use the helper class
    /// region_dispatcher.

    /// Fall through for other fields
    template<class Field, class Stack, class StackField, class Super>
    class region_dispatcher_specialization : public Super
    { };

    /// Dispatcher for the region arithmetics
    template<class Field, class Stack, class Super>
    class region_dispatcher_specialization<Field, Stack, Field, Super> : public Super
    {
    public:

        /// @copydoc layer::field_type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename Super::value_type value_type;

    public:

        region_dispatcher_specialization()
        {
            m_region_multiply_constant = dispatch_region_multiply_constant();
        }

        /*
        /// @copydoc layer::region_add(value_type*, const value_type*,
        ///                            uint32_t) const
        void region_add(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

        }

        /// @copydoc layer::region_subtract(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_subtract(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

        }

        /// @copydoc layer::region_divide(value_type*, const value_type*,
        ///                               uint32_t) const
        void region_divide(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

        }

        /// @copydoc layer::region_multiply(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_multiply(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

        }
        */

        /// @copydoc layer::region_multiply_constant(value_type*, value_type,
        ///                                          uint32_t) const
        void region_multiply_constant(
            value_type* dest, value_type constant,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));
            assert(m_region_multiply_constant);

            m_region_multiply_constant(dest, constant, length);
        }

        /*
        /// @copydoc layer::region_multiply_add(value_type*, const value_type*,
        ///                                     value_type, uint32_t) const
        void region_multiply_add(value_type* dest, const value_type* src,
                          value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

        }

        /// @copydoc layer::region_multiply_subtract(value_type*,
        ///                                          const value_type*,
        ///                                          value_type, uint32_t) const
        void region_multiply_subtract(value_type* dest, const value_type* src,
                                value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

        }
        */

        /// @copydoc static layer::alignment()
        static uint32_t alignment()
        {
            if(Stack::enabled())
            {
                return std::max(Stack::alignment(),
                                Super::alignment());
            }
            else
            {
                return Super::alignment();
            }
        }

        /// @copydoc static layer::max_alignment()
        static uint32_t max_alignment()
        {
            if(Stack::enabled())
            {
                return std::max(Stack::max_alignment(),
                                Super::max_alignment());
            }
            else
            {
                return Super::max_alignment();
            }
        }

        /// @copydoc static layer::granularity()
        static uint32_t granularity()
        {
            if(Stack::enabled())
            {
                return std::max(Stack::granularity(),
                                Super::granularity());
            }
            else
            {
                return Super::granularity();
            }
        }

        /// @copydoc static layer::max_granularity()
        static uint32_t max_granularity()
        {
            if(Stack::enabled())
            {
                return std::max(Stack::max_granularity(),
                                Super::max_granularity());
            }
            else
            {
                return Super::max_granularity();
            }
        }

        static bool enabled()
        {
            return Stack::enabled();
        }

    private:

        /// @return A function that dispatches to the "right" function
        /// depending on whether the dispatching stack is enabled or not.
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
                return std::bind(
                    &Super::region_multiply_constant,
                    (Super*)this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3);
            }
        }

    private:

        /// The stack to use for dispatching
        Stack m_stack;

        /// Store the function to invoke when calling region_multiply_constant
        std::function<void (value_type*, value_type, uint32_t)>
            m_region_multiply_constant;

    };
}
