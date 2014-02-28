// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

#include <fifi/binary.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>

#include "expected_results.hpp"

namespace fifi
{
    /// Helper function which given a field implementation will
    /// instantiate it (with the different binary extension fields)
    /// and perform the unit tests for region arithmetic.
    ///
    /// Note: This function is usually called indirectly through the
    /// check_region_all() helper function.
    template<template <class> class FieldImpl>
    void check_region_add()
    {
        {
            SCOPED_TRACE("binary");
            check_results_region_add<
                FieldImpl<fifi::binary> >();
        }
        {
            SCOPED_TRACE("binary4");
            check_results_region_add<
                FieldImpl<fifi::binary4> >();
        }
        {
            SCOPED_TRACE("binary8");
            check_results_region_add<
                FieldImpl<fifi::binary8> >();
        }
        {
            SCOPED_TRACE("binary16");
            check_results_region_add<
                FieldImpl<fifi::binary16> >();
        }
    }

    /// @copydoc check_region_add()
    template<template <class> class FieldImpl>
    void check_region_subtract()
    {
        {
            SCOPED_TRACE("binary");
            check_results_region_subtract<
                FieldImpl<fifi::binary> >();
        }
        {
            SCOPED_TRACE("binary4");
            check_results_region_subtract<
                FieldImpl<fifi::binary4> >();
        }
        {
            SCOPED_TRACE("binary8");
            check_results_region_subtract<
                FieldImpl<fifi::binary8> >();
        }
        {
            SCOPED_TRACE("binary16");
            check_results_region_subtract<
                FieldImpl<fifi::binary16> >();
        }
    }

    /// @copydoc check_region_add()
    template<template <class> class FieldImpl>
    void check_region_multiply()
    {
        {
            SCOPED_TRACE("binary");
            check_results_region_multiply<
                FieldImpl<fifi::binary> >();
        }
        {
            SCOPED_TRACE("binary4");
            check_results_region_multiply<
                FieldImpl<fifi::binary4> >();
        }
        {
            SCOPED_TRACE("binary8");
            check_results_region_multiply<
                FieldImpl<fifi::binary8> >();
        }
        {
            SCOPED_TRACE("binary16");
            check_results_region_multiply<
                FieldImpl<fifi::binary16> >();
        }
    }

    /// @copydoc check_region_add()
    template<template <class> class FieldImpl>
    void check_region_divide()
    {
        {
            SCOPED_TRACE("binary");
            check_results_region_divide<
                FieldImpl<fifi::binary> >();
        }
        {
            SCOPED_TRACE("binary4");
            check_results_region_divide<
                FieldImpl<fifi::binary4> >();
        }
        {
            SCOPED_TRACE("binary8");
            check_results_region_divide<
                FieldImpl<fifi::binary8> >();
        }
        {
            SCOPED_TRACE("binary16");
            check_results_region_divide<
                FieldImpl<fifi::binary16> >();
        }
    }

    /// @copydoc check_region_add()
    template<template <class> class FieldImpl>
    void check_region_multiply_constant()
    {
        {
            SCOPED_TRACE("binary");
            check_results_region_multiply_constant<
                FieldImpl<fifi::binary> >();
        }
        {
            SCOPED_TRACE("binary4");
            check_results_region_multiply_constant<
                FieldImpl<fifi::binary4> >();
        }
        {
            SCOPED_TRACE("binary8");
            check_results_region_multiply_constant<
                FieldImpl<fifi::binary8> >();
        }
        {
            SCOPED_TRACE("binary16");
            check_results_region_multiply_constant<
                FieldImpl<fifi::binary16> >();
        }
    }

    /// @copydoc check_region_add()
    template<template <class> class FieldImpl>
    void check_region_multiply_add()
    {
        {
            SCOPED_TRACE("binary");
            check_results_region_multiply_add<
                FieldImpl<fifi::binary> >();
        }
        {
            SCOPED_TRACE("binary4");
            check_results_region_multiply_add<
                FieldImpl<fifi::binary4> >();
        }
        {
            SCOPED_TRACE("binary8");
            check_results_region_multiply_add<
                FieldImpl<fifi::binary8> >();
        }
        {
            SCOPED_TRACE("binary16");
            check_results_region_multiply_add<
                FieldImpl<fifi::binary16> >();
        }
    }

    /// @copydoc check_region_add()
    template<template <class> class FieldImpl>
    void check_region_multiply_subtract()
    {
        {
            SCOPED_TRACE("binary");
            check_results_region_multiply_subtract<
                FieldImpl<fifi::binary> >();
        }
        {
            SCOPED_TRACE("binary4");
            check_results_region_multiply_subtract<
                FieldImpl<fifi::binary4> >();
        }
        {
            SCOPED_TRACE("binary8");
            check_results_region_multiply_subtract<
                FieldImpl<fifi::binary8> >();
        }
        {
            SCOPED_TRACE("binary16");
            check_results_region_multiply_subtract<
                FieldImpl<fifi::binary16> >();
        }
    }

    /// Helper function that given a field implementation will invoke
    /// all the different check_region_xxx() functions.
    template<class FieldImpl>
    void check_region_all()
    {
        {
            SCOPED_TRACE("multiply");
            check_results_region_multiply<FieldImpl>();
        }
        {
            SCOPED_TRACE("divide");
            check_results_region_divide<FieldImpl>();
        }
        {
            SCOPED_TRACE("add");
            check_results_region_add<FieldImpl>();
        }
        {
            SCOPED_TRACE("subtract");
            check_results_region_subtract<FieldImpl>();
        }
        {
            SCOPED_TRACE("multiply_constant");
            check_results_region_multiply_constant<FieldImpl>();
        }
        {
            SCOPED_TRACE("multiply_add");
            check_results_region_multiply_add<FieldImpl>();
        }
        {
            SCOPED_TRACE("multiply_subtract");
            check_results_region_multiply_subtract<FieldImpl>();
        }
    }
}
