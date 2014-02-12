// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <fifi/binary4_packed_arithmetic.hpp>
#include <fifi/binary8_full_table_region_arithmetic.hpp>
#include <fifi/final.hpp>
#include <fifi/full_table_arithmetic.hpp>
#include <fifi/packed_arithmetic.hpp>
#include <fifi/polynomial_degree.hpp>
#include <fifi/region_arithmetic.hpp>
#include <fifi/multithreading_region_arithmetic.hpp>
#include <fifi/simple_multithreading_region_arithmetic.hpp>
#include <fifi/region_info.hpp>
#include <fifi/multithreading_region_info.hpp>
#include <fifi/simple_online_arithmetic.hpp>

namespace fifi
{
    template<class Field>
    class multithreading_full_table :
        public multithreading_region_arithmetic<
               multithreading_region_info<
               binary8_full_table_region_arithmetic<Field,
               region_arithmetic<
               region_info<Field,
               binary4_packed_arithmetic<Field,
               packed_arithmetic<
               full_table_arithmetic<Field,
               simple_online_arithmetic<
               polynomial_degree<
               final<Field> > > > > > > > > > >
    { };

    template<class Field>
    class simple_multithreading_full_table :
        public simple_multithreading_region_arithmetic<
               multithreading_region_info<
               binary8_full_table_region_arithmetic<Field,
               region_arithmetic<
               region_info<Field,
               binary4_packed_arithmetic<Field,
               packed_arithmetic<
               full_table_arithmetic<Field,
               simple_online_arithmetic<
               polynomial_degree<
               final<Field> > > > > > > > > > >
    { };
}
