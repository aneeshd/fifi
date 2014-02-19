// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>
#include <vector>

/// @todo fix cannot compile sak::aligned_allocator without
#include <limits>

#include <sak/aligned_allocator.hpp>

#include "binary4.hpp"
#include "simple_online_arithmetic.hpp"
#include "final.hpp"

namespace fifi
{
    /// ssse3_binary4_full_table_dispatch
    /// ssse3_binary4_full_table
    ///
    /// Stack implementing SSSE3 SIMD accelerated finite field
    /// arithmetic. The following intrinsics are used available in the
    /// following SIMD versions:
    ///
    /// _mm_load_si128 (SSE2)
    /// _mm_set1_epi8 (SSE2)
    /// _mm_and_si128 (SSE2)
    /// _mm_shuffle_epi8 (SSSE3)
    /// _mm_srli_epi64 (SSE2)
    /// _mm_xor_si128 (SSE2)
    /// _mm_store_si128 (SSE2)
    ///
    /// Based on this we see that the minimum required instruction for
    /// this optimization is the Supplemental Streaming SIMD Extension
    /// 3 (SSSE3).
    class ssse3_binary4_full_table
        : public simple_online_arithmetic<final<binary4> >
    {
    public:

        /// The base class
        typedef simple_online_arithmetic<final<binary4> > base;

        /// The field type
        typedef binary4 field_type;

        /// Typedef of the data type used for each field element
        typedef binary4::value_type value_type;

    public:

        /// Constructor for the stack
        ssse3_binary4_full_table();

        /// Optimized function for multiply constant
        /// @copydoc layer::region_multiply_constant(
        ///      value_type*, value_type*) const
        void region_multiply_constant(value_type* dest, value_type constant,
            uint32_t length) const;

        /// @return true if the executable was built with SSSE3 binary4
        ///         full table support
        bool ssse3_binary4_full_table_enabled() const;

        /// @copydoc layer::granularity() const
        uint32_t granularity() const;

        /// @copydoc layer::alignment() const
        uint32_t alignment() const;

    private:

        /// The size of each step in the region loops
        uint32_t m_ssse3_size;

        /// The storage type
        typedef std::vector<uint8_t, sak::aligned_allocator<uint8_t> >
            aligned_vector;

        /// Storage for the high 4 bit multiplication table
        aligned_vector m_table_one;

        /// Storage for the low 4 bit multiplication table
        aligned_vector m_table_two;
    };
}
