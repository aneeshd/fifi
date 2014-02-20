// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <fifi/simple_online.hpp>
#include <fifi/ssse3_binary4_full_table.hpp>
#include <fifi/correct_alignment.hpp>
#include <fifi/correct_granularity.hpp>
#include <fifi/region_dispatcher.hpp>
#include <fifi/binary4.hpp>

namespace fifi
{

    /// Simple online finite field algorithms - computes the results
    /// on the fly without relying on pre-computed look-up tables etc.
    template<class Field>
    class ssse3_binary4 :
        public correct_alignment<
               correct_granularity<
               region_dispatcher<Field, ssse3_binary4_full_table, binary4,
               name_super<
               binary_region_arithmetic<Field,
               region_arithmetic<
               region_info<
               binary4_packed_arithmetic<Field,
               binary_packed_arithmetic<Field,
               packed_arithmetic<
               binary_simple_online_arithmetic<Field,
               simple_online_arithmetic<
               polynomial_degree<
               final<Field> > > > > > > > > > > > > >
    { };
}
