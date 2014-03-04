// Copyright Steinwurf ApS 2014
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>
#include <utility>


namespace fifi
{
    /// Type trait helper allows compile time detection of whether an
    /// encoder contains a layer with the member function
    /// region_multiply_add(value_type*,value_type*,uint32_t)
    ///
    /// Example:
    ///
    /// typedef fifi::simple_online online;
    ///
    /// if(kodo::has_region_multiply_add<online>::value)
    /// {
    ///     // Do something here
    /// }
    ///
    template<typename T>
    struct has_region_multiply_add
    {
    private:

        template<typename U>
        static auto test(int) ->
            decltype(std::declval<U>().region_multiply_add(0,0,0,0),
                     uint32_t());

        template<typename> static uint8_t test(...);

    public:

        static const bool value = sizeof(decltype(test<T>(0))) == 4;
    };
}

