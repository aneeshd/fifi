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
    /// @brief Helper class for easing the use of
    /// region_dispatcher_specialization.
    ///
    /// The region_dispatcher layer "extracts" the information needed
    /// by the region_dispatcher_specilization making the embedding
    /// nicer.
    template<class Stack, class Super>
    class stack_region_dispatcher :
        public region_dispatcher_specialization_v2<
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
        typedef stack_region_dispatcher<Stack, Super> OptimizedSuper;
    };




    /// @brief Helper class for easing the use of
    /// region_dispatcher_specialization.
    ///
    /// The region_dispatcher layer "extracts" the information needed
    /// by the region_dispatcher_specilization making the embedding
    /// nicer.
    template<class Stack, class Super>
    class region_dispatcher_temp :
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
        typedef region_dispatcher_temp<Stack, Super> OptimizedSuper;
    };
}
