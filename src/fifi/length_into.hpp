// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

namespace fifi
{

    /// Produces a field for storing the buffer length
    template<class Super>
    class length_into : public Super
    {
    public:

        /// Sets the length of the buffer
        /// @param length denotes the new length
        void set_length(uint32_t length)
        {
            m_length = length;
        }

        /// Gets the length of the buffer
        uint32_t length()
        {
            return m_length;
        }

    private:

        /// The length
        uint32_t m_length

    };
}
