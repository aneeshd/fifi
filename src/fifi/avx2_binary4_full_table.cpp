// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <platform/config.hpp>
#include <cpuid/cpuinfo.hpp>

// Include x86 intrinsics for GCC-compatible compilers on x86/x86_64
#if defined(PLATFORM_GCC_COMPATIBLE_X86)
#include <x86intrin.h>
#endif

#include "simple_online_arithmetic.hpp"
#include "final.hpp"

#include "avx2_binary4_full_table.hpp"

namespace fifi
{

#ifdef PLATFORM_AVX2

    avx2_binary4_full_table::avx2_binary4_full_table()
    {
        simple_online_arithmetic<final<binary4>> field;

        m_table_one.resize(16 * 32);
        m_table_two.resize(16 * 32);

        for (uint32_t i = 0; i < 16; ++i)
        {
            for (uint32_t j = 0; j < 16; ++j)
            {
                auto v = field.multiply(i, j);

                m_table_one[i * 32 + j] = v & 0x0f;
                m_table_one[i * 32 + j + 16] = v & 0x0f;
                m_table_two[i * 32 + j] = (v << 4) & 0xf0;
                m_table_two[i * 32 + j + 16] = (v << 4) & 0xf0;
            }
        }
    }

    void avx2_binary4_full_table::region_add(
        value_type* dest, const value_type* src, uint32_t length) const
    {
        assert(dest != 0);
        assert(src != 0);
        assert(length > 0);
        assert((length % granularity()) == 0);

        // We loop 16 bytes at-a-time so we calculate how many loops we need
        uint32_t simd_size = length / granularity();
        assert(simd_size > 0);

        __m256i* src_ptr = (__m256i*)src;
        __m256i* dest_ptr = (__m256i*)dest;
        for (uint32_t i = 0; i < simd_size; i++, src_ptr++, dest_ptr++)
        {
            // Load the next 16-bytes of the destination and source buffers
            __m256i ymm0 = _mm256_loadu_si256(dest_ptr);
            __m256i ymm1 = _mm256_loadu_si256(src_ptr);
            // Xor these values together
            ymm0 = _mm256_xor_si256(ymm0, ymm1);
            // Store the result in the destination buffer
            _mm256_storeu_si256(dest_ptr, ymm0);
        }
    }

    void avx2_binary4_full_table::region_subtract(
        value_type* dest, const value_type* src, uint32_t length) const
    {
        // In a binary extension field addition is the same as subtraction
        region_add(dest, src, length);
    }

    void avx2_binary4_full_table::region_multiply_constant(
        value_type* dest, value_type constant, uint32_t length) const
    {
        assert(dest != 0);
        assert(length > 0);
        assert((length % granularity()) == 0);

        // We loop 16 bytes at-a-time so we calculate how many loops we need
        uint32_t simd_size = length / granularity();
        assert(simd_size > 0);

        // The constant is packed, so we need just either the high or
        // low 4 bits to get constant value
        constant = constant & 0xf;

        // Initialize the look-up tables
        // Load the 32-byte row that contains pre-calculated multiplication
        // results with the constant
        __m256i table1 = _mm256_loadu_si256(
            (const __m256i*)(&m_table_one[0] + (constant * 32)));

        // table2 contains the same results shifted left by 4 bits
        __m256i table2 = _mm256_loadu_si256(
            (const __m256i*)(&m_table_two[0] + (constant * 32)));

        // Create low and high bitmasks by replicating the mask values 32 times
        __m256i mask1 = _mm256_set1_epi8((char)0x0f);
        __m256i mask2 = _mm256_set1_epi8((char)0xf0);

        __m256i* dest_ptr = (__m256i*)dest;
        for (uint32_t i = 0; i < simd_size; i++, dest_ptr++)
        {
            // Load the next 16-bytes of the destination buffer
            __m256i ymm0 = _mm256_loadu_si256(dest_ptr);
            // Apply mask1 to get the low-half of the data
            __m256i l = _mm256_and_si256(ymm0, mask1);
            // Perform 32 simultaneous table lookups to multiply the low-half
            l = _mm256_shuffle_epi8(table1, l);
            // Apply mask2 to get the high-half of the data
            __m256i h = _mm256_and_si256(ymm0, mask2);
            // Right shift the high-half by 4 bits to get values in [0,15]
            h = _mm256_srli_epi64(h, 4);
            // Perform table lookup with these indices to multiply the high-half
            h = _mm256_shuffle_epi8(table2, h);
            // Xor the high and low halves together to get the final result
            ymm0 = _mm256_xor_si256(h, l);
            // Store the result in the destination buffer
            _mm256_storeu_si256(dest_ptr, ymm0);
        }
    }

    void avx2_binary4_full_table::region_multiply_add(value_type* dest,
        const value_type* src, value_type constant, uint32_t length) const
    {
        assert(dest != 0);
        assert(src != 0);
        assert(length > 0);
        assert((length % granularity()) == 0);

        // We loop 16 bytes at-a-time so we calculate how many loops we need
        uint32_t simd_size = length / granularity();
        assert(simd_size > 0);

        // The constant is packed, so we need just either the high or
        // low 4 bits to get constant value
        constant = constant & 0xf;

        // Initialize the look-up tables
        // Load the 32-byte row that contains pre-calculated multiplication
        // results with the constant
        __m256i table1 = _mm256_loadu_si256(
            (const __m256i*)(&m_table_one[0] + (constant * 32)));

        // table2 contains the same results shifted left by 4 bits
        __m256i table2 = _mm256_loadu_si256(
            (const __m256i*)(&m_table_two[0] + (constant * 32)));

        // Create low and high bitmasks by replicating the mask values 32 times
        __m256i mask1 = _mm256_set1_epi8((char)0x0f);
        __m256i mask2 = _mm256_set1_epi8((char)0xf0);

        __m256i* src_ptr = (__m256i*)src;
        __m256i* dest_ptr = (__m256i*)dest;
        for (uint32_t i = 0; i < simd_size; i++, src_ptr++, dest_ptr++)
        {
            // Multiply the src with the constant

            // Load the next 16-bytes of the source buffer
            __m256i ymm0 = _mm256_loadu_si256(src_ptr);
            // Apply mask1 to get the low-half of the data
            __m256i l = _mm256_and_si256(ymm0, mask1);
            // Perform 32 simultaneous table lookups to multiply the low-half
            l = _mm256_shuffle_epi8(table1, l);
            // Apply mask2 to get the high-half of the data
            __m256i h = _mm256_and_si256(ymm0, mask2);
            // Right shift the high-half by 4 bits to get values in [0,15]
            h = _mm256_srli_epi64(h, 4);
            // Perform table lookup with these indices to multiply the high-half
            h = _mm256_shuffle_epi8(table2, h);
            // Xor the high and low halves together to get the final result
            ymm0 = _mm256_xor_si256(h, l);

            // Add this product to the dest

            // Load the next 16-bytes of the destination buffer
            __m256i ymm1 = _mm256_loadu_si256(dest_ptr);
            // Xor the multiplication result and the destination value
            ymm0 = _mm256_xor_si256(ymm0, ymm1);
            // Store the result in the destination buffer
            _mm256_storeu_si256(dest_ptr, ymm0);
        }
    }

    void avx2_binary4_full_table::region_multiply_subtract(value_type* dest,
        const value_type* src, value_type constant, uint32_t length) const
    {
        // In a binary extension field addition is the same as subtraction
        region_multiply_add(dest, src, constant, length);
    }

    uint32_t avx2_binary4_full_table::alignment() const
    {
        return 1U;
    }

    uint32_t avx2_binary4_full_table::max_alignment() const
    {
        return alignment();
    }

    uint32_t avx2_binary4_full_table::granularity() const
    {
        // We are working over 32 bytes at a time i.e. 256 bits so we
        // require a length granularity of 16. We expect that binary4
        // uses uint8_t as value_type
        static_assert(std::is_same<value_type, uint8_t>::value,
            "Here we expect binary4 to use uint8_t as value_type");
        return 32U;
    }

    uint32_t avx2_binary4_full_table::max_granularity() const
    {
        return granularity();
    }

    bool avx2_binary4_full_table::enabled() const
    {
        static cpuid::cpuinfo info;
        return info.has_avx2();
    }

#else

    avx2_binary4_full_table::avx2_binary4_full_table()
    { }

    void avx2_binary4_full_table::region_add(
        value_type*, const value_type*, uint32_t) const
    {
        // Not implemented
        assert(0);
    }

    void avx2_binary4_full_table::region_subtract(
        value_type*, const value_type*, uint32_t) const
    {
        // Not implemented
        assert(0);
    }

    void avx2_binary4_full_table::region_multiply_constant(
        value_type*, value_type, uint32_t) const
    {
        // Not implemented
        assert(0);
    }

    void avx2_binary4_full_table::region_multiply_add(
        value_type*, const value_type*, value_type, uint32_t) const
    {
        // Not implemented
        assert(0);
    }

    void avx2_binary4_full_table::region_multiply_subtract(
        value_type*, const value_type*, value_type, uint32_t) const
    {
        // Not implemented
        assert(0);
    }

    uint32_t avx2_binary4_full_table::alignment() const
    {
        // Not implemented
        assert(0);
        return 0;
    }

    uint32_t avx2_binary4_full_table::max_alignment() const
    {
        // Not implemented
        assert(0);
        return 0;
    }

    uint32_t avx2_binary4_full_table::granularity() const
    {
        // Not implemented
        assert(0);
        return 0;
    }

    uint32_t avx2_binary4_full_table::max_granularity() const
    {
        // Not implemented
        assert(0);
        return 0;
    }

    bool avx2_binary4_full_table::enabled() const
    {
        return false;
    }

#endif

}
