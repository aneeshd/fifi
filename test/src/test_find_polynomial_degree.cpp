// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/final.hpp>
#include <fifi/find_polynomial_degree.hpp>
#include <fifi/prime2325.hpp>

#include <gtest/gtest.h>

#include "fifi_unit_test/expected_results.hpp"


namespace fifi
{
    namespace
    {
        template<class Field>
        struct dummy_stack : public final<Field>
        {
            typedef Field field_type;
            typedef typename field_type::value_type value_type;

            value_type calculate(value_type a)
            {
                return find_polynomial_degree<field_type>(a);
            }
        };
    }
}

template<class Field>
inline void check_results_find_polynomial_degree()
{
    check_results_unary<
        fifi::dummy_stack<Field>,
        find_polynomial_degree_results
    >(std::mem_fn(&fifi::dummy_stack<Field>::calculate));
}

TEST(test_find_polynomial_degree, find_polynomial_degree)
{
    {
        SCOPED_TRACE("binary");
        check_results_find_polynomial_degree<fifi::binary>();
    }
    {
        SCOPED_TRACE("binary4");
        check_results_find_polynomial_degree<fifi::binary4>();
    }
    {
        SCOPED_TRACE("binary8");
        check_results_find_polynomial_degree<fifi::binary8>();
    }
    {
        SCOPED_TRACE("binary16");
        check_results_find_polynomial_degree<fifi::binary16>();
    }
    {
        SCOPED_TRACE("prime2325");
        check_results_find_polynomial_degree<fifi::prime2325>();
    }
}
