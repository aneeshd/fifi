// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <algorithm>
#include <cmath>
#include <cassert>
#include <stdint.h>

#include "final.hpp"
#include "simple_online_layer.hpp"
#include "extended_log_table_layer.hpp"
#include "polynomial_degree.hpp"
#include "binary_arithmetic.hpp"

namespace fifi
{

    template<class Field>
    class extended_log_table :
        public extended_log_table_layer<Field,
               simple_online_layer<Field,
               polynomial_degree<Field,
               binary_arithmetic<
               final<Field> > > > >
    { };

}


