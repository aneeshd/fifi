// Copyright Steinwurf ApS 2011-2013.
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

        /// The field type
        typedef Field field_type;

        /// The data type storing field elements
        typedef typename field_type::value_type value_type;
    };
}
