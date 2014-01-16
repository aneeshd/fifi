// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <fifi/field_types.hpp>

/// Definition of the multiply_results struct
template<class Field>
struct multiply_results;

/// Specialized struct which contains the multiplication
/// results for the binary4 field
template<>
struct multiply_results<fifi::binary4>
{
    static const expected_result_binary<fifi::binary4> m_results[];
    static const uint32_t m_size;
};

/// Specialized struct which contains the multiplication
/// results for the binary8 field
template<>
struct multiply_results<fifi::binary8>
{
    static const expected_result_binary<fifi::binary8> m_results[];
    static const uint32_t m_size;
};

/// Specialized struct which contains the multiplication
/// results for the binary16 field
template<>
struct multiply_results<fifi::binary16>
{
    static const expected_result_binary<fifi::binary16> m_results[];
    static const uint32_t m_size;
};

/// Specialized struct which contains the multiplication
/// results for the prime2325 field
template<>
struct multiply_results<fifi::prime2325>
{
    static const expected_result_binary<fifi::prime2325> m_results[];
    static const uint32_t m_size;
};
