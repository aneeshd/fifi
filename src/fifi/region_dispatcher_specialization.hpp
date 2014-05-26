// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <type_traits>

#include <sak/easy_bind.hpp>
#include <sak/optional_bind.hpp>

#include "is_packed_constant.hpp"
#include "has_region_add.hpp"
#include "has_region_subtract.hpp"
#include "has_region_multiply.hpp"
#include "has_region_divide.hpp"
#include "has_region_multiply_constant.hpp"
#include "has_region_multiply_add.hpp"
#include "has_region_multiply_subtract.hpp"

namespace fifi
{

    template<class Field, class Stack, class StackField, class Super>
    class region_dispatcher_specialization : public Super
    { };

    /// Specialization of the dispatcher which is enabled when the main
    /// stack and the dispatch stack have matching fields.
    template<class Field, class Stack, class Super>
    class region_dispatcher_specialization<Field, Stack, Field, Super> :
        public Super
    {
    public:

        /// @copydoc layer::field_type
        using field_type = typename Super::field_type;

        /// @copydoc layer::value_type
        using value_type = typename Super::value_type;

        /// @copydoc super_region_dispatcher_::call_region_add
        using call_region_add =
            typename Super::call_region_add;

        /// @copydoc super_region_dispatcher_::call_region_subtract
        using call_region_subtract =
            typename Super::call_region_subtract;

        /// @copydoc super_region_dispatcher_::call_region_divide
        using call_region_divide =
            typename Super::call_region_divide;

        /// @copydoc super_region_dispatcher_::call_region_multiply
        using call_region_multiply =
            typename Super::call_region_multiply;

        /// @copydoc super_region_dispatcher_::call_region_multiply_constant
        using call_region_multiply_constant =
            typename Super::call_region_multiply_constant;

        /// @copydoc super_region_dispatcher_::call_region_multiply_add
        using call_region_multiply_add =
            typename Super::call_region_multiply_add;

        /// @copydoc super_region_dispatcher_::call_region_multiply_subtract
        using call_region_multiply_subtract =
            typename Super::call_region_multiply_subtract;

    public:

        /// Helper struct for sak::optional_bind. sak::optinal_bind
        /// allows us to "attempt" to bind to a specific function in
        /// the Stack object. However if that function is not defined
        /// by the stack, it will simply return an empty std::function
        /// object.
        struct bind_add
        {
            template<class T>
            static auto bind(const T& t) ->
                decltype(sak::easy_bind(&T::region_add, t))
            {
                return sak::easy_bind(&T::region_add, t);
            }

            using result_type = call_region_add;
        };

        /// @copydoc bind_add
        struct bind_subtract
        {
            template<class T>
            static auto bind(const T& t) ->
                decltype(sak::easy_bind(&T::region_subtract, t))
            {
                return sak::easy_bind(&T::region_subtract, t);
            }

            using result_type = call_region_subtract;
        };

        /// @copydoc bind_add
        struct bind_divide
        {
            template<class T>
            static auto bind(const T& t) ->
                decltype(sak::easy_bind(&T::region_divide, t))
            {
                return sak::easy_bind(&T::region_divide, t);
            }

            using result_type = call_region_divide;
        };

        /// @copydoc bind_add
        struct bind_multiply
        {
            template<class T>
            static auto bind(const T& t) ->
                decltype(sak::easy_bind(&T::region_multiply, t))
            {
                return sak::easy_bind(&T::region_multiply, t);
            }

            using result_type = call_region_multiply;
        };

        /// @copydoc bind_add
        struct bind_multiply_constant
        {
            template<class T>
            static auto bind(const T& t) ->
                decltype(sak::easy_bind(&T::region_multiply_constant, t))
            {
                return sak::easy_bind(&T::region_multiply_constant, t);
            }

            using result_type = call_region_multiply_constant;
        };

        /// @copydoc bind_add
        struct bind_multiply_add
        {
            template<class T>
            static auto bind(const T& t) ->
                decltype(sak::easy_bind(&T::region_multiply_add, t))
            {
                return sak::easy_bind(&T::region_multiply_add, t);
            }

            using result_type = call_region_multiply_add;
        };

        /// @copydoc bind_add
        struct bind_multiply_subtract
        {
            template<class T>
            static auto bind(const T& t) ->
                decltype(sak::easy_bind(&T::region_multiply_subtract, t))
            {
                return sak::easy_bind(&T::region_multiply_subtract, t);
            }

            using result_type = call_region_multiply_subtract;
        };

    public:

        call_region_add
        dispatch_region_add() const
        {
            auto call = sak::optional_bind<bind_add>(&m_stack);

            if (call && m_stack.enabled())
            {
                return call;
            }

            return Super::dispatch_region_add();
        }

        call_region_subtract
        dispatch_region_subtract() const
        {
            auto call = sak::optional_bind<bind_subtract>(&m_stack);

            if (call && m_stack.enabled())
            {
                return call;
            }

            return Super::dispatch_region_subtract();
        }

        call_region_divide
        dispatch_region_divide() const
        {
            auto call = sak::optional_bind<bind_divide>(&m_stack);

            if (call && m_stack.enabled())
            {
                return call;
            }

            return Super::dispatch_region_divide();
        }

        call_region_multiply
        dispatch_region_multiply() const
        {
            auto call = sak::optional_bind<bind_multiply>(&m_stack);

            if (call && m_stack.enabled())
            {
                return call;
            }

            return Super::dispatch_region_multiply();
        }

        call_region_multiply_constant
        dispatch_region_multiply_constant() const
        {
            auto call = sak::optional_bind<bind_multiply_constant>(&m_stack);

            if (call && m_stack.enabled())
            {
                return call;
            }

            return Super::dispatch_region_multiply_constant();
        }

        call_region_multiply_add
        dispatch_region_multiply_add() const
        {
            auto call = sak::optional_bind<bind_multiply_add>(&m_stack);

            if (call && m_stack.enabled())
            {
                return call;
            }

            return Super::dispatch_region_multiply_add();
        }

        call_region_multiply_subtract
        dispatch_region_multiply_subtract() const
        {
            auto call = sak::optional_bind<bind_multiply_subtract>(&m_stack);

            if (call && m_stack.enabled())
            {
                return call;
            }

            return Super::dispatch_region_multiply_subtract();
        }

        /// @copydoc layer::alignment() const
        uint32_t alignment() const
        {
            if (m_stack.enabled())
            {
                return std::max(m_stack.alignment(), Super::alignment());
            }
            else
            {
                return Super::alignment();
            }
        }

        /// @copydoc layer::max_alignment() const
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

        /// @copydoc layer::granularity() const
        uint32_t granularity() const
        {
            if (m_stack.enabled())
            {
                return std::max(m_stack.granularity(), Super::granularity());
            }
            else
            {
                return Super::granularity();
            }
        }

        /// @copydoc layer::max_granularity() const
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

        /// @return True if the embedded stack is enabled i.e. if it
        /// can be used for computations
        bool enabled() const
        {
            return m_stack.enabled();
        }

    protected:

        /// The stack to use for dispatching
        Stack m_stack;

    };

    /// This class is typically not used directly in the finite field
    /// stacks. Instead use the convenience class region_dispatcher
    /// which "extracts" the template arguments needed by this layer
    /// from the dispatch stack.
    ///
    /// The generic version of the stack represents the fall through
    /// in cases where the main stack's field is different from the
    /// dispatch stack's field. See the specialization below which is
    /// enabled when the fields match.
    template<class Field, class Stack, class StackField, class Super>
    class region_dispatcher_specialization_temp : public Super
    { };

    /// Specialization of the dispatcher which is enabled when the main
    /// stack and the dispatch stack have matching fields.
    template<class Field, class Stack, class Super>
    class region_dispatcher_specialization_temp<Field, Stack, Field, Super> :
        public Super
    {
    public:

        /// @copydoc layer::field_type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename Super::value_type value_type;

    public:

        /// Constructor
        region_dispatcher_specialization_temp()
        {
            bool enabled = m_stack.enabled();

            // Region Add
            if (enabled && has_region_add<Stack>::value)
            {
                bind_region_add(&m_stack);
            }
            else
            {
                bind_region_add((Super*)this);
            }

            // Region Subtract
            if (enabled && has_region_subtract<Stack>::value)
            {
                bind_region_subtract(&m_stack);
            }
            else
            {
                bind_region_subtract((Super*)this);
            }

            // Region Multiply
            if (enabled && has_region_multiply<Stack>::value)
            {
                bind_region_multiply(&m_stack);
            }
            else
            {
                bind_region_multiply((Super*)this);
            }

            // Region Divide
            if (enabled && has_region_divide<Stack>::value)
            {
                bind_region_divide(&m_stack);
            }
            else
            {
                bind_region_divide((Super*)this);
            }

            // Region Multiply Constant
            if (enabled && has_region_multiply_constant<Stack>::value)
            {
                bind_region_multiply_constant(&m_stack);
            }
            else
            {
                bind_region_multiply_constant((Super*)this);
            }

            // Region Multiply Add
            if (enabled && has_region_multiply_add<Stack>::value)
            {
                bind_region_multiply_add(&m_stack);
            }
            else
            {
                bind_region_multiply_add((Super*)this);
            }

            // Region Multiply Subtract
            if (enabled && has_region_multiply_subtract<Stack>::value)
            {
                bind_region_multiply_subtract(&m_stack);
            }
            else
            {
                bind_region_multiply_subtract((Super*)this);
            }
        }

        /// @copydoc layer::region_add(value_type*, const value_type*,
        ///                            uint32_t) const
        void region_add(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(m_add);
            m_add(dest, src, length);
        }

        /// @copydoc layer::region_subtract(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_subtract(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(m_subtract);
            m_subtract(dest, src, length);
        }

        /// @copydoc layer::region_multiply(value_type*, const value_type*,
        ///                                 uint32_t) const
        void region_multiply(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(m_multiply);
            m_multiply(dest, src, length);
        }

        /// @copydoc layer::region_divide(value_type*, const value_type*,
        ///                               uint32_t) const
        void region_divide(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            assert(m_divide);
            m_divide(dest, src, length);
        }

        /// @copydoc layer::region_multiply_constant(value_type*, value_type,
        ///                                          uint32_t) const
        void region_multiply_constant(
            value_type* dest, value_type constant,
            uint32_t length) const
        {
            assert(m_multiply_constant);
            m_multiply_constant(dest, constant, length);
        }

        /// @copydoc layer::region_multiply_add(value_type*, const value_type*,
        ///                                     value_type, uint32_t) const
        void region_multiply_add(value_type* dest, const value_type* src,
                          value_type constant, uint32_t length) const
        {
            assert(m_multiply_add);
            m_multiply_add(dest, src, constant, length);
        }

        /// @copydoc layer::region_multiply_subtract(value_type*,
        ///                                          const value_type*,
        ///                                          value_type, uint32_t) const
        void region_multiply_subtract(value_type* dest, const value_type* src,
                                value_type constant, uint32_t length) const
        {
            assert(m_multiply_subtract);
            m_multiply_subtract(dest, src, constant, length);
        }

        /// @copydoc layer::alignment() const
        uint32_t alignment() const
        {
            if (m_stack.enabled())
            {
                return std::max(m_stack.alignment(), Super::alignment());
            }
            else
            {
                return Super::alignment();
            }
        }

        /// @copydoc layer::max_alignment() const
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

        /// @copydoc layer::granularity() const
        uint32_t granularity() const
        {
            if (m_stack.enabled())
            {
                return std::max(m_stack.granularity(), Super::granularity());
            }
            else
            {
                return Super::granularity();
            }
        }

        /// @copydoc layer::max_granularity() const
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

        /// @return True if the embedded stack is enabled i.e. if it
        /// can be used for computations
        bool enabled() const
        {
            return m_stack.enabled();
        }

    private:

        /// Helper function for binding to the chosen
        /// layer::region_add(value_type*, const value_type*,
        /// uint32_t). The function uses SFINA to only bind if the
        /// chosen stack supports the operation.
        ///
        /// @param stack Pointer to the stack where the operation
        /// should be bound
        template
        <
            class T,
            typename std::enable_if<
                has_region_add<T>::value, uint8_t>::type = 0
        >
        void bind_region_add(const T* stack)
        {
            namespace sp = std::placeholders;
            m_add = std::bind(&T::region_add, stack, sp::_1, sp::_2, sp::_3);
        }

        /// Helper function called if the chosen stack does not
        /// support the desired operation. In this case, this function
        /// will be instantiated ensuring that the code will
        /// compile. To avoid asserting the calling code should use
        /// the has_region_add<T>::value helper
        ///
        /// @param stack Pointer to the stack where the operation
        /// should be bound
        template
        <
            class T,
            typename std::enable_if<
                !has_region_add<T>::value, uint16_t>::type = 0
        >
        void bind_region_add(const T* stack)
        {
            // We do the assert here - to make sure that this call is
            // not silently ignored in cases where the stack does not
            // have the layer::region_add(value_type*, const
            // value_type*, uint32_t) function. However, this assert
            // can be avoided by using the has_region_add helper.
            (void) stack;
            assert(0);
        }

        /// @copydoc bind_region_add(const T*)
        template
        <
            class T,
            typename std::enable_if<
                has_region_subtract<T>::value, uint8_t>::type = 0
        >
        void bind_region_subtract(const T* stack)
        {
            namespace sp = std::placeholders;
            m_subtract = std::bind(
                &T::region_subtract, stack, sp::_1, sp::_2, sp::_3);
        }

        /// @copydoc bind_region_add(const T*)
        template
        <
            class T,
            typename std::enable_if<
                !has_region_subtract<T>::value, uint16_t>::type = 0
        >
        void bind_region_subtract(const T* stack)
        {
            // @see bind_region_add(T*)
            (void) stack;
            assert(0);
        }

        /// @copydoc bind_region_add(const T*)
        template
        <
            class T,
            typename std::enable_if<
                has_region_multiply<T>::value, uint8_t>::type = 0
        >
        void bind_region_multiply(const T* stack)
        {
            namespace sp = std::placeholders;
            m_multiply = std::bind(
                &T::region_multiply, stack, sp::_1, sp::_2, sp::_3);
        }

        /// @copydoc bind_region_add(const T*)
        template
        <
            class T,
            typename std::enable_if<
                !has_region_multiply<T>::value, uint16_t>::type = 0
        >
        void bind_region_multiply(const T* stack)
        {
            // @see bind_region_add(T*)
            (void) stack;
            assert(0);
        }

        /// @copydoc bind_region_add(const T*)
        template
        <
            class T,
            typename std::enable_if<
                has_region_divide<T>::value, uint8_t>::type = 0
        >
        void bind_region_divide(const T* stack)
        {
            namespace sp = std::placeholders;
            m_divide = std::bind(
                &T::region_divide, stack, sp::_1, sp::_2, sp::_3);
        }

        /// @copydoc bind_region_add(const T*)
        template
        <
            class T,
            typename std::enable_if<
                !has_region_divide<T>::value, uint16_t>::type = 0
        >
        void bind_region_divide(const T* stack)
        {
            // @see bind_region_add(T*)
            (void) stack;
            assert(0);
        }

        /// @copydoc bind_region_add(const T*)
        template
        <
            class T,
            typename std::enable_if<
                has_region_multiply_constant<T>::value, uint8_t>::type = 0
        >
        void bind_region_multiply_constant(const T* stack)
        {
            namespace sp = std::placeholders;
            m_multiply_constant = std::bind(
                &T::region_multiply_constant, stack, sp::_1, sp::_2, sp::_3);
        }

        /// @copydoc bind_region_add(const T*)
        template
        <
            class T,
            typename std::enable_if<
                !has_region_multiply_constant<T>::value, uint16_t>::type = 0
        >
        void bind_region_multiply_constant(const T* stack)
        {
            // @see bind_region_add(T*)
            (void) stack;
            assert(0);
        }

        /// @copydoc bind_region_add(const T*)
        template
        <
            class T,
            typename std::enable_if<
                has_region_multiply_add<T>::value, uint8_t>::type = 0
        >
        void bind_region_multiply_add(const T* stack)
        {
            namespace sp = std::placeholders;
            m_multiply_add = std::bind(
                &T::region_multiply_add, stack, sp::_1, sp::_2, sp::_3, sp::_4);
        }

        /// @copydoc bind_region_add(const T*)
        template
        <
            class T,
            typename std::enable_if<
                !has_region_multiply_add<T>::value, uint16_t>::type = 0
        >
        void bind_region_multiply_add(const T* stack)
        {
            // @see bind_region_add(T*)
            (void) stack;
            assert(0);
        }

        /// @copydoc bind_region_add(const T*)
        template
        <
            class T,
            typename std::enable_if<
                has_region_multiply_subtract<T>::value, uint8_t>::type = 0
        >
        void bind_region_multiply_subtract(const T* stack)
        {
            namespace sp = std::placeholders;
            m_multiply_subtract = std::bind(&T::region_multiply_subtract,
                stack, sp::_1, sp::_2, sp::_3, sp::_4);
        }

        /// @copydoc bind_region_add(const T*)
        template
        <
            class T,
            typename std::enable_if<
                !has_region_multiply_subtract<T>::value, uint16_t>::type = 0
        >
        void bind_region_multiply_subtract(const T* stack)
        {
            // @see bind_region_add(T*)
            (void) stack;
            assert(0);
        }

    protected:

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
