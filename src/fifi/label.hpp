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
        const label& _get_this(select<true>) const
        {
            std::cout << "_get_this true, Label: " << Label << " SuperLabel: " << SuperLabel << std::endl;
            return *this;
        }

        template<uint32_t SuperLabel>
        auto _get_this(select<false>) const -> decltype(((Super*)this)->template get_this<SuperLabel>())
        {
            std::cout << "_get_this false, Label: " << Label << " SuperLabel: " << SuperLabel << std::endl;
            return ((Super*)this)->template get_this<SuperLabel>();
        }

        template<uint32_t SuperLabel>
        auto get_this() const -> decltype(this->template _get_this<SuperLabel>( select<Label == SuperLabel>() ))
        {
            return this->template _get_this<SuperLabel>(select<Label == SuperLabel>());
        }
    };
}
