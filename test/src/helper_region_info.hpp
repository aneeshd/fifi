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
        class Field,
        uint32_t Alignment,
        uint32_t MaxAlignment,
        uint32_t Granularity,
        uint32_t MaxGranularity,
        class Super
    >
    class helper_region_info : public Super
    {
    public:

        typedef Field field_type;
        typedef typename field_type::value_type value_type;

    public:

        static uint32_t alignment()
        {
            return Alignment;
        }

        static uint32_t max_alignment()
        {
            return MaxAlignment;
        }

        static uint32_t granularity()
        {
            return Granularity;
        }

        static uint32_t max_granularity()
        {
            return MaxGranularity;
        }
    };
}
