// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "has_basic_super.hpp"

#include "region_dispatcher_specialization.hpp"


namespace fifi
{
    /// Helper class for easing the use of region_dispatcher_specialization.
    template<class Stack, class Super>
    class region_dispatcher :
        public region_dispatcher_specialization<
            typename Super::field_type, Stack,
            typename Stack::field_type, Super>
    {
        template<bool B, class T>
        struct reuse_basic_super_if { typedef typename T::BasicSuper type; };

        template<class T>
        struct reuse_basic_super_if<false, T> { typedef T type; };

    public:

        typedef typename reuse_basic_super_if<
            has_basic_super<Super>::value, Super>::type BasicSuper;

        typedef region_dispatcher<Stack, Super> OptimizedSuper;
    };
}
