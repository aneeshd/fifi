// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <algorithm>
#include <cmath>
#include <cassert>
#include <stdint.h>
#include <vector>

#include "final.hpp"
#include "simple_online_arithmetic.hpp"
#include "log_table_arithmetic.hpp"
#include "polynomial_degree.hpp"

namespace fifi
{

    /// Simple online finite field algorithms - computes the results
    /// on the fly without relying on pre-computed look-up tables etc.
    template<class Field>
    class log_table :
        public log_table_arithmetic<Field,
               simple_online_arithmetic<Field,
               polynomial_degree<
               final<Field> > > >
    { };


}
