// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "binary.hpp"

#include <limits>

namespace fifi
{
    const binary::value_type binary::max_value = 1;
    const binary::value_type binary::min_value = 0;
    const binary::order_type binary::order = 2;
    const uint32_t binary::bits_per_value =
        std::numeric_limits<binary::value_type>::digits;
}
