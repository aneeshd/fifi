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
#include "arithmetic_simple_online.hpp"
#include "arithmetic_log_table.hpp"
#include "polynomial_degree.hpp"

namespace fifi
{

    /// Simple online finite field algorithms - computes the results
    /// on the fly without relying on pre-computed look-up tables etc.
    template<class Field>
    class log_table :
        public arithmetic_log_table<Field,
               arithmetic_simple_online<Field,
               polynomial_degree<
               final<Field> > > >
    { };


}
