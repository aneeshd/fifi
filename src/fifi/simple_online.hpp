// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "binary_simple_online_arithmetic.hpp"
#include "final.hpp"
#include "polynomial_degree.hpp"
#include "simple_online_arithmetic.hpp"

namespace fifi
{

    /// Simple online finite field algorithms - computes the results
    /// on the fly without relying on pre-computed look-up tables etc.
    template<class Field>
    class simple_online :
        public binary_simple_online_arithmetic<Field,
               simple_online_arithmetic<
               polynomial_degree<
               final<Field> > > >
    { };

}
