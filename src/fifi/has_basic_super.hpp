// Copyright Steinwurf ApS 2014
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

namespace fifi
{
    /// Type trait helper for compile time detection of whether
    /// a class defines a typedef called basic_super_type.
    ///
    /// Example:
    ///
    /// if(has_basic_super<MyClass>::value)
    /// {
    ///     // Do something here
    /// }
    ///
    template<typename T>
    class has_basic_super
    {
        typedef uint8_t yes;
        typedef uint32_t no;

        template <typename U> static yes check(typename U::basic_super_type*);
        template <typename U> static no  check(...);

    public:

        enum { value = (sizeof(check<T>(0)) == sizeof(yes)) };
    };
}
