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
    /// @ingroup generic_api
    /// @copydoc set_systematic_off(const T&)
    template<bool what, class T, class... Args>
    inline void bind_region_multiply_subtract(T* t, Args&&... args,
                                              char (*)[what] = 0)
    {
        // Explanation for the char (*)[what] here:
        // http://stackoverflow.com/a/6917354/1717320
        return std::bind(t, &T::region_multiply_subtract, args...);
    }

    /// @ingroup generic_api
    /// @copydoc set_systematic_off(const T&)
    template<bool what, class T>
    inline void set_systematic_off(T& t, char (*)[!what] = 0)
    {
        (void)t;

        // We do the assert here - to make sure that this call is not
        // silently ignored in cases where the stack does not have the
        // set_systematic_off() function. However, this assert can
        // be avoided by using the has_systematic_encoder
        assert(0);
    }

    /// @ingroup generic_api
    /// Generic function overload for cases where set_systematic_off is part
    /// of a stack. @see systematic_encoder::set_systematic_off() const
    /// @param t The stack to query
    template<class T>
    inline void set_systematic_off(T& t)
    {
        set_systematic_off<has_set_systematic_off<T>::value, T>(t);
    }

    /// @ingroup generic_api
    /// @copydoc set_systematic_off(const T&)
    template<class T>
    inline void set_systematic_off(boost::shared_ptr<T>& t)
    {
        set_systematic_off(*t);
    }


}

}

