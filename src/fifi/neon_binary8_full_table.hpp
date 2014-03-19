// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>
#include <vector>

#include <sak/aligned_allocator.hpp>

#include "binary8.hpp"

namespace fifi
{
    /// neon_binary8_full_table
    ///
    /// Stack implementing NEON SIMD-accelerated finite field
    /// arithmetic.
    class neon_binary8_full_table
    {
    public:

        /// @copydoc layer::field_type
        typedef binary8 field_type;

        /// @copydoc layer::value_type
        typedef binary8::value_type value_type;

    public:

        /// Constructor for the stack
        neon_binary8_full_table();

        /// @copydoc layer::region_add(
        ///     value_type*, value_type*, uint32_t) const
        void region_add(
            value_type* dest, const value_type* src, uint32_t length) const;

        /// @copydoc layer::region_subtract(
        ///     value_type*, value_type*, uint32_t) const
        void region_subtract(
            value_type* dest, const value_type* src, uint32_t length) const;

//         /// @copydoc layer::region_multiply_constant(
//         ///      value_type*, value_type, uint32_t) const
//         void region_multiply_constant(
//             value_type* dest, value_type constant, uint32_t length) const;
//
//         /// @copydoc layer::region_multiply_add(
//         ///     value_type*, const value_type*, value_type, uint32_t) const
//         void region_multiply_add(value_type* dest, const value_type* src,
//             value_type constant, uint32_t length) const;
//
//         /// @copydoc layer::region_multiply_subtract(
//         ///     value_type*, const value_type*, value_type, uint32_t) const
//         void region_multiply_subtract(value_type* dest, const value_type* src,
//             value_type constant, uint32_t length) const;

        /// @copydoc layer::alignment() const
        uint32_t alignment() const;

        /// @copydoc layer::max_alignment() const
        uint32_t max_alignment() const;

        /// @copydoc layer::granularity() const
        uint32_t granularity() const;

        /// @copydoc layer::max_granularity() const
        uint32_t max_granularity() const;

        /// @return true if the executable was built with SSSE3 binary8
        ///         full table support
        bool enabled() const;

    private:

        /// The storage type
        typedef std::vector<uint8_t, sak::aligned_allocator<uint8_t>>
            aligned_vector;

        /// Storage for the high 4 bit multiplication table
        aligned_vector m_table_one;

        /// Storage for the low 4 bit multiplication table
        aligned_vector m_table_two;
    };
}
