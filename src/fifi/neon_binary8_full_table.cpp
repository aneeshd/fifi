// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdio>
#include <platform/config.hpp>
#include <cpuid/cpuinfo.hpp>

// Include x86 intrinsics for GCC-compatible compilers on x86/x86_64
#if defined(PLATFORM_NEON)
#include <arm_neon.h>
#endif

#include "simple_online_arithmetic.hpp"
#include "final.hpp"

#include "neon_binary8_full_table.hpp"

namespace fifi
{

#ifdef PLATFORM_NEON

    neon_binary8_full_table::neon_binary8_full_table()
    {
        simple_online_arithmetic<final<binary8>> field;

        m_table_one.resize(256 * 16);
        m_table_two.resize(256 * 16);

        assert(((uintptr_t) &m_table_one[0] % 16) == 0);
        assert(((uintptr_t) &m_table_two[0] % 16) == 0);

        // Iterate over all elements in the field
        for (uint32_t i = 0; i < 256; ++i)
        {
            // Only take the constants whose first 4 bits are zero
            for (uint32_t j = 0; j < 16; ++j)
            {
                // Calculate 8-bit product with the low-half
                auto v1 = field.multiply(i, j);
                m_table_one[i * 16 + j] = v1;
                // Calculate 8-bit product with the high-half
                auto v2 = field.multiply(i, j << 4);
                m_table_two[i * 16 + j] = v2;
            }
        }
    }

    void neon_binary8_full_table::region_add(
        value_type* dest, const value_type* src, uint32_t length) const
    {
        assert(dest != 0);
        assert(src != 0);
        assert(length > 0);
        assert((length % granularity()) == 0);

        //assert(((uintptr_t)dest % 16) == 0);
        //assert(((uintptr_t)src % 16) == 0);

        // We loop 16 bytes at-a-time so we calculate how many loops we need
        uint32_t simd_size = length / granularity();
        assert(simd_size > 0);

        uint64_t* src_ptr = (uint64_t*)src;
        uint64_t* dest_ptr = (uint64_t*)dest;
        for (uint32_t i = 0; i < simd_size; i++, src_ptr+=2, dest_ptr+=2)
        {
            // Load the next 16-bytes of the destination and source buffers
            uint64x2_t q0 = vld1q_u64(dest_ptr);
            uint64x2_t q1 = vld1q_u64(src_ptr);
            // Xor these values together
            uint64x2_t result = veorq_u64(q0, q1);
            // Store the result in the destination buffer
            vst1q_u64(dest_ptr, result);
        }
    }

    void neon_binary8_full_table::region_subtract(
        value_type* dest, const value_type* src, uint32_t length) const
    {
        // In a binary extension field addition is the same as subtraction
        region_add(dest, src, length);
    }

    void neon_binary8_full_table::region_multiply_constant(
        value_type* dest, value_type constant, uint32_t length) const
    {
        assert(dest != 0);
        assert(length > 0);
        assert((length % granularity()) == 0);

        //assert(((uintptr_t)dest % 16) == 0);
        //assert(((uintptr_t)src % 16) == 0);

        // We loop 16 bytes at-a-time so we calculate how many loops we need
        uint32_t simd_size = length / granularity();
        assert(simd_size > 0);

        #define uint8x16_to_8x8x2(v) ((uint8x8x2_t) { vget_low_u8(v), vget_high_u8(v) } )

        // Initialize the look-up tables
        // Load the 16-byte row that contains pre-calculated multiplication
        // results with the low-half of the constant
        uint8x8x2_t table1 = uint8x16_to_8x8x2(
            vld1q_u8(&m_table_one[0] + constant * 16));

        // table2 contains the results with the high-half of the constant
        uint8x8x2_t table2 = uint8x16_to_8x8x2(
            vld1q_u8(&m_table_two[0] + constant * 16));

        // Create low and high bitmasks by replicating the mask values 16 times
        uint8x8_t mask1 = vdup_n_u8((uint8_t)0x0f);
        uint8x8_t mask2 = vdup_n_u8((uint8_t)0xf0);

        uint8_t* dest_ptr = (uint8_t*)dest;
        for (uint32_t i = 0; i < simd_size * 2; i++, dest_ptr++)
        {
            // Load the next 8-bytes of the destination buffer
            uint8x8_t q0 = vld1_u8(dest_ptr);
            // Apply mask1 to get the low-half of the data
            uint8x8_t l = vand_u8(q0, mask1);
            // Perform 8 simultaneous table lookups to multiply the low-half
            l = vtbl2_u8(table1, l);
            // Apply mask2 to get the high-half of the data
            uint8x8_t h = vand_u8(q0, mask2);
            // Right shift the high-half by 4 bits to get values in [0,15]
            h = vshr_n_u8(h, 4);
            // Perform table lookup with these indices to multiply the high-half
            h = vtbl2_u8(table2, h);
            // Xor the high and low halves together to get the final result
            uint8x8_t result = veor_u8(h, l);
            // Store the result in the destination buffer
            vst1_u8(dest_ptr, result);
        }
    }

//     void neon_binary8_full_table::region_multiply_add(value_type* dest,
//         const value_type* src, value_type constant, uint32_t length) const
//     {
//         assert(dest != 0);
//         assert(src != 0);
//         assert(length > 0);
//         assert((length % granularity()) == 0);
//
//         // We loop 16 bytes at-a-time so we calculate how many loops we need
//         uint32_t simd_size = length / granularity();
//         assert(simd_size > 0);
//
//         // Initialize the look-up tables
//         // Load the 16-byte row that contains pre-calculated multiplication
//         // results with the constant
//         __m128i table1 = _mm_load_si128(
//             (const __m128i*)(&m_table_one[0] + (constant * 16)));
//
//         // table2 contains the same results shifted left by 4 bits
//         __m128i table2 = _mm_load_si128(
//             (const __m128i*)(&m_table_two[0] + (constant * 16)));
//
//         // Create low and high bitmasks by replicating the mask values 16 times
//         __m128i mask1 = _mm_set1_epi8((char)0x0f);
//         __m128i mask2 = _mm_set1_epi8((char)0xf0);
//
//         __m128i* src_ptr = (__m128i*)src;
//         __m128i* dest_ptr = (__m128i*)dest;
//         for (uint32_t i = 0; i < simd_size; i++, src_ptr++, dest_ptr++)
//         {
//             // Multiply the src with the constant
//
//             // Load the next 16-bytes of the source buffer
//             __m128i xmm0 = _mm_loadu_si128(src_ptr);
//             // Apply mask1 to get the low-half of the data
//             __m128i l = _mm_and_si128(xmm0, mask1);
//             // Perform 16 simultaneous table lookups to multiply the low-half
//             l = _mm_shuffle_epi8(table1, l);
//             // Apply mask2 to get the high-half of the data
//             __m128i h = _mm_and_si128(xmm0, mask2);
//             // Right shift the high-half by 4 bits to get values in [0,15]
//             h = _mm_srli_epi64(h, 4);
//             // Perform table lookup with these indices to multiply the high-half
//             h = _mm_shuffle_epi8(table2, h);
//             // Xor the high and low halves together to get the final result
//             xmm0 = _mm_xor_si128(h, l);
//
//             // Add the src to the dest
//
//             // Load the next 16-bytes of the destination buffer
//             __m128i xmm1 = _mm_loadu_si128(dest_ptr);
//             // Xor the multiplication result and the destination value
//             xmm0 = _mm_xor_si128(xmm0, xmm1);
//             // Store the result in the destination buffer
//             _mm_storeu_si128(dest_ptr, xmm0);
//         }
//     }
//
//     void neon_binary8_full_table::region_multiply_subtract(value_type* dest,
//         const value_type* src, value_type constant, uint32_t length) const
//     {
//         // In a binary extension field addition is the same as subtraction
//         region_multiply_add(dest, src, constant, length);
//     }


    uint32_t neon_binary8_full_table::alignment() const
    {
        return 1U;
    }

    uint32_t neon_binary8_full_table::max_alignment() const
    {
        return alignment();
    }

    uint32_t neon_binary8_full_table::granularity() const
    {
        // We are working over 16 bytes (128 bits) at a time, so we
        // require a length granularity of 16. We expect that binary8
        // uses uint8_t as value_type
        static_assert(std::is_same<value_type, uint8_t>::value,
            "Here we expect binary8 to use uint8_t as value_type");
        return 16U;
    }

    uint32_t neon_binary8_full_table::max_granularity() const
    {
        return granularity();
    }

    bool neon_binary8_full_table::enabled() const
    {
        static cpuid::cpuinfo info;
        return info.has_neon();
    }

#else

    neon_binary8_full_table::neon_binary8_full_table()
    { }

    void neon_binary8_full_table::region_add(
        value_type*, const value_type*, uint32_t) const
    {
        // Not implemented
        assert(0);
    }

    void neon_binary8_full_table::region_subtract(
        value_type*, const value_type*, uint32_t) const
    {
        // Not implemented
        assert(0);
    }

    void neon_binary8_full_table::region_multiply_constant(
        value_type*, value_type, uint32_t) const
    {
        // Not implemented
        assert(0);
    }

//     void neon_binary8_full_table::region_multiply_add(
//         value_type*, const value_type*, value_type, uint32_t) const
//     {
//         // Not implemented
//         assert(0);
//     }
//
//     void neon_binary8_full_table::region_multiply_subtract(
//         value_type*, const value_type*, value_type, uint32_t) const
//     {
//         // Not implemented
//         assert(0);
//     }

    uint32_t neon_binary8_full_table::alignment() const
    {
        // Not implemented
        assert(0);
        return 0;
    }

    uint32_t neon_binary8_full_table::max_alignment() const
    {
        // Not implemented
        assert(0);
        return 0;
    }

    uint32_t neon_binary8_full_table::granularity() const
    {
        // Not implemented
        assert(0);
        return 0;
    }

    uint32_t neon_binary8_full_table::max_granularity() const
    {
        // Not implemented
        assert(0);
        return 0;
    }

    bool neon_binary8_full_table::enabled() const
    {
        return false;
    }

#endif

}
