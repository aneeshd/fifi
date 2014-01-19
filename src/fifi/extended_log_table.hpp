// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "final.hpp"
#include "arithmetic_simple_online.hpp"
#include "arithmetic_extended_log_table.hpp"
#include "polynomial_degree.hpp"

namespace fifi
{

    template<class Field>
    class extended_log_table :
        public arithmetic_extended_log_table<
               arithmetic_simple_online<Field,
               polynomial_degree<
               final<Field> > > >
    { };

}


