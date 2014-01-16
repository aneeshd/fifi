// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "field_types.hpp"
#include "binary_extension_field.hpp"
#include "polynomial_degree.hpp"

namespace fifi
{
    struct dummy {};

    /// Simple online finite field algorithms - computes the results
    /// on the fly without relying on pre-computed look-up tables etc.
    template<class Field>
    class simple_online :
        public binary_extension_field<Field,
               polynomial_degree<Field, dummy> >
    { };

}


