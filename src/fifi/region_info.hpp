// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "fifi_utils.hpp"

#include <cstdint>

namespace fifi
{

    /// Produces a field for storing the buffer length
    template<class Field, class Super>
    class region_info : public Super
    {
    public:

        /// Sets the length in elements
        /// @param length denotes the new length
        void set_length(uint32_t length)
        {
            m_length = length;
            m_size = length_to_size<Field>(length);
        }

        /// Sets the size in bytes
        /// @param size denotes the new size
        void set_size(uint32_t size)
        {
            m_size = size;
            m_length = size_to_length<Field>(size);
        }

        /// Gets the length i.e. the number of elements
        uint32_t length() const
        {
            return m_length;
        }

        /// Gets the size in of the elements in bytes
        uint32_t size() const
        {
            return m_size;
        }

    private:

        /// The length in Field elements
        uint32_t m_length;

        /// The size in bytes
        uint32_t m_size;

    };
}
