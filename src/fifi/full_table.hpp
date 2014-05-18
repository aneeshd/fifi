// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "binary4.hpp"
#include "binary4_packed_arithmetic.hpp"
#include "binary8.hpp"
#include "binary8_region_arithmetic_full_table.hpp"
#include "final.hpp"
#include "full_table_arithmetic.hpp"
#include "packed_arithmetic.hpp"
#include "region_arithmetic.hpp"
#include "region_dispatcher.hpp"
#include "region_divide_granularity.hpp"
#include "region_info.hpp"
#include "simple_online_arithmetic.hpp"
#include "ssse3_binary4_full_table.hpp"
#include "ssse3_binary8_full_table.hpp"
#include "neon_binary4_full_table.hpp"
#include "neon_binary8_full_table.hpp"

namespace fifi
{
    /// The full look-up table stack. This stack does most
    /// computations base on full look-up tables.
    template<class Field>
    class full_table : public
        region_divide_granularity<
        use_region_dispatcher<
        region_dispatcher_v2<ssse3_binary4_full_table,
        region_dispatcher<ssse3_binary4_full_table,
        region_dispatcher<ssse3_binary8_full_table,
        region_dispatcher<neon_binary4_full_table,
        region_dispatcher<neon_binary8_full_table,
        binary8_region_arithmetic_full_table<Field,
        bind_region_arithmetic<
        region_arithmetic<
        region_info<
        binary4_packed_arithmetic<Field,
        packed_arithmetic<
        full_table_arithmetic<
        simple_online_arithmetic<
        final<Field> > > > > > > > > > > > > > > >
    { };
}
