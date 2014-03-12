// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <platform/config.hpp>

// This file causes double definition warnings with MSVC
#if !defined(PLATFORM_MSVC)

#include "binary8.hpp"

namespace fifi
{
    const binary8::value_type binary8::max_value;
    const binary8::value_type binary8::min_value;
    const binary8::order_type binary8::order;
    const binary8::degree_type binary8::degree;
    const binary8::value_type binary8::prime;
    const bool binary8::is_exact;
}

#endif
