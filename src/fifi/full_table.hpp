// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "final.hpp"
#include "arithmetic_simple_online.hpp"
#include "arithmetic_full_table.hpp"
#include "polynomial_degree.hpp"
#include "packed_arithmetic.hpp"
#include "binary_packed_arithmetic.hpp"
#include "binary4_packed_arithmetic.hpp"
#include "region_arithmetic.hpp"

namespace fifi
{

    /// Simple online finite field algorithms - computes the results
    /// on the fly without relying on pre-computed look-up tables etc.
    template<class Field>
    class full_table :
        public // Region arithmetic
               region_arithmetic<
               // Packed arithmetic
               binary4_packed_arithmetic<Field,
               binary_packed_arithmetic<Field,
               packed_arithmetic<
               // Arithmetic
               arithmetic_full_table<Field,
               arithmetic_simple_online<Field,
               polynomial_degree<
               final<Field> > > > > > > >
    { };
}


