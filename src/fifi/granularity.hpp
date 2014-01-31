// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace fifi
{

    /// @brief This layer provides the default region alignment
    ///        required for the buffers used in the finite field
    ///        computations. The buffers passed to the arithmetic
    ///        functions should have their memory aligned according to
    ///        the value returned by this layer
    template<class Super>
    class granularity : public Super
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
