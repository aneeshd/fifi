// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "binary4_packed_arithmetic.hpp"
#include "binary8_region_arithmetic_full_table.hpp"
#include "final.hpp"
#include "full_table_arithmetic.hpp"
#include "packed_arithmetic.hpp"
#include "polynomial_degree.hpp"
#include "region_arithmetic.hpp"
#include "region_info.hpp"
#include "simple_online_arithmetic.hpp"
#include "region_dispatcher.hpp"
#include "ssse3_binary4_full_table.hpp"
#include "correct_alignment.hpp"
#include "correct_granularity.hpp"
#include "name_super.hpp"

namespace fifi
{

    /// The full look-up table - computes a full lookup table of
    /// the multiplication and division operations.
    template<class Field>
    class full_table :
        public correct_alignment<
               correct_granularity<
               region_dispatcher<Field, ssse3_binary4_full_table,
               name_super<
               binary8_region_arithmetic_full_table<Field,
               region_arithmetic<
               region_info<
               binary4_packed_arithmetic<Field,
               packed_arithmetic<
               full_table_arithmetic<Field,
               simple_online_arithmetic<
               polynomial_degree<
               final<Field> > > > > > > > > > > > >
    { };
}
