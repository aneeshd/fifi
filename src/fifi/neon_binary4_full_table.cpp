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

#include "neon_binary4_full_table.hpp"

namespace fifi
{

#ifdef PLATFORM_NEON

    neon_binary4_full_table::neon_binary4_full_table()
    {
        simple_online_arithmetic<final<binary4>> field;

        m_table_one.resize(16 * 16);
        m_table_two.resize(16 * 16);

        assert(((uintptr_t) &m_table_one[0] % 16) == 0);
        assert(((uintptr_t) &m_table_two[0] % 16) == 0);

        // Iterate over all elements in the field
        for (uint32_t i = 0; i < 16; ++i)
        {
            for (uint32_t j = 0; j < 16; ++j)
            {
                auto v = field.multiply(i, j);

                // Store the 8-bit product in the low-half table
                m_table_one[i * 16 + j] = v & 0x0f;
                // Store the shifted 8-bit product in the high-half table
                m_table_two[i * 16 + j] = (v << 4) & 0xf0;
            }
        }
    }

    void neon_binary4_full_table::region_add(
        value_type* dest, const value_type* src, uint32_t length) const
    {
        assert(dest != 0);
        assert(src != 0);
        assert(length > 0);
        assert((length % granularity()) == 0);

        // We loop 16 bytes at-a-time so we calculate how many loops we need
        uint32_t simd_size = length / granularity();
        assert(simd_size > 0);

        uint8_t* src_ptr = (uint8_t*)src;
        uint8_t* dest_ptr = (uint8_t*)dest;
        for (uint32_t i = 0; i < simd_size; i++, src_ptr+=16, dest_ptr+=16)
        {
            // Load the next 16-bytes of the destination and source buffers
            uint8x16_t q0 = vld1q_u8(dest_ptr);
            uint8x16_t q1 = vld1q_u8(src_ptr);
            // Xor these values together
            uint8x16_t result = veorq_u8(q0, q1);
            // Store the result in the destination buffer
            vst1q_u8(dest_ptr, result);
        }
    }

    void neon_binary4_full_table::region_subtract(
        value_type* dest, const value_type* src, uint32_t length) const
    {
        // In a binary extension field addition is the same as subtraction
        region_add(dest, src, length);
    }

    void neon_binary4_full_table::region_multiply_constant(
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
        // Load the 16-byte row that contains pre-calculated multiplication
        // results with the low-half of the constant
        // Convert to uint8x8x2_t as vtbl2_u8 expects two 8-byte arrays
        uint8x16_t t1 = vld1q_u8(&m_table_one[0] + constant * 16);
        uint8x8x2_t table1 = {{ vget_low_u8(t1), vget_high_u8(t1) }};

        // table2 contains the results with the high-half of the constant
        uint8x16_t t2 = vld1q_u8(&m_table_two[0] + constant * 16);
        uint8x8x2_t table2 = {{ vget_low_u8(t2), vget_high_u8(t2) }};

        // Create low and high bitmasks by replicating the mask values 16 times
        uint8x16_t mask1 = vdupq_n_u8((uint8_t)0x0f);
        uint8x16_t mask2 = vdupq_n_u8((uint8_t)0xf0);

        uint8_t* dest_ptr = (uint8_t*)dest;
        for (uint32_t i = 0; i < simd_size; i++, dest_ptr+=16)
        {
            // Load the next 16-bytes of the destination buffer
            uint8x16_t q0 = vld1q_u8(dest_ptr);
            // Apply mask1 to get the low-half of the data
            uint8x16_t l = vandq_u8(q0, mask1);
            // Perform 8 simultaneous table lookups to multiply the low-half
            // The lookup is performed twice due to NEON restrictions
            l = vcombine_u8(vtbl2_u8(table1, vget_low_u8(l)),
                vtbl2_u8(table1, vget_high_u8(l)));
            // Apply mask2 to get the high-half of the data
            uint8x16_t h = vandq_u8(q0, mask2);
            // Right shift the high-half by 4 bits to get values in [0,15]
            h = vshrq_n_u8(h, 4);
            // Perform table lookup with these indices to multiply the high-half
            // The lookup is performed twice due to NEON restrictions
            h = vcombine_u8(vtbl2_u8(table2, vget_low_u8(h)),
                vtbl2_u8(table2, vget_high_u8(h)));
            // Xor the high and low halves together to get the final result
            uint8x16_t result = veorq_u8(h, l);
            // Store the result in the destination buffer
            vst1q_u8(dest_ptr, result);
        }
    }

    void neon_binary4_full_table::region_multiply_add(value_type* dest,
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
        // Load the 16-byte row that contains pre-calculated multiplication
        // results with the low-half of the constant
        // Convert to uint8x8x2_t as vtbl2_u8 expects two 8-byte arrays
        uint8x16_t t1 = vld1q_u8(&m_table_one[0] + constant * 16);
        uint8x8x2_t table1 = {{ vget_low_u8(t1), vget_high_u8(t1) }};

        // table2 contains the results with the high-half of the constant
        uint8x16_t t2 = vld1q_u8(&m_table_two[0] + constant * 16);
        uint8x8x2_t table2 = {{ vget_low_u8(t2), vget_high_u8(t2) }};

        // Create low and high bitmasks by replicating the mask values 16 times
        uint8x16_t mask1 = vdupq_n_u8((uint8_t)0x0f);
        uint8x16_t mask2 = vdupq_n_u8((uint8_t)0xf0);

        uint8_t* src_ptr = (uint8_t*)src;
        uint8_t* dest_ptr = (uint8_t*)dest;
        for (uint32_t i = 0; i < simd_size; i++, src_ptr+=16, dest_ptr+=16)
        {
            // Load the next 16-bytes of the destination buffer
            uint8x16_t q0 = vld1q_u8(src_ptr);
            // Apply mask1 to get the low-half of the data
            uint8x16_t l = vandq_u8(q0, mask1);
            // Perform 8 simultaneous table lookups to multiply the low-half
            // The lookup is performed twice due to NEON restrictions
            l = vcombine_u8(vtbl2_u8(table1, vget_low_u8(l)),
                vtbl2_u8(table1, vget_high_u8(l)));
            // Apply mask2 to get the high-half of the data
            uint8x16_t h = vandq_u8(q0, mask2);
            // Right shift the high-half by 4 bits to get values in [0,15]
            h = vshrq_n_u8(h, 4);
            // Perform table lookup with these indices to multiply the high-half
            // The lookup is performed twice due to NEON restrictions
            h = vcombine_u8(vtbl2_u8(table2, vget_low_u8(h)),
                vtbl2_u8(table2, vget_high_u8(h)));
            // Xor the high and low halves together to get the final result
            uint8x16_t result = veorq_u8(h, l);

            // Add this product to the dest

            // Load the next 16-bytes of the destination buffer
            uint8x16_t q1 = vld1q_u8(dest_ptr);
            // Xor the multiplication result and the destination value
            result = veorq_u8(result, q1);
            // Store the result in the destination buffer
            vst1q_u8(dest_ptr, result);
        }
    }

    void neon_binary4_full_table::region_multiply_subtract(value_type* dest,
        const value_type* src, value_type constant, uint32_t length) const
    {
        // In a binary extension field addition is the same as subtraction
        region_multiply_add(dest, src, constant, length);
    }

    uint32_t neon_binary4_full_table::alignment() const
    {
        return 1U;
    }

    uint32_t neon_binary4_full_table::max_alignment() const
    {
        return alignment();
    }

    uint32_t neon_binary4_full_table::granularity() const
    {
        // We are working over 16 bytes (128 bits) at a time, so we
        // require a length granularity of 16. We expect that binary4
        // uses uint8_t as value_type
        static_assert(std::is_same<value_type, uint8_t>::value,
            "Here we expect binary4 to use uint8_t as value_type");
        return 16U;
    }

    uint32_t neon_binary4_full_table::max_granularity() const
    {
        return granularity();
    }

    bool neon_binary4_full_table::enabled() const
    {
        static cpuid::cpuinfo info;
        return info.has_neon();
    }

#else

    neon_binary4_full_table::neon_binary4_full_table()
    { }

    void neon_binary4_full_table::region_add(
        value_type*, const value_type*, uint32_t) const
    {
        // Not implemented
        assert(0);
    }

    void neon_binary4_full_table::region_subtract(
        value_type*, const value_type*, uint32_t) const
    {
        // Not implemented
        assert(0);
    }

    void neon_binary4_full_table::region_multiply_constant(
        value_type*, value_type, uint32_t) const
    {
        // Not implemented
        assert(0);
    }

    void neon_binary4_full_table::region_multiply_add(
        value_type*, const value_type*, value_type, uint32_t) const
    {
        // Not implemented
        assert(0);
    }

    void neon_binary4_full_table::region_multiply_subtract(
        value_type*, const value_type*, value_type, uint32_t) const
    {
        // Not implemented
        assert(0);
    }

    uint32_t neon_binary4_full_table::alignment() const
    {
        // Not implemented
        assert(0);
        return 0;
    }

    uint32_t neon_binary4_full_table::max_alignment() const
    {
        // Not implemented
        assert(0);
        return 0;
    }

    uint32_t neon_binary4_full_table::granularity() const
    {
        // Not implemented
        assert(0);
        return 0;
    }

    uint32_t neon_binary4_full_table::max_granularity() const
    {
        // Not implemented
        assert(0);
        return 0;
    }

    bool neon_binary4_full_table::enabled() const
    {
        return false;
    }

#endif

}
