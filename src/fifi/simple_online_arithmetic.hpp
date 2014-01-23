// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

#include "specialized_simple_online.hpp"
#include "general_simple_online.hpp"

namespace fifi
{

    /// Simple online finite field algorithms - computes the results
    /// on the fly without relying on pre-computed look-up tables etc.
    template<class Field, class Super>
    class simple_online_arithmetic : public specialized_simple_online<Field,
                                            general_simple_online<Super> >
    { };

}
