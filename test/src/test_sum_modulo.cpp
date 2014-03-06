// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <functional>

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/final.hpp>
#include <fifi/prime2325.hpp>
#include <fifi/sum_modulo.hpp>

#include <gtest/gtest.h>

#include "expected_results.hpp"

namespace fifi
{
    namespace
    {
        template<class Field>
        struct dummy_stack : public final<Field>
        {
            typedef Field field_type;
            typedef typename field_type::value_type value_type;

            value_type calculate(value_type a, value_type b)
            {
                return sum_modulo<field_type>(a,b);
            }
        };
    }
}


template<class Field>
inline void check_results_sum_modulo()
{
    check_results_binary<
        fifi::dummy_stack<Field>,
        sum_modulo_results>(
            std::mem_fn(&fifi::dummy_stack<Field>::calculate));
}


TEST(test_sum_modulo, sum_modulo)
{
    {
        SCOPED_TRACE("binary");
        check_results_sum_modulo<fifi::binary>();
    }
    {
        SCOPED_TRACE("binary4");
        check_results_sum_modulo<fifi::binary4>();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_sum_modulo<fifi::binary8>();
    }
    {
        SCOPED_TRACE("binary16");
        check_results_sum_modulo<fifi::binary16>();
    }
    {
        SCOPED_TRACE("prime2325");
        check_results_sum_modulo<fifi::prime2325>();
    }
}
