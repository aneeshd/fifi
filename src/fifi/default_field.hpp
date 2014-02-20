// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "binary.hpp"
#include "binary4.hpp"
#include "binary16.hpp"
#include "binary8.hpp"
#include "extended_log_table.hpp"
#include "full_table.hpp"
#include "optimal_prime.hpp"
#include "prime2325.hpp"
#include "simple_online.hpp"

namespace fifi
{
    /// Choosing the right field implementation is a matter of speed
    /// and memory requirements. The default_field chosen for each
    /// field represents a corresponding implementation which is known
    /// to provide a good trade-off.

    template<class Field>
    struct default_field;

    /// For the binary field
    template<>
    struct default_field<binary>
    {
        /// default field implementation type
        typedef simple_online<binary> type;
    };

    /// For the binary4 field
    template<>
    struct default_field<binary4>
    {
        /// default field implementation type
        typedef full_table<binary4> type;
    };

    /// For the binary8 field
    template<>
    struct default_field<binary8>
    {
        /// default field implementation type
        typedef full_table<binary8> type;
    };

    /// For the binary16 field
    template<>
    struct default_field<binary16>
    {
        /// default field implementation type
        typedef extended_log_table<binary16> type;
    };

    /// For the prime2325 field
    template<>
    struct default_field<prime2325>
    {
        /// default field implementation type
        typedef optimal_prime<prime2325> type;
    };
}
