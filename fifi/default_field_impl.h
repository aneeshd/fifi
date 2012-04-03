// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#ifndef FIFI_DEFAULT_FIELD_IMPL_H
#define FIFI_DEFAULT_FIELD_IMPL_H

#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>

#include "field_types.h"
#include "simple_online.h"
#include "full_table.h"
#include "extended_log_table.h"

namespace fifi
{

    /// Choosing the right field implementation is a
    /// matter of speed and memory requirements. The
    /// default_field_impl choose for each field type
    /// an corresponding implementation which is know
    /// to provide a good trade-off.
    template<class Field>
    struct default_field_impl;

    /// For the binary field
    template<>
    struct default_field_impl<binary>
    {
        typedef simple_online<binary> type;
    };

    /// For the binary8 field
    template<>
    struct default_field_impl<binary8>
    {
        typedef full_table<binary8> type;
    };

    /// For the binary16 field
    template<>
    struct default_field_impl<binary16>
    {
        typedef extended_log_table<binary16> type;
    };

}

#endif

