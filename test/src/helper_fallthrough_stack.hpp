// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "helper_fallthrough.hpp"

namespace fifi
{
    template<template <class,class> class Arithmetic, class Field>
    struct helper_fallthrough_stack : public
    Arithmetic<Field, helper_fallthrough<Field> >
    { };
}
