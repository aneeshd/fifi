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
    template<template<class> class FieldImpl>
    void check_add()
    {
        {
            SCOPED_TRACE("binary");
            check_results_add<FieldImpl<fifi::binary> >();
        }
        {
            SCOPED_TRACE("binary4");
            check_results_add<FieldImpl<fifi::binary4> >();
        }
        {
            SCOPED_TRACE("binary8");
            check_results_add<FieldImpl<fifi::binary8> >();
        }
        {
            SCOPED_TRACE("binary16");
            check_results_add<FieldImpl<fifi::binary16> >();
        }
    }

    template<template <class> class FieldImpl>
    void check_subtract()
    {
        {
            SCOPED_TRACE("binary");
            check_results_subtract<FieldImpl<fifi::binary> >();
        }
        {
            SCOPED_TRACE("binary4");
            check_results_subtract<FieldImpl<fifi::binary4> >();
        }
        {
            SCOPED_TRACE("binary8");
            check_results_subtract<FieldImpl<fifi::binary8> >();
        }
        {
            SCOPED_TRACE("binary16");
            check_results_subtract<FieldImpl<fifi::binary16> >();
        }
    }

    template<template <class> class FieldImpl>
    void check_multiply()
    {
        {
            SCOPED_TRACE("binary");
            check_results_multiply<FieldImpl<fifi::binary> >();
        }
        {
            SCOPED_TRACE("binary4");
            check_results_multiply<FieldImpl<fifi::binary4> >();
        }
        {
            SCOPED_TRACE("binary8");
            check_results_multiply<FieldImpl<fifi::binary8> >();
        }
        {
            SCOPED_TRACE("binary16");
            check_results_multiply<FieldImpl<fifi::binary16> >();
        }
    }

    template<template <class> class FieldImpl>
    void check_divide()
    {
        {
            SCOPED_TRACE("binary");
            check_results_divide<FieldImpl<fifi::binary> >();
        }
        {
            SCOPED_TRACE("binary4");
            check_results_divide<FieldImpl<fifi::binary4> >();
        }
        {
            SCOPED_TRACE("binary8");
            check_results_divide<FieldImpl<fifi::binary8> >();
        }
        {
            SCOPED_TRACE("binary16");
            check_results_divide<FieldImpl<fifi::binary16> >();
        }
    }

    template<template <class> class FieldImpl>
    void check_invert()
    {
        {
            SCOPED_TRACE("binary");
            check_results_invert<FieldImpl<fifi::binary> >();
        }
        {
            SCOPED_TRACE("binary4");
            check_results_invert<FieldImpl<fifi::binary4> >();
        }
        {
            SCOPED_TRACE("binary8");
            check_results_invert<FieldImpl<fifi::binary8> >();
        }
        {
            SCOPED_TRACE("binary16");
            check_results_invert<FieldImpl<fifi::binary16> >();
        }
    }

    template<template <class> class FieldImpl>
    void check_random()
    {

        {
            SCOPED_TRACE("binary");
            check_random_default<FieldImpl<fifi::binary> >();
        }
        {
            SCOPED_TRACE("binary4");
            check_random_default<FieldImpl<fifi::binary4> >();
        }
        {
            SCOPED_TRACE("binary8");
            check_random_default<FieldImpl<fifi::binary8> >();
        }
        {
            SCOPED_TRACE("binary16");
            check_random_default<FieldImpl<fifi::binary16> >();
        }
    }

    template<class FieldImpl>
    void check_all()
    {
        {
            SCOPED_TRACE("multiply");
            check_results_multiply<FieldImpl>();
        }
        {
            SCOPED_TRACE("divide");
            check_results_divide<FieldImpl>();
        }
        {
            SCOPED_TRACE("add");
            check_results_add<FieldImpl>();
        }
        {
            SCOPED_TRACE("subtract");
            check_results_subtract<FieldImpl>();
        }
        {
            SCOPED_TRACE("invert");
            check_results_invert<FieldImpl>();
        }
        {
            SCOPED_TRACE("random");
            check_random_default<FieldImpl>();
        }
    }
}
