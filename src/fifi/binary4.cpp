// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <platform/config.hpp>

// This file causes double definition warnings with MSVC
#if !defined(PLATFORM_MSVC)

#include "binary4.hpp"

namespace fifi
{
    const binary4::value_type binary4::max_value;
    const binary4::value_type binary4::min_value;
    const binary4::order_type binary4::order;
    const binary4::degree_type binary4::degree;
    const binary4::value_type binary4::prime;
    const bool binary4::is_exact;
}

#endif
