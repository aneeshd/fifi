// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

namespace fifi
{

    /// @brief This layer provides the default region buffer size
    ///        granularity. This means that the size (bytes) or length
    ///        (number of value_type elements) must be divisible by
    ///        the size and length granularity
    template<class Super>
    class region_granularity : public Super
    {
    public:

        /// The field type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename field_type::value_type value_type;

    public:

        /// @return The alignment requirement
        uint32_t size_granularity() const
        {
            return sizeof(value_type);
        }

        /// @return The alignment requirement
        uint32_t length_granularity() const
        {
            return 1U;
        }
    };
}
