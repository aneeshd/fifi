// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "has_basic_super.hpp"

#include "region_dispatcher_specialization.hpp"

#include <sak/easy_bind.hpp>

namespace fifi
{


    template<class Super>
    class bind_region_arithmetic : public Super
    {
    public:

        /// @copydoc layer::value_type
        using value_type = typename Super::value_type;

        /// @copydoc layer::region_add(value_type*, const value_type*,
        ///                            uint32_t) const
        using call_region_add = std::function<
            void (value_type* dest, const value_type* src, uint32_t length)>;

        /// @copydoc layer::region_subtract(value_type*, const value_type*,
        ///                                 uint32_t) const
        using call_region_subtract = std::function<
            void (value_type* dest, const value_type* src, uint32_t length)>;


        /// @copydoc layer::region_divide(value_type*, const value_type*,
        ///                               uint32_t) const
        using call_region_divide = std::function<
            void (value_type* dest, const value_type* src, uint32_t length)>;

        /// @copydoc layer::region_multiply(value_type*, const value_type*,
        ///                                 uint32_t) const
        using call_region_multiply = std::function<
            void (value_type* dest, const value_type* src, uint32_t length)>;

        /// @copydoc layer::region_multiply_constant(value_type*, value_type,
        ///                                          uint32_t) const
        using call_region_multiply_constant = std::function<
            void (value_type* dest, value_type constant, uint32_t length)>;

        /// @copydoc layer::region_multiply_add(value_type*, const value_type*,
        ///                                     value_type, uint32_t) const
        using call_region_multiply_add = std::function<
            void (value_type* dest, const value_type* src, value_type constant,
                  uint32_t length)>;

        /// @copydoc layer::region_multiply_subtract(value_type*,
        ///                                          const value_type*,
        ///                                          value_type,
        ///                                          uint32_t) const
        using call_region_multiply_subtract = std::function<
            void (value_type* dest, const value_type* src, value_type constant,
                  uint32_t length)>;

    public:

        call_region_add dispatch_region_add()
        {
            auto v = sak::easy_bind(&Super::region_add, (Super*)this);
            return v;
        }

        call_region_subtract dispatch_region_subtract()
        {
            return sak::easy_bind(&Super::region_subtract, this);
        }

        call_region_divide dispatch_region_divide()
        {
            return sak::easy_bind(&Super::region_divide, this);
        }

        call_region_multiply dispatch_region_multiply()
        {
            return sak::easy_bind(&Super::region_multiply, this);
        }

        call_region_multiply_constant dispatch_region_multiply_constant()
        {
            return sak::easy_bind(&Super::region_multiply_constant, this);
        }

        call_region_multiply_add dispatch_region_multiply_add()
        {
            return sak::easy_bind(&Super::region_multiply_add, this);
        }

        call_region_multiply_subtract dispatch_region_multiply_subtract()
        {
            return sak::easy_bind(&Super::region_multiply_subtract, this);
        }


    };


    template<class Super>
    class use_region_dispatcher : public Super
    {
    public:

        /// @copydoc layer::value_type
        using value_type = typename Super::value_type;

        using call_region_add =
            typename Super::call_region_add;

        using call_region_subtract =
            typename Super::call_region_subtract;

        using call_region_divide =
            typename Super::call_region_divide;

        using call_region_multiply =
            typename Super::call_region_multiply;

        using call_region_multiply_constant =
            typename Super::call_region_multiply_constant;

        using call_region_multiply_add =
            typename Super::call_region_multiply_add;

        using call_region_multiply_subtract =
            typename Super::call_region_multiply_subtract;

        /// Constructor
        use_region_dispatcher()
        {
            // m_region_add = Super::dispatch_region_add();
        }


    protected:

        call_region_add m_region_add;
        call_region_subtract m_region_subtract;
        call_region_divide m_region_divide;
        call_region_multiply m_region_multiply;
        call_region_multiply_constant m_region_multiply_constant;
        call_region_multiply_add m_region_multiply_add;
        call_region_multiply_subtract m_region_multiply_subtract;
    };



    /// @brief Helper class for easing the use of
    /// region_dispatcher_specialization.
    ///
    /// The region_dispatcher layer "extracts" the information needed
    /// by the region_dispatcher_specilization making the embedding
    /// nicer.
    template<class Stack, class Super>
    class region_dispatcher_v2 : public Super
    {
    public:

        /// Helper struct which will typedef type to T::BasicSuper if T
        /// has such a type otherwise we typedef type to T itself.
        template<bool B, class T>
        struct reuse_basic_super_if { typedef typename T::BasicSuper type; };

        /// @copydoc reuse_basic_super_if
        template<class T>
        struct reuse_basic_super_if<false, T> { typedef T type; };

    public:

        /// The BasicSuper typedef ensures that we can "by-pass"
        /// optimized e.g. SIMD layers. The BasicSuper typedef will always
        /// reference the first layer after any number of dispatchers.
        typedef typename reuse_basic_super_if<
            has_basic_super<Super>::value, Super>::type BasicSuper;

        /// The OptimizedSuper typedef references the dispatcher
        /// e.g. SIMD layers directly this allows us to forward calls
        /// to the optimized stack
        typedef region_dispatcher_v2<Stack, Super> OptimizedSuper;

    public:

        /// @copydoc layer::value_type
        using value_type = typename Super::value_type;

        using call_region_add =
            typename Super::call_region_add;

        using call_region_subtract =
            typename Super::call_region_subtract;

        using call_region_divide =
            typename Super::call_region_divide;

        using call_region_multiply =
            typename Super::call_region_multiply;

        using call_region_multiply_constant =
            typename Super::call_region_multiply_constant;

        using call_region_multiply_add =
            typename Super::call_region_multiply_add;

        using call_region_multiply_subtract =
            typename Super::call_region_multiply_subtract;

    public:

        region_dispatcher_v2()
        {

        }

    public:

        // call_region_add bind_region_add()
        // {
        //     if (m_stack.enabled() && has_region_add<Stack>::value)
        //     {
        //         return sak::easy_bind(&Stack::region_add, &m_stack);
        //     }
        //     else
        //     {
        //         return Super::bind_region_add();
        //     }
        // }

        // call_region_subtract bind_region_subtract()
        // {
        //     if (m_stack.enabled() && has_region_subtract<Stack>::value)
        //     {
        //         return sak::easy_bind(&Stack::region_subtract, &m_stack);
        //     }
        //     else
        //     {
        //         return Super::bind_region_subtract();
        //     }
        // }

        // call_region_divide bind_region_divide()
        // {
        //     if (m_stack.enabled() && has_region_divide<Stack>::value)
        //     {
        //         return sak::easy_bind(&Stack::region_divide, &m_stack);
        //     }
        //     else
        //     {
        //         return Super::bind_region_divide();
        //     }
        // }

        // call_region_multiply bind_region_multiply()
        // {
        //     if (m_stack.enabled() && has_region_multiply<Stack>::value)
        //     {
        //         return sak::easy_bind(&Stack::region_multiply, &m_stack);
        //     }
        //     else
        //     {
        //         return Super::bind_region_multiply();
        //     }
        // }

        // call_region_multiply_constant bind_region_multiply_constant()
        // {
        //     if (m_stack.enabled() && has_region_multiply_constant<Stack>::value)
        //     {
        //         return sak::easy_bind(
        //             &Stack::region_multiply_constant, &m_stack);
        //     }
        //     else
        //     {
        //         return Super::bind_region_multiply_constant();
        //     }
        // }

        // call_region_multiply_add bind_region_multiply_add()
        // {
        //     if (m_stack.enabled() && has_region_multiply_add<Stack>::value)
        //     {
        //         return sak::easy_bind(&Stack::region_multiply_add, &m_stack);
        //     }
        //     else
        //     {
        //         return Super::bind_region_multiply_add();
        //     }
        // }

        // call_region_multiply_subtract bind_region_multiply_subtract()
        // {
        //     if (m_stack.enabled() && has_region_multiply_subtract<Stack>::value)
        //     {
        //         return sak::easy_bind(
        //             &Stack::region_multiply_subtract, &m_stack);
        //     }
        //     else
        //     {
        //         return Super::bind_region_multiply_subtract();
        //     }
        // }

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

        /// @brief Helper class for easing the use of
    /// region_dispatcher_specialization.
    ///
    /// The region_dispatcher layer "extracts" the information needed
    /// by the region_dispatcher_specilization making the embedding
    /// nicer.
    template<class Stack, class Super>
    class region_dispatcher :
        public region_dispatcher_specialization<
            typename Super::field_type, Stack,
            typename Stack::field_type, Super>
    {
        /// Helper struct which will typedef type to T::BasicSuper if T
        /// has such a type otherwise we typedef type to T itself.
        template<bool B, class T>
        struct reuse_basic_super_if { typedef typename T::BasicSuper type; };

        /// @copydoc reuse_basic_super_if
        template<class T>
        struct reuse_basic_super_if<false, T> { typedef T type; };

    public:

        /// The BasicSuper typedef ensures that we can "by-pass"
        /// optimized e.g. SIMD layers. The BasicSuper typedef will always
        /// reference the first layer after any number of dispatchers.
        typedef typename reuse_basic_super_if<
            has_basic_super<Super>::value, Super>::type BasicSuper;

        /// The OptimizedSuper typedef references the dispatcher
        /// e.g. SIMD layers directly this allows us to forward calls
        /// to the optimized stack
        typedef region_dispatcher<Stack, Super> OptimizedSuper;
    };
}
