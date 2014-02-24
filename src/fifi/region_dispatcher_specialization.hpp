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
    template<class Stack>
    auto bind_region_add(const Stack* stack) -> decltype(
        std::bind(&Stack::region_add,
                  stack,
                  std::placeholders::_1,
                  std::placeholders::_2,
                  std::placeholders::_3))
    {
        return std::bind(&Stack::region_add,
                         stack,
                         std::placeholders::_1,
                         std::placeholders::_2,
                         std::placeholders::_3);
    }


    template<class Stack>
    auto bind_region_multiply_constant(const Stack* stack) -> decltype(
        std::bind(&Stack::region_multiply_constant,
                  stack,
                  std::placeholders::_1,
                  std::placeholders::_2,
                  std::placeholders::_3))
    {
        return std::bind(&Stack::region_multiply_constant,
                         stack,
                         std::placeholders::_1,
                         std::placeholders::_2,
                         std::placeholders::_3);
    }

    template<class Stack>
    auto bind_region_multiply_add(const Stack* stack) -> decltype(
        std::bind(&Stack::region_multiply_add,
                  stack,
                  std::placeholders::_1,
                  std::placeholders::_2,
                  std::placeholders::_3,
                  std::placeholders::_4))
    {
        return std::bind(&Stack::region_multiply_add,
                         stack,
                         std::placeholders::_1,
                         std::placeholders::_2,
                         std::placeholders::_3,
                         std::placeholders::_4);
    }



    /// This class is not to be used in the stacks. Instead use the helper class
    /// region_dispatcher.

    /// Fall through for other fields
    template<class Field, class Stack, class StackField, class Super>
    class region_dispatcher_specialization : public Super
    { };

    /// Dispatcher for the region arithmetics
    template<class Field, class Stack, class Super>
    class region_dispatcher_specialization<Field, Stack, Field, Super>
        : public Super
    {
    public:

        /// @copydoc layer::field_type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename Super::value_type value_type;

    public:

        region_dispatcher_specialization()
        {
            if(Stack::enabled())
            {
                m_add = bind_region_add(&m_stack);
                m_multiply_constant = bind_region_multiply_constant(&m_stack);
                m_multiply_add = bind_region_multiply_add(&m_stack);
            }
            else
            {
                Super* stack = this;
                m_add = bind_region_add(stack);
                m_multiply_constant = bind_region_multiply_constant(stack);
                m_multiply_add = bind_region_multiply_add(stack);
            }
        }


        /// @copydoc layer::region_add(value_type*, const value_type*,
        ///                            uint32_t) const
        void region_add(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            m_add(dest, src, length);
        }

        /*
        /// @copydoc layer::region_subtract(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_subtract(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            m_subtract(dest, src, length);
        }

        /// @copydoc layer::region_multiply(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_multiply(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            m_multiply(dest, src, length);
        }

        /// @copydoc layer::region_divide(value_type*, const value_type*,
        ///                               uint32_t) const
        void region_divide(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);

            m_divide(dest, src, length);
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
            assert(m_multiply_constant);

            m_multiply_constant(dest, constant, length);
        }

        /// @copydoc layer::region_multiply_add(value_type*, const value_type*,
        ///                                     value_type, uint32_t) const
        void region_multiply_add(value_type* dest, const value_type* src,
                          value_type constant, uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);
            assert(is_packed_constant<field_type>(constant));

            m_multiply_add(dest, src, constant, length);
        }

        /*
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

            m_multiply_subtract(dest, src, constant, length);
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

        /// The stack to use for dispatching
        Stack m_stack;

        /// Store the function to invoke when calling region_add
        // typedef decltype(bind_region_add((Stack*)0)) add_type;
        // add_type m_add;
        std::function<void (value_type*, const value_type*, uint32_t)> m_add;
        /*
        /// Store the function to invoke when calling region_subtract
        std::function<void (value_type*, value_type*, uint32_t)> m_subtract;

        /// Store the function to invoke when calling region_multiply
        std::function<void (value_type*, value_type*, uint32_t)> m_multiply;

        /// Store the function to invoke when calling region_divide
        std::function<void (value_type*, value_type*, uint32_t)> m_divide;
        */
        /// Store the function to invoke when calling region_multiply_constant
        std::function<void (value_type*, value_type, uint32_t)>
            m_multiply_constant;

        /// Store the function to invoke when calling region_multiply_add
        std::function<void (value_type*, const value_type*, value_type, uint32_t)>
            m_multiply_add;

        /// Store the function to invoke when calling region_multiply_subtract
        // std::function<void (value_type*, value_type*, value_type, uint32_t)>
        //     m_multiply_subtract;

    };
}
