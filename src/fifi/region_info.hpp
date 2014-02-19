// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

namespace fifi
{

    /// @brief This layer provides the default region infomation.
    template<class Super>
    class region_info : public Super
    {
    public:

        /// @copydoc layer::field_type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename field_type::value_type value_type;

    public:

        /// @return The default region alignment required for the buffers used
        ///         in the finite field computations. The buffers passed to the
        ///         arithmetic functions should have their memory aligned
        ///         according to the value returned by this function.
        uint32_t alignment() const
        {
            /// @todo Change to C++11 alignof when available in MSVC
            return sizeof(value_type);
        }

        /// @return The buffer length granularity, i.e., length (number of
        ///         value_type elements) by which the buffer must be divisible.
        uint32_t granularity() const
        {
            return 1U;
        }
    };
}
