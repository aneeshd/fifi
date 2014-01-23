// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "final.hpp"
#include "simple_online_arithmetic.hpp"
#include "extended_log_table_arithmetic.hpp"
#include "polynomial_degree.hpp"

namespace fifi
{

    template<class Field>
    class extended_log_table :
        public extended_log_table_arithmetic<
               simple_online_arithmetic<Field,
               polynomial_degree<
               final<Field> > > >
    { };

}
