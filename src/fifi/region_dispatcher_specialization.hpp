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
#include <iostream>

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
    /// Fall-through case where the Field and StackField types are
    /// different. This means that whatever optimizations are
    /// implmented in the Stack does not apply here since they are for
    /// a different finite field from that used in the main stack.
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

        /// @todo these doc strings look wrong there is a _ too much
        /// after dispatcher
        ///
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

        /// Define this layer as the optimized_super_type. We use the
        /// optimized_super_type type to access the optimization
        /// layers. The motivation for this is that the optimization
        /// layers might have specific granularity requirements (the
        /// minimum amount of data they process), and if these
        /// requirements are not statisfied we have to use the basic
        /// region arithmetic functions. The basic region dispatchers
        /// define the BasicSuper type to allow a callee to by pass
        /// the optimization layers.
        using optimized_super_type =
            region_dispatcher_specialization<Field, Stack, Field, Super>;

    public:

        /// Helper struct for sak::optional_bind. sak::optinal_bind
        /// allows us to "attempt" to bind to a specific function in
        /// the Stack object. However if that function is not defined
        /// by the stack, it will simply return an empty std::function
        /// object.
        struct bind_add
        {
            using result_type = call_region_add;

            template<class T, class U = Stack>
            static auto bind(T&& t) ->
            decltype(std::declval<U>().region_add(0,0,0),
                     result_type())
            {
                return sak::easy_bind(&U::region_add, std::forward<T>(t));
            }
        };

        /// @copydoc bind_add
        struct bind_subtract
        {
            using result_type = call_region_subtract;

            template<class T, class U = Stack>
            static auto bind(T&& t) ->
                decltype(std::declval<U>().region_subtract(0,0,0),
                         result_type())
            {
                return sak::easy_bind(&U::region_subtract, std::forward<T>(t));
            }
        };

        /// @copydoc bind_add
        struct bind_divide
        {
            using result_type = call_region_divide;

            template<class T, class U = Stack>
            static auto bind(T&& t) ->
                decltype(std::declval<U>().region_divide(0,0,0),
                         result_type())
            {
                return sak::easy_bind(&U::region_divide, std::forward<T>(t));
            }
        };

        /// @copydoc bind_add
        struct bind_multiply
        {
            using result_type = call_region_multiply;

            template<class T, class U = Stack>
            static auto bind(T&& t) ->
                decltype(std::declval<U>().region_multiply(0,0,0),
                         result_type())
            {
                return sak::easy_bind(&U::region_multiply, std::forward<T>(t));
            }
        };

        /// @copydoc bind_add
        struct bind_multiply_constant
        {
            using result_type = call_region_multiply_constant;

            template<class T, class U = Stack>
            static auto bind(T&& t) ->
            decltype(std::declval<U>().region_multiply_constant(0,0,0),
                     result_type())
            {
                return sak::easy_bind(&U::region_multiply_constant,
                                      std::forward<T>(t));
            }
        };

        /// @copydoc bind_add
        struct bind_multiply_add
        {
            using result_type = call_region_multiply_add;

            template<class T, class U = Stack>
            static auto bind(T&& t) ->
            decltype(std::declval<U>().region_multiply_add(0,0,0,0),
                     result_type())
            {
                return sak::easy_bind(&U::region_multiply_add,
                                      std::forward<T>(t));
            }

        };

        /// @copydoc bind_add
        struct bind_multiply_subtract
        {
            using result_type = call_region_multiply_subtract;

            template<class T, class U = Stack>
            static auto bind(T&& t) ->
            decltype(std::declval<U>().region_multiply_subtract(0,0,0,0),
                     result_type())
            {
                return sak::easy_bind(&U::region_multiply_subtract, t);
            }
        };

    public:

        /// @todo missing docs on these files
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
}
