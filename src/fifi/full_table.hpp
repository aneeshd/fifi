// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "final.hpp"
#include "arithmetic_simple_online.hpp"
#include "arithmetic_full_table.hpp"
#include "polynomial_degree.hpp"

namespace fifi
{

    /// Simple online finite field algorithms - computes the results
    /// on the fly without relying on pre-computed look-up tables etc.
    template<class Field>
    class full_table :
        public // Region arithmetic
               // Packed arithmetic
               // Arithmetic
               arithmetic_full_table<Field,
               arithmetic_simple_online<Field,
               polynomial_degree<
               final<Field> > > >
    { };
}


