// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <platform/config.hpp>

// This file causes double definition warnings with MSVC
#if !defined(PLATFORM_MSVC)

#include "binary.hpp"

#include "binary.hpp"

namespace fifi
{
    const binary::value_type binary::max_value;
    const binary::value_type binary::min_value;
    const binary::order_type binary::order;
    const bool binary::is_exact;
}

#endif
