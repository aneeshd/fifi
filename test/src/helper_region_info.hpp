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

        helper_region_info() :
            m_alignment(Alignment),
            m_max_alignment(MaxAlignment),
            m_granularity(Granularity),
            m_max_granularity(MaxGranularity)
        { }


        uint32_t alignment() const
        {
            return m_alignment;
        }

        void set_alignment(uint32_t alignment)
        {
            m_alignment = alignment;
        }

        uint32_t max_alignment() const
        {
            return m_max_alignment;
        }

        void set_max_alignment(uint32_t max_alignment)
        {
            m_max_alignment = max_alignment;
        }

        uint32_t granularity() const
        {
            return m_granularity;
        }

        void set_granularity(uint32_t granularity)
        {
            m_granularity = granularity;
        }

        uint32_t max_granularity() const
        {
            return m_max_granularity;
        }

        void set_max_granularity(uint32_t max_granularity)
        {
            m_max_granularity = max_granularity;
        }

    private:

        uint32_t m_alignment;
        uint32_t m_max_alignment;
        uint32_t m_granularity;
        uint32_t m_max_granularity;

    };
}
