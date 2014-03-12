// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

namespace fifi
{
    /// @brief This layer provides the default region information.
    template<class Super>
    class region_info : public Super
    {
    public:

        /// @copydoc layer::field_type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename field_type::value_type value_type;

    public:

        /// @copydoc layer::alignment() const
        uint32_t alignment() const
        {
            /// @todo Change to C++11 alignof when available in MSVC
            return sizeof(value_type);
        }

        /// @copydoc layer::max_alignment() const
        uint32_t max_alignment() const
        {
            return alignment();
        }

        /// @copydoc layer::granularity() const
        uint32_t granularity() const
        {
            return 1U;
        }

        /// @copydoc layer::max_granularity() const
        uint32_t max_granularity() const
        {
            return granularity();
        }
    };
}
