// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <boost/utility/enable_if.hpp>

#include "is_binary.hpp"

namespace fifi
{
    /// SFINAE class to disable implementations if binary
    /// Can be used e.g. like this:
    ///
    ///     template<class Field>
    ///     typename disable_if_binary<Field>::type
    ///     function(...)
    ///     {
    ///         ...
    ///     }
    ///
    template<class Field>
    struct disable_if_binary : public boost::disable_if<is_binary<Field> >
    { };

}
