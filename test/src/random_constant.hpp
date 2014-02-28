// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <random>
#include <limits>
#include <cassert>

#include <fifi/fifi_utils.hpp>

namespace fifi
{
    template<class Field>
    struct random_constant
    {
        typedef Field field_type;
        typedef typename field_type::value_type value_type;

        random_constant() :
            m_distribution(field_type::min_value, field_type::max_value)
        { }

        value_type value()
        {
            // We only create uint32_t sized random numbers
            assert(
                std::numeric_limits<uint32_t>::max() >= field_type::max_value);
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
