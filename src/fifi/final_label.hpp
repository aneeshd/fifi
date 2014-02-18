// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <cassert>

namespace fifi
{
    template<class Super>
    class final_label : public Super
    {
    public:
        template<uint32_t Label>
        const final_label& get_label() const
        {
            // The provided template integer, Label is not valid, please review
            // your stack.
            assert(0);
            return *this;
        }
    };
}
