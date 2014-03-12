// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

namespace fifi
{
    template
    <
        uint32_t Alignment,
        uint32_t MaxAlignment,
        uint32_t Granularity,
        uint32_t MaxGranularity,
        class Super
    >
    class helper_region_info : public Super
    {
    public:
        uint32_t alignment() const
        {
            return Alignment;
        }

        uint32_t max_alignment() const
        {
            return MaxAlignment;
        }

        uint32_t granularity() const
        {
            return Granularity;
        }

        uint32_t max_granularity() const
        {
            return MaxGranularity;
        }
    };
}
