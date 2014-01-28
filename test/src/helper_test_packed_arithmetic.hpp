// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "expected_results.hpp"

namespace fifi
{
    template<template <class> FieldImpl>
    void check_packed_add()
    {
        check_results_packed_add<FieldImpl<fifi::binary> >();
        check_results_packed_add<FieldImpl<fifi::binary4> >();
        check_results_packed_add<FieldImpl<fifi::binary8> >();
        check_results_packed_add<FieldImpl<fifi::binary16> >();
    }

    template<template <class> FieldImpl>
    void check_packed_subtract()
    {
        check_results_packed_subtract<FieldImpl<fifi::binary> >();
        check_results_packed_subtract<FieldImpl<fifi::binary4> >();
        check_results_packed_subtract<FieldImpl<fifi::binary8> >();
        check_results_packed_subtract<FieldImpl<fifi::binary16> >();
    }

    template<template <class> FieldImpl>
    void check_packed_multiply()
    {
        check_results_packed_multiply<FieldImpl<fifi::binary> >();
        check_results_packed_multiply<FieldImpl<fifi::binary4> >();
        check_results_packed_multiply<FieldImpl<fifi::binary8> >();
        check_results_packed_multiply<FieldImpl<fifi::binary16> >();
    }

    template<template <class> FieldImpl>
    void check_packed_divide()
    {
        check_results_packed_divide<FieldImpl<fifi::binary> >();
        check_results_packed_divide<FieldImpl<fifi::binary4> >();
        check_results_packed_divide<FieldImpl<fifi::binary8> >();
        check_results_packed_divide<FieldImpl<fifi::binary16> >();
    }

    template<template <class> FieldImpl>
    void check_packed_invert()
    {
        check_results_packed_invert<FieldImpl<fifi::binary> >();
        check_results_packed_invert<FieldImpl<fifi::binary4> >();
        check_results_packed_invert<FieldImpl<fifi::binary8> >();
        check_results_packed_invert<FieldImpl<fifi::binary16> >();
    }

    template<class FieldImpl>
    void check_all()
    {
        check_results_packed_multiply<FieldImpl>();
        check_results_packed_divide<FieldImpl>();
        check_results_packed_add<FieldImpl>();
        check_results_packed_subtract<FieldImpl>();
        check_results_packed_invert<FieldImpl>();
    }
}
