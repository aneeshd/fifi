// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

#include <iostream>

namespace fifi
{
    template<bool B>
    struct select
    { };

    template<uint32_t Label, class Super>
    class label : public Super
    {
    public:

        template<uint32_t SuperLabel>
        const label& _get_label(select<true>) const
        {
            return *this;
        }

        template<uint32_t SuperLabel>
        auto _get_label(select<false>) const
            -> decltype(((Super*)nullptr)->template get_label<SuperLabel>())
        {
            return ((Super*)this)->template get_label<SuperLabel>();
        }

        template<uint32_t SuperLabel>
        auto get_label() const
            -> decltype(((label*)nullptr)->template _get_label<SuperLabel>(
                select<Label == SuperLabel>()))
        {
            return this->template _get_label<SuperLabel>(select<Label == SuperLabel>());
        }
    };
}
