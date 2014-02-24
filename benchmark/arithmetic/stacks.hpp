// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <fifi/binary4.hpp>
#include <fifi/region_dispatcher.hpp>
#include <fifi/region_divide_alignment.hpp>
#include <fifi/region_divide_granularity.hpp>
#include <fifi/region_equal_alignment.hpp>
#include <fifi/simple_online.hpp>
#include <fifi/ssse3_binary4_full_table.hpp>

namespace fifi
{

    /// Stack containing the SSSE3 binary4 SIMD optimized
    /// operations. Using the CPU dispatcher optimizations should only
    /// be enabled on SSSE3 capable CPUs.
    template<class Field>
    class ssse3_binary4 :
        public region_equal_alignment<
               region_divide_alignment<
               region_divide_granularity<
               region_dispatcher<ssse3_binary4_full_table,
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
               final<Field> > > > > > > > > > > > > > >
    { };
}
