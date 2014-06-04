// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "has_basic_super.hpp"

#include "region_dispatcher_specialization.hpp"

#include <sak/easy_bind.hpp>

namespace fifi
{
    /// @brief Helper class for easing the use of
    /// region_dispatcher_specialization.
    ///
    /// The region_dispatcher layer "extracts" the information needed
    /// by the region_dispatcher_specilization making the embedding
    /// nicer.
    template<class Stack, class Super>
    using region_dispatcher = region_dispatcher_specialization<
        typename Super::field_type, Stack,
        typename Stack::field_type, Super>;
}
