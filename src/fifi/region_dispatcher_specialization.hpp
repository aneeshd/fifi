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
    class region_dispatcher_specialization<Field, Stack, Field, Super> :
        public Super
    {
    public:

        /// @copydoc layer::field_type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename Super::value_type value_type;

    public:

        region_dispatcher_specialization()
        {
            Super* stack = this;
            if (m_stack.enabled())
            {
                bind_region_add(&m_stack);
                bind_region_subtract(&m_stack);

                ////////////////////////////////////////////////////////////////
                //TODO: These should be called with m_stack, when implemented://
                ////////////////////////////////////////////////////////////////
                bind_region_multiply(stack);
                bind_region_divide(stack);

                bind_region_multiply_constant(&m_stack);
                bind_region_multiply_add(&m_stack);
                bind_region_multiply_subtract(&m_stack);
            }
            else
            {
                bind_region_add(stack);
                bind_region_subtract(stack);
                bind_region_multiply(stack);
                bind_region_divide(stack);
                bind_region_multiply_constant(stack);
                bind_region_multiply_add(stack);
                bind_region_multiply_subtract(stack);
            }
        }

        template<class TargetStack>
        void bind_region_add(const TargetStack* stack)
        {
            using namespace std::placeholders;
            m_add = std::bind(&TargetStack::region_add, stack, _1, _2, _3);
        }

        template<class TargetStack>
        void bind_region_subtract(const TargetStack* stack)
        {
            using namespace std::placeholders;
            m_subtract = std::bind(
                &TargetStack::region_subtract, stack, _1, _2, _3);
        }

        template<class TargetStack>
        void bind_region_multiply(const TargetStack* stack)
        {
            using namespace std::placeholders;
            m_multiply = std::bind(
                &TargetStack::region_multiply, stack, _1, _2, _3);
        }

        template<class TargetStack>
        void bind_region_divide(const TargetStack* stack)
        {
            using namespace std::placeholders;
            m_divide = std::bind(
                &TargetStack::region_divide, stack, _1, _2, _3);
        }

        template<class TargetStack>
        void bind_region_multiply_constant(const TargetStack* stack)
        {
            using namespace std::placeholders;
            m_multiply_constant = std::bind(
                &TargetStack::region_multiply_constant, stack, _1, _2, _3);
        }

        template<class TargetStack>
        void bind_region_multiply_add(const TargetStack* stack)
        {
            using namespace std::placeholders;
            m_multiply_add = std::bind(
                &TargetStack::region_multiply_add, stack, _1, _2, _3, _4);
        }

        template<class TargetStack>
        void bind_region_multiply_subtract(const TargetStack* stack)
        {
            using namespace std::placeholders;
            m_multiply_subtract = std::bind(
                &TargetStack::region_multiply_subtract, stack, _1, _2, _3, _4);
        }

        /// @copydoc layer::region_add(value_type*, const value_type*,
        ///                            uint32_t) const
        void region_add(value_type* dest, const value_type* src,
            uint32_t length) const
        {
//             assert(dest != 0);
//             assert(src  != 0);
//             assert(length > 0);
//             assert(m_add);

            m_add(dest, src, length);
        }

        /// @copydoc layer::region_subtract(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_subtract(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(dest != 0);
            assert(src  != 0);
            assert(length > 0);
            assert(m_subtract);

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
            assert(m_multiply);

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
            assert(m_divide);

            m_divide(dest, src, length);
        }

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
            assert(m_multiply_add);

            m_multiply_add(dest, src, constant, length);
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
            assert(m_multiply_subtract);

            m_multiply_subtract(dest, src, constant, length);
        }

        /// @copydoc layer::alignment()
        uint32_t alignment() const
        {
            if (m_stack.enabled())
            {
                return std::max(m_stack.alignment(),
                                Super::alignment());
            }
            else
            {
                return Super::alignment();
            }
        }

        /// @copydoc layer::max_alignment()
        uint32_t max_alignment() const
        {
            if (m_stack.enabled())
            {
                return std::max(m_stack.max_alignment(),
                                Super::max_alignment());
            }
            else
            {
                return Super::max_alignment();
            }
        }

        /// @copydoc layer::granularity()
        uint32_t granularity() const
        {
            if (m_stack.enabled())
            {
                return std::max(m_stack.granularity(),
                                Super::granularity());
            }
            else
            {
                return Super::granularity();
            }
        }

        /// @copydoc layer::max_granularity()
        uint32_t max_granularity() const
        {
            if (m_stack.enabled())
            {
                return std::max(m_stack.max_granularity(),
                                Super::max_granularity());
            }
            else
            {
                return Super::max_granularity();
            }
        }

        bool enabled() const
        {
            return m_stack.enabled();
        }

    private:

        typedef std::function<void (value_type*, const value_type*, uint32_t)>
            ptr_ptr_function;

        typedef std::function<void (value_type*, value_type, uint32_t)>
            ptr_const_function;

        typedef std::function<
            void (value_type*, const value_type*, value_type, uint32_t)>
            ptr_ptr_const_function;

    private:

        /// The stack to use for dispatching
        Stack m_stack;

        /// Store the function to invoke when calling region_add
        ptr_ptr_function m_add;

        /// Store the function to invoke when calling region_subtract
        ptr_ptr_function m_subtract;

        /// Store the function to invoke when calling region_multiply
        ptr_ptr_function m_multiply;

        /// Store the function to invoke when calling region_divide
        ptr_ptr_function m_divide;

        /// Store the function to invoke when calling region_multiply_constant
        ptr_const_function m_multiply_constant;

        /// Store the function to invoke when calling region_multiply_add
        ptr_ptr_const_function m_multiply_add;

        /// Store the function to invoke when calling region_multiply_subtract
        ptr_ptr_const_function m_multiply_subtract;
    };
}
