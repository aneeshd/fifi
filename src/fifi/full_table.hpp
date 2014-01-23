// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "binary_simple_online_arithmetic.hpp"
#include "binary4_packed_arithmetic.hpp"
#include "binary_packed_arithmetic.hpp"
#include "final.hpp"
#include "full_table_arithmetic.hpp"
#include "packed_arithmetic.hpp"
#include "polynomial_degree.hpp"
#include "region_arithmetic.hpp"
#include "simple_online_arithmetic.hpp"

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
               // Specialized Arithmetic
               binary_simple_online_arithmetic<Field,
               // Arithmetic
               full_table_arithmetic<Field,
               simple_online_arithmetic<
               polynomial_degree<
               final<Field> > > > > > > > >
    { };
}
