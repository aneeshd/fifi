// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <iostream>

#include <platform/config.hpp>
#include <cpuid/cpuinfo.hpp>

// Include x86 intrinsics for GCC-compatible compilers on x86/x86_64
#if defined(PLATFORM_GCC_COMPATIBLE_X86)
    #include <x86intrin.h>
#endif

#include "ssse3_binary8_full_table.hpp"

namespace fifi
{

#ifdef PLATFORM_SSSE3

    ssse3_binary8_full_table::ssse3_binary8_full_table()
    {
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
                auto v1 = base::multiply(i, j);
                m_table_one[i * 16 + j] = v1;
                // Calculate 8-bit product with the high-half
                auto v2 = base::multiply(i, j << 4);
                m_table_two[i * 16 + j] = v2;
            }
        }
    }

    void ssse3_binary8_full_table::region_add(value_type* dest,
        const value_type* src, uint32_t length) const
    {
        assert(dest != 0);
        assert(src != 0);
        //assert(((uintptr_t) dest % alignment()) == 0);
        //assert(((uintptr_t) src % alignment()) == 0);
        assert(length > 0);
        assert((length % granularity()) == 0);

        // We loop 16 bytes at-a-time so we calculate how many loops we need
        uint32_t ssse3_size = length / granularity();
        assert(ssse3_size > 0);

        __m128i* src_ptr = (__m128i*)src;
        __m128i* dest_ptr = (__m128i*)dest;
        for (uint32_t i = 0; i < ssse3_size; i++, src_ptr++, dest_ptr++)
        {
            // Load the next 16-bytes of the destination and source buffers
            __m128i xmm0 = _mm_loadu_si128(dest_ptr);
            __m128i xmm1 = _mm_loadu_si128(src_ptr);
            // Xor these values together
            xmm0 = _mm_xor_si128(xmm0, xmm1);
            // Store the result in the destination buffer
            _mm_storeu_si128(dest_ptr, xmm0);
        }
    }

    void ssse3_binary8_full_table::region_subtract(value_type* dest,
        const value_type* src, uint32_t length) const
    {
        // In a binary extension field addition is the same as subtraction
        region_add(dest, src, length);
    }

    void ssse3_binary8_full_table::region_multiply(value_type* dest,
        const value_type* src, uint32_t length) const
    {
        (void) dest;
        (void) src;
        (void) length;

        // Not implemented
        assert(0);
    }

    void ssse3_binary8_full_table::region_divide(value_type* dest,
        const value_type* src, uint32_t length) const
    {
        (void) dest;
        (void) src;
        (void) length;

        // Not implemented
        assert(0);
    }

    void ssse3_binary8_full_table::region_multiply_constant(
        value_type* dest, value_type constant, uint32_t length) const
    {
        assert(dest != 0);
        //assert(((uintptr_t) dest % alignment()) == 0);
        assert(length > 0);
        assert((length % granularity()) == 0);
        // assert(alignment)

        // We loop 16 bytes at-a-time so we calculate how many loops we need
        uint32_t ssse3_size = length / granularity();
        assert(ssse3_size > 0);

        // Initialize the look-up tables
        // Load the 16-byte row that contains pre-calculated multiplication
        // results with the constant
        __m128i table1 = _mm_load_si128(
            (const __m128i*)(&m_table_one[0] + (constant * 16)));

        // table2 contains the same results shifted left by 4 bits
        __m128i table2 = _mm_load_si128(
            (const __m128i*)(&m_table_two[0] + (constant * 16)));

        // Create low and high bitmasks by replicating the mask values 16 times
        __m128i mask1 = _mm_set1_epi8((char)0x0f);
        __m128i mask2 = _mm_set1_epi8((char)0xf0);

        __m128i* dest_ptr = (__m128i*)dest;
        for (uint32_t i = 0; i < ssse3_size; i++, dest_ptr++)
        {
            // Load the next 16-bytes of the destination buffer
            __m128i xmm0 = _mm_loadu_si128(dest_ptr);
            // Apply mask1 to get the low-half of the data
            __m128i l = _mm_and_si128(xmm0, mask1);
            // Perform 16 simultaneous table lookups to multiply the low-half
            l = _mm_shuffle_epi8(table1, l);
            // Apply mask2 to get the high-half of the data
            __m128i h = _mm_and_si128(xmm0, mask2);
            // Right shift the high-half by 4 bits to get values in [0,15]
            h = _mm_srli_epi64(h, 4);
            // Perform table lookup with these indices to multiply the high-half
            h = _mm_shuffle_epi8(table2, h);
            // Xor the high and low halves together to get the final result
            xmm0 = _mm_xor_si128(h, l);
            // Store the result in the destination buffer
            _mm_storeu_si128(dest_ptr, xmm0);
        }
    }

    void ssse3_binary8_full_table::region_multiply_add(value_type* dest,
        const value_type* src, value_type constant, uint32_t length) const
    {
        assert(dest != 0);
        assert(src != 0);
        //assert(((uintptr_t) dest % alignment()) == 0);
        //assert(((uintptr_t) src % alignment()) == 0);
        assert(length > 0);
        assert((length % granularity()) == 0);

        // We loop 16 bytes at-a-time so we calculate how many loops we need
        uint32_t ssse3_size = length / granularity();
        assert(ssse3_size > 0);

        // Initialize the look-up tables
        // Load the 16-byte row that contains pre-calculated multiplication
        // results with the constant
        __m128i table1 = _mm_load_si128(
            (const __m128i*)(&m_table_one[0] + (constant * 16)));

        // table2 contains the same results shifted left by 4 bits
        __m128i table2 = _mm_load_si128(
            (const __m128i*)(&m_table_two[0] + (constant * 16)));

        // Create low and high bitmasks by replicating the mask values 16 times
        __m128i mask1 = _mm_set1_epi8((char)0x0f);
        __m128i mask2 = _mm_set1_epi8((char)0xf0);

        __m128i* src_ptr = (__m128i*)src;
        __m128i* dest_ptr = (__m128i*)dest;
        for (uint32_t i = 0; i < ssse3_size; i++, src_ptr++, dest_ptr++)
        {
            // Multiply the src with the constant

            // Load the next 16-bytes of the source buffer
            __m128i xmm0 = _mm_loadu_si128(src_ptr);
            // Apply mask1 to get the low-half of the data
            __m128i l = _mm_and_si128(xmm0, mask1);
            // Perform 16 simultaneous table lookups to multiply the low-half
            l = _mm_shuffle_epi8(table1, l);
            // Apply mask2 to get the high-half of the data
            __m128i h = _mm_and_si128(xmm0, mask2);
            // Right shift the high-half by 4 bits to get values in [0,15]
            h = _mm_srli_epi64(h, 4);
            // Perform table lookup with these indices to multiply the high-half
            h = _mm_shuffle_epi8(table2, h);
            // Xor the high and low halves together to get the final result
            xmm0 = _mm_xor_si128(h, l);

            // Add the src to the dest

            // Load the next 16-bytes of the destination buffer
            __m128i xmm1 = _mm_loadu_si128(dest_ptr);
            // Xor the multiplication result and the destination value
            xmm0 = _mm_xor_si128(xmm0, xmm1);
            // Store the result in the destination buffer
            _mm_storeu_si128(dest_ptr, xmm0);
        }
    }

    void ssse3_binary8_full_table::region_multiply_subtract(value_type* dest,
        const value_type* src, value_type constant, uint32_t length) const
    {
        // In a binary extension field addition is the same as subtraction
        region_multiply_add(dest, src, constant, length);
    }


    uint32_t ssse3_binary8_full_table::alignment()
    {
        // SSSE3 require 16 byte alignment data
        return 16U;
    }

    uint32_t ssse3_binary8_full_table::max_alignment()
    {
        return alignment();
    }

    uint32_t ssse3_binary8_full_table::granularity()
    {
        // We are working over 16 bytes at a time i.e. 128 bits so we
        // require a length granularity of 16. We expect that binary4
        // uses uint8_t as value_type
        static_assert(std::is_same<value_type, uint8_t>::value,
                      "Here we expect binary4 to use uint8_t as value_type");
        return 16U;
    }

    uint32_t ssse3_binary8_full_table::max_granularity()
    {
        return granularity();
    }

    bool ssse3_binary8_full_table::enabled()
    {
        static cpuid::cpuinfo info;
        return info.has_ssse3();
    }

#else

    ssse3_binary8_full_table::ssse3_binary8_full_table()
    { }

    void ssse3_binary8_full_table::region_add(value_type* dest,
        const value_type* src, uint32_t length) const
    {
        (void) dest;
        (void) src;
        (void) length;

        // Not implemented
        assert(0);
    }

    void ssse3_binary8_full_table::region_subtract(value_type* dest,
        const value_type* src, uint32_t length) const
    {
        (void) dest;
        (void) src;
        (void) length;

        // Not implemented
        assert(0);
    }

    void ssse3_binary8_full_table::region_multiply(value_type* dest,
        const value_type* src, uint32_t length) const
    {
        (void) dest;
        (void) src;
        (void) length;

        // Not implemented
        assert(0);
    }

    void ssse3_binary8_full_table::region_divide(value_type* dest,
        const value_type* src, uint32_t length) const
    {
        (void) dest;
        (void) src;
        (void) length;

        // Not implemented
        assert(0);
    }

    void ssse3_binary8_full_table::region_multiply_constant(
        value_type* dest, value_type constant, uint32_t length) const
    {
        (void) dest;
        (void) constant;
        (void) length;

        // Not implemented
        assert(0);
    }

    void ssse3_binary8_full_table::region_multiply_add(value_type* dest,
        const value_type* src, value_type constant, uint32_t length) const
    {
        (void) dest;
        (void) src;
        (void) constant;
        (void) length;

        // Not implemented
        assert(0);
    }

    void ssse3_binary8_full_table::region_multiply_subtract(value_type* dest,
        const value_type* src, value_type constant, uint32_t length) const
    {
        (void) dest;
        (void) src;
        (void) constant;
        (void) length;

        // Not implemented
        assert(0);
    }

    uint32_t ssse3_binary8_full_table::alignment()
    {
        // Not implemented
        assert(0);
        return 0;
    }

    uint32_t ssse3_binary8_full_table::max_alignment()
    {
        // Not implemented
        assert(0);
        return 0;
    }

    uint32_t ssse3_binary8_full_table::granularity()
    {
        // Not implemented
        assert(0);
        return 0;
    }

    uint32_t ssse3_binary8_full_table::max_granularity()
    {
        // Not implemented
        assert(0);
        return 0;
    }

    bool ssse3_binary8_full_table::enabled()
    {
        return false;
    }

#endif

}
