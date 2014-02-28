// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <fifi/fifi_utils.hpp>

#include <cstdint>
#include <random>
#include <limits>

namespace fifi
{
    template<class Field>
    struct random_constant
    {
        typedef Field field_type;
        typedef typename field_type::value_type value_type;

        static_assert(
            std::numeric_limits<uint32_t>::max() > field_type::max_value,
                      "We only create uint32_t sized random numbers");

        random_constant()
            : m_distribution(field_type::min_value, field_type::max_value)
        { }

        value_type value()
        {
            return (value_type)m_distribution(m_generator);
        }

        value_type pack()
        {
            return fifi::pack<field_type>(value());
        }

        std::uniform_int_distribution<uint32_t> m_distribution;
        std::mt19937 m_generator;

    };
}
