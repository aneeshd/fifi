// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "expected_results.hpp"

namespace fifi
{
    template<template<class>class FieldImpl>
    void check_add()
    {
        check_results_add<FieldImpl<fifi::binary> >();
        check_results_add<FieldImpl<fifi::binary4> >();
        check_results_add<FieldImpl<fifi::binary8> >();
        check_results_add<FieldImpl<fifi::binary16> >();
    }

    template<template <class> class FieldImpl>
    void check_subtract()
    {
        check_results_subtract<FieldImpl<fifi::binary> >();
        check_results_subtract<FieldImpl<fifi::binary4> >();
        check_results_subtract<FieldImpl<fifi::binary8> >();
        check_results_subtract<FieldImpl<fifi::binary16> >();
    }

    template<template <class> class FieldImpl>
    void check_multiply()
    {
        check_results_multiply<FieldImpl<fifi::binary> >();
        check_results_multiply<FieldImpl<fifi::binary4> >();
        check_results_multiply<FieldImpl<fifi::binary8> >();
        check_results_multiply<FieldImpl<fifi::binary16> >();
    }

    template<template <class> class FieldImpl>
    void check_divide()
    {
        check_results_divide<FieldImpl<fifi::binary> >();
        check_results_divide<FieldImpl<fifi::binary4> >();
        check_results_divide<FieldImpl<fifi::binary8> >();
        check_results_divide<FieldImpl<fifi::binary16> >();
    }

    template<template <class> class FieldImpl>
    void check_invert()
    {
        check_results_invert<FieldImpl<fifi::binary> >();
        check_results_invert<FieldImpl<fifi::binary4> >();
        check_results_invert<FieldImpl<fifi::binary8> >();
        check_results_invert<FieldImpl<fifi::binary16> >();
    }

    template<template <class> class FieldImpl>
    void check_random()
    {

        check_random_default<FieldImpl<fifi::binary> >();
        check_random_default<FieldImpl<fifi::binary4> >();
        check_random_default<FieldImpl<fifi::binary8> >();
        check_random_default<FieldImpl<fifi::binary16> >();
    }

    template<class FieldImpl>
    void check_all()
    {
        check_results_multiply<FieldImpl>();
        check_results_divide<FieldImpl>();
        check_results_add<FieldImpl>();
        check_results_subtract<FieldImpl>();
        check_results_invert<FieldImpl>();
        check_random_default<FieldImpl>();
    }
}
