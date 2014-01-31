// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "binary4_packed_arithmetic.hpp"
#include "extended_log_table_arithmetic.hpp"
#include "final.hpp"
#include "packed_arithmetic.hpp"
#include "polynomial_degree.hpp"
#include "region_arithmetic.hpp"
#include "region_info.hpp"
#include "simple_online_arithmetic.hpp"

namespace fifi
{

    template<class Field>
    class extended_log_table :
        public region_arithmetic<
               region_info<Field,
               binary4_packed_arithmetic<Field,
               packed_arithmetic<
               extended_log_table_arithmetic<
               simple_online_arithmetic<
               polynomial_degree<
               final<Field> > > > > > > >
    { };

}
