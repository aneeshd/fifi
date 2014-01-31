// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "final.hpp"
#include "optimal_prime_arithmetic.hpp"
#include "region_arithmetic.hpp"
#include "region_info.hpp"
#include "packed_arithmetic.hpp"

namespace fifi
{
    /// This implementation allows finite field arithmetics in the
    /// prime fields in this case where the characteristic of the
    /// field is different than two.
    template<class Field>
    class optimal_prime :
        public
               region_arithmetic<
               region_info<Field,
               packed_arithmetic<
               optimal_prime_arithmetic<
               final<Field> > > > >
    { };
}
