// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

// This file causes double definition warnings with MSVC
#if !defined(_MSC_VER)

#include "prime2325.hpp"

namespace fifi
{
    const prime2325::value_type prime2325::max_value;
    const prime2325::value_type prime2325::min_value;
    const prime2325::order_type prime2325::order;
    const prime2325::value_type prime2325::prime;
    const uint32_t prime2325::max_block_size;
    const uint32_t prime2325::max_block_length;
    const bool prime2325::is_exact;
}

#endif
