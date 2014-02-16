// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <fifi/region_arithmetic.hpp>
#include <fifi/simple_online.hpp>
#include <fifi/optimal_prime.hpp>
#include <fifi/is_packed_constant.hpp>

namespace fifi
{

    template<class Field>
    struct reference_selector
    {
        typedef fifi::simple_online<Field> reference_field;
    };

    template<>
    struct reference_selector<prime2325>
    {
        typedef fifi::optimal_prime<prime2325> reference_field;
    };


    // Helper class which creates a reference stack that uses region_arithmetic
    // functions to create reference results.
    template<class Field>
    class helper_region_reference : public
        region_arithmetic<typename reference_selector<Field>::reference_field>
    { };
}
