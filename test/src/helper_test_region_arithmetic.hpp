// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "expected_results.hpp"

namespace fifi
{
    template<template <class> FieldImpl>
    void check_region_add()
    {
        check_results_region_add<FieldImpl<fifi::binary> >();
        check_results_region_add<FieldImpl<fifi::binary4> >();
        check_results_region_add<FieldImpl<fifi::binary8> >();
        check_results_region_add<FieldImpl<fifi::binary16> >();
    }

    template<template <class> FieldImpl>
    void check_region_subtract()
    {
        check_results_region_subtract<FieldImpl<fifi::binary> >();
        check_results_region_subtract<FieldImpl<fifi::binary4> >();
        check_results_region_subtract<FieldImpl<fifi::binary8> >();
        check_results_region_subtract<FieldImpl<fifi::binary16> >();
    }

    template<template <class> FieldImpl>
    void check_region_multiply()
    {
        check_results_region_multiply<FieldImpl<fifi::binary> >();
        check_results_region_multiply<FieldImpl<fifi::binary4> >();
        check_results_region_multiply<FieldImpl<fifi::binary8> >();
        check_results_region_multiply<FieldImpl<fifi::binary16> >();
    }

    template<template <class> FieldImpl>
    void check_region_divide()
    {
        check_results_region_divide<FieldImpl<fifi::binary> >();
        check_results_region_divide<FieldImpl<fifi::binary4> >();
        check_results_region_divide<FieldImpl<fifi::binary8> >();
        check_results_region_divide<FieldImpl<fifi::binary16> >();
    }

    template<template <class> FieldImpl>
    void check_region_invert()
    {
        check_results_region_invert<FieldImpl<fifi::binary> >();
        check_results_region_invert<FieldImpl<fifi::binary4> >();
        check_results_region_invert<FieldImpl<fifi::binary8> >();
        check_results_region_invert<FieldImpl<fifi::binary16> >();
    }
}
