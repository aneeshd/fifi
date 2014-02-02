// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <fifi/binary.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>

#include "expected_results.hpp"

namespace fifi
{
    template<template <class> class FieldImpl>
    void check_region_add(uint32_t elements = 128)
    {
        {
            SCOPED_TRACE("binary");
            check_results_region_add<FieldImpl<fifi::binary> >(elements);
        }
        {
            SCOPED_TRACE("binary4");
            check_results_region_add<FieldImpl<fifi::binary4> >(elements);
        }
        {
            SCOPED_TRACE("binary8");
            check_results_region_add<FieldImpl<fifi::binary8> >(elements);
        }
        {
            SCOPED_TRACE("binary16");
            check_results_region_add<FieldImpl<fifi::binary16> >(elements);
        }
    }

    template<template <class> class FieldImpl>
    void check_region_subtract(uint32_t elements = 128)
    {
        {
            SCOPED_TRACE("binary");
            check_results_region_subtract<FieldImpl<fifi::binary> >(elements);
        }
        {
            SCOPED_TRACE("binary4");
            check_results_region_subtract<FieldImpl<fifi::binary4> >(elements);
        }
        {
            SCOPED_TRACE("binary8");
            check_results_region_subtract<FieldImpl<fifi::binary8> >(elements);
        }
        {
            SCOPED_TRACE("binary16");
            check_results_region_subtract<FieldImpl<fifi::binary16> >(elements);
        }
    }

    template<template <class> class FieldImpl>
    void check_region_multiply(uint32_t elements = 128)
    {
        {
            SCOPED_TRACE("binary");
            check_results_region_multiply<FieldImpl<fifi::binary> >(elements);
        }
        {
            SCOPED_TRACE("binary4");
            check_results_region_multiply<FieldImpl<fifi::binary4> >(elements);
        }
        {
            SCOPED_TRACE("binary8");
            check_results_region_multiply<FieldImpl<fifi::binary8> >(elements);
        }
        {
            SCOPED_TRACE("binary16");
            check_results_region_multiply<FieldImpl<fifi::binary16> >(elements);
        }
    }

    template<template <class> class FieldImpl>
    void check_region_divide(uint32_t elements = 128)
    {
        {
            SCOPED_TRACE("binary");
            check_results_region_divide<FieldImpl<fifi::binary> >(elements);
        }
        {
            SCOPED_TRACE("binary4");
            check_results_region_divide<FieldImpl<fifi::binary4> >(elements);
        }
        {
            SCOPED_TRACE("binary8");
            check_results_region_divide<FieldImpl<fifi::binary8> >(elements);
        }
        {
            SCOPED_TRACE("binary16");
            check_results_region_divide<FieldImpl<fifi::binary16> >(elements);
        }
    }

    template<template <class> class FieldImpl>
    void check_region_multiply_constant(uint32_t elements = 128)
    {
        {
            SCOPED_TRACE("binary");
            check_results_region_multiply_constant<FieldImpl<fifi::binary> >(elements);
        }
        {
            SCOPED_TRACE("binary4");
            check_results_region_multiply_constant<FieldImpl<fifi::binary4> >(elements);
        }
        {
            SCOPED_TRACE("binary8");
            check_results_region_multiply_constant<FieldImpl<fifi::binary8> >(elements);
        }
        {
            SCOPED_TRACE("binary16");
            check_results_region_multiply_constant<FieldImpl<fifi::binary16> >(elements);
        }
    }

    template<template <class> class FieldImpl>
    void check_region_multiply_add(uint32_t elements = 128)
    {
        {
            SCOPED_TRACE("binary");
            check_results_region_multiply_add<FieldImpl<fifi::binary> >(elements);
        }
        {
            SCOPED_TRACE("binary4");
            check_results_region_multiply_add<FieldImpl<fifi::binary4> >(elements);
        }
        {
            SCOPED_TRACE("binary8");
            check_results_region_multiply_add<FieldImpl<fifi::binary8> >(elements);
        }
        {
            SCOPED_TRACE("binary16");
            check_results_region_multiply_add<FieldImpl<fifi::binary16> >(elements);
        }
    }

    template<template <class> class FieldImpl>
    void check_region_multiply_subtract(uint32_t elements = 128)
    {
        {
            SCOPED_TRACE("binary");
            check_results_region_multiply_subtract<FieldImpl<fifi::binary> >(elements);
        }
        {
            SCOPED_TRACE("binary4");
            check_results_region_multiply_subtract<FieldImpl<fifi::binary4> >(elements);
        }
        {
            SCOPED_TRACE("binary8");
            check_results_region_multiply_subtract<FieldImpl<fifi::binary8> >(elements);
        }
        {
            SCOPED_TRACE("binary16");
            check_results_region_multiply_subtract<FieldImpl<fifi::binary16> >(elements);
        }
    }

    template<class FieldImpl>
    void check_region_all(uint32_t elements = 128)
    {
        {
            SCOPED_TRACE("multiply");
            check_results_region_multiply<FieldImpl>(elements);
        }
        {
            SCOPED_TRACE("divide");
            check_results_region_divide<FieldImpl>(elements);
        }
        {
            SCOPED_TRACE("add");
            check_results_region_add<FieldImpl>(elements);
        }
        {
            SCOPED_TRACE("subtract");
            check_results_region_subtract<FieldImpl>(elements);
        }
        {
            SCOPED_TRACE("multiply_constant");
            check_results_region_multiply_constant<FieldImpl>(elements);
        }
        {
            SCOPED_TRACE("multiply_add");
            check_results_region_multiply_add<FieldImpl>(elements);
        }
        {
            SCOPED_TRACE("multiply_subtract");
            check_results_region_multiply_subtract<FieldImpl>(elements);
        }
    }
}
