// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "fifi_utils.hpp"

#include <cassert>
#include <cstdint>

namespace fifi
{
    /// Provides multithreading info
    template<class Field, class Super>
    class multithreading_region_info : public Super
    {

    public:

        multithreading_region_info() :
            m_threads(1)
        { }

        uint32_t threads() const
        {
            return m_threads;
        }

        void set_threads(uint32_t threads)
        {
            assert(threads > 0);
            assert((m_length % threads) == 0);

            m_threads = threads;

            assert(m_length / m_threads);

            Super::set_length(m_length / m_threads);
        }

        void set_length(uint32_t length)
        {
            assert(length > 0);
            assert((length % m_threads) == 0);

            m_length = length;
            m_size = length_to_size<Field>(m_length);

            assert(m_length / m_threads);

            Super::set_length(m_length / m_threads);
        }

        void set_size(uint32_t size)
        {
            assert(size > 0);

            m_size = size;
            m_length = size_to_length<Field>(m_size);

            assert((m_length % m_threads) == 0);
            assert(m_length > 0);

            assert(m_length / m_threads);

            Super::set_length(m_length / m_threads);
        }

        uint32_t length() const
        {
            return m_length;
        }

        uint32_t size() const
        {
            return m_size;
        }

        uint32_t slice() const
        {
            return Super::length();
        }

    private:

        uint32_t m_threads;
        uint32_t m_length;
        uint32_t m_size;
    };
}
