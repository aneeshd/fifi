// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "binary_simple_online_arithmetic.hpp"
#include "extended_log_table_arithmetic.hpp"
#include "final.hpp"
#include "polynomial_degree.hpp"
#include "simple_online_arithmetic.hpp"

namespace fifi
{

    template<class Field>
    class extended_log_table :
        public extended_log_table_arithmetic<Field,
               simple_online_arithmetic<
               polynomial_degree<
               final<Field> > > >
    { };

}
