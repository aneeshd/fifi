// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "binary4_packed_arithmetic.hpp"
#include "binary_simple_online_arithmetic.hpp"
#include "final.hpp"
#include "log_table_arithmetic.hpp"
#include "packed_arithmetic.hpp"
#include "polynomial_degree.hpp"
#include "region_arithmetic.hpp"
#include "region_info.hpp"
#include "simple_online_arithmetic.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <vector>

namespace fifi
{

    /// Simple online finite field algorithms - computes the results
    /// on the fly without relying on pre-computed look-up tables etc.
    template<class Field>
    class log_table :
        public region_arithmetic<
               region_info<Field,
               binary4_packed_arithmetic<Field,
               packed_arithmetic<
               log_table_arithmetic<Field,
               simple_online_arithmetic<
               polynomial_degree<
               sum_modulo<
               final<Field> > > > > > > > >
    { };
}
