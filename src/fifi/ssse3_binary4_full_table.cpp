// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "ssse3_binary4_full_table.hpp"

#include <iostream>
#include <cpuid/config.hpp>

#if defined(CPUID_LINUX_GCC_X86)
    #include <x86intrin.h>
#elif defined(CPUID_LINUX_CLANG_X86)
    #include <x86intrin.h>
#endif

namespace fifi
{

#ifdef __SSSE3__

    ssse3_binary4_full_table::ssse3_binary4_full_table()
        : m_ssse3_size(0)
    {
        m_table_one.resize(16*16);
        m_table_two.resize(16*16);

        assert( ( (uintptr_t)&m_table_one[0] % 16) == 0);
        assert( ( (uintptr_t)&m_table_two[0] % 16) == 0);

        for(uint32_t i = 0; i < 16; ++i)
        {
            for(uint32_t j = 0; j < 16; ++j)
            {
                auto v = base::multiply(i,j);

                m_table_one[i*16 + j] = v & 0x0f;
                m_table_two[i*16 + j] = (v << 4) & 0xf0;
            }
        }
    }

    void ssse3_binary4_full_table::region_multiply_constant(
        value_type* dest, value_type constant) const
    {
        assert(dest != 0);
        assert( ( (uintptr_t)dest % 16) == 0);
        // assert(alignment)

        // The constant is packed, so we need just either the high or
        // low 4 bits to get constant value
        constant = constant & 0xf;

        // Initialize the look-up tables
        __m128i table1 = _mm_load_si128(
            (const __m128i*)(&m_table_one[0] + (constant * 16)));

        __m128i table2 = _mm_load_si128(
            (const __m128i*)(&m_table_two[0] + (constant * 16)));

        __m128i mask1 = _mm_set1_epi8(0x0f);
        __m128i mask2 = _mm_set1_epi8(0xf0);

        for(uint32_t i = 0; i < m_ssse3_size; ++i)
        {
            __m128i xmm0 = _mm_load_si128(((const __m128i*) dest) + i);

            __m128i l = _mm_and_si128(xmm0, mask1);

            l = _mm_shuffle_epi8(table1, l);

            __m128i h = _mm_and_si128(xmm0, mask2);
            h = _mm_srli_epi64(h,4);
            h = _mm_shuffle_epi8(table2, h);

            xmm0 = _mm_xor_si128(h,l);

            _mm_store_si128(((__m128i*)dest) + i, xmm0);
        }

    }

    void ssse3_binary4_full_table::set_length(uint32_t length)
    {
        assert(length > 0);
        assert((length % length_granularity()) == 0);

        // We loop 16 bytes at-a-time so we calculate how many loops we need
        m_ssse3_size = length / length_granularity();
    }

    /// @return The granularity requirements for specifying a length
    uint32_t ssse3_binary4_full_table::length_granularity() const
    {
        // We are working over 16 bytes at a time i.e. 128 bits so we
        // require a length granularity of 16. We expect that binary4
        // uses uint8_t as value_type
        static_assert(std::is_same<value_type, uint8_t>::value,
                      "Here we expect binary4 to use uint8_t as value_type");
        return 16U;
    }

    bool ssse3_binary4_full_table::executable_has_ssse3() const
    {
        return true;
    }

#else

    ssse3_binary4_full_table::ssse3_binary4_full_table()
    { }

    void ssse3_binary4_full_table::region_multiply_constant(
        value_type* /*dest*/, value_type /*constant*/) const
    {
        // Not implemented
        assert(0);
    }

    bool ssse3_binary4_full_table::executable_has_ssse3() const
    {
        return false;
    }


    void ssse3_binary4_full_table::set_length(uint32_t length)
    {
        assert(0);
    }


    uint32_t ssse3_binary4_full_table::length_granularity() const
    {
        assert(0);
        return 0;
    }


#endif

}

