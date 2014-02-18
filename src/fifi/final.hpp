// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace fifi
{
    /// @todo docs
    template<class Field>
    class final
    {

    public:

        /// @copydoc layer::field_type
        typedef Field field_type;

        /// @copydoc layer::value_type
        typedef typename field_type::value_type value_type;
    };
}
