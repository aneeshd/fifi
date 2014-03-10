// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/region_dispatcher.hpp>
#include <fifi/region_divide_alignment.hpp>
#include <fifi/region_divide_granularity.hpp>
#include <fifi/region_equal_alignment.hpp>
#include <fifi/simple_online.hpp>
#include <fifi/ssse3_binary4_full_table.hpp>
#include <fifi/ssse3_binary8_full_table.hpp>

namespace fifi
{
    /// Unoptimized Binary8 stack for comparison with SIMD implementations.
    template<class Field>
    class unoptimized_binary8 :
        public binary8_region_arithmetic_full_table<Field,
               region_arithmetic<
               region_info<
               binary4_packed_arithmetic<Field,
               packed_arithmetic<
               full_table_arithmetic<
               simple_online_arithmetic<
               final<Field> > > > > > > >
    { };
}
