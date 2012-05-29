// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/optimal_prime.h>
#include <fifi/field_types.h>
#include <fifi/crowley2325.h>

#include <sak/storage.h>

#include <cmath>
#include <stdexcept>


/// Bitmap algorithm for finding the an unused bit prefix
/// within a block of data.
struct prefix2325_bitmap
{
    /// The data type used for the bitmap
    typedef uint32_t mapping_type;

    /// Create a new prefix bitmap
    ///
    /// @param max_block_size denotes the largest block size in bytes
    ///        that can be searched using this algorithm.
    prefix2325_bitmap(uint32_t max_block_length)
        : m_max_block_length(max_block_length)
        {
            assert(m_max_block_length <= fifi::crowley2325::max_block_length());

            // log2 of the maximum block size gives us the
            // maximum bit prefix needed
            m_max_prefix_bits = fifi::crowley2325::prefix_length(m_max_block_length);

            // The amount we have to shift the prefix to get the prefix
            // value:
            //
            // | b31 b30 b29 b28 b27  ... b1 b0 |
            //    ^               ^
            //    '-   prefix    -'
            //          value
            //
            // In the above example we have 5 prefix bits so
            // we need to shift it down 32 - 5 = 27 bits to get
            // the numeric prefix value

            m_shift_prefix = 32 - m_max_prefix_bits;

            // The number of bits in the mapping type
            m_mapping_bits = std::numeric_limits<mapping_type>::digits;

            // We need one bit per possible prefix value we have
            // 2^m_max_prefix_bits possible values
            uint32_t prefix_values = 2 << m_max_prefix_bits;

            // ceil(x/y) = ((x - 1) / y) + 1
            uint32_t bitmap_size = ((prefix_values - 1) / m_mapping_bits) + 1;
            m_bitmap.resize(bitmap_size);
        }

    /// @return the size in bytes needed for the bitmap depending on
    ///         the block length i.e. the number of 32-bit integers
    ///         in the block.
    static uint32_t size_needed(uint32_t block_length)
        {
            assert(block_length > 0);

            uint32_t prefix_bits = fifi::crowley2325::prefix_length(block_length);

            // ceil(x/y) = ((x - 1) / y) + 1
            uint32_t size_bytes = (((2 << prefix_bits) - 1) / 8) + 1;
            assert(size_bytes > 0);

            return size_bytes;
        }

    template<class StorageSequence>
    uint32_t find_prefix(const StorageSequence &sequence)
        {
            return find_prefix(sequence.begin(), sequence.end());
        }

    template<class StorageIterator>
    uint32_t find_prefix(StorageIterator first, StorageIterator last)
        {
            // @see crowley2325::max_block_size()
            assert(sak::storage_size(first, last) <= fifi::crowley2325::max_block_size());

            std::fill(m_bitmap.begin(), m_bitmap.end(), 0);

            // Update the bitmap
            while(first != last)
            {
                // Size must be multiple of 4 bytes due to the field
                // 2^32 - 5
                assert((first->m_size % 4) == 0);

                uint32_t block_size = first->m_size / 4;
                const uint32_t *block_data = sak::cast_storage<uint32_t>(*first);

                for(uint32_t i = 0; i < block_size; ++i)
                {
                    update_bitmap(block_data[i]);
                }

                ++first;
            }

            uint32_t prefix = 0;

            if(!find_in_bitmap(&prefix))
            {
                throw std::runtime_error("No prefix found");
            }

            return prefix;

        }


    bool find_in_bitmap(uint32_t *prefix) const
        {
            // Find the missing prefix in the bitmap
            for(uint32_t i = 0; i < m_bitmap.size(); ++i)
            {
                for(uint32_t j = 0; j < m_mapping_bits; ++j)
                {
                    if((m_bitmap[i] & (1 << j)) == 0)
                    {
                        *prefix = (i*m_mapping_bits + j) << m_shift_prefix;
                        return true;
                    }
                }
            }

            return false;
        }

    void update_bitmap(uint32_t value)
        {
            // We use a 32 bit data type for the base value
            uint32_t prefix_value = value >> m_shift_prefix;
            std::cout << "shift_prefix " << m_shift_prefix << std::endl;
            std::cout << "prefix_value " << prefix_value << std::endl;

            uint32_t index = prefix_value / m_mapping_bits;
            uint32_t offset = prefix_value % m_mapping_bits;

            m_bitmap[index] = m_bitmap[index] | 1 << offset;
        }

    /// The maximum block length
    uint32_t m_max_block_length;

    /// The maximum length of the prefix in bits
    uint32_t m_max_prefix_bits;

    /// The bits in the
    uint32_t m_mapping_bits;

    /// The length of the prefix in bits
    uint32_t m_prefix_bits;

    /// The amount we need to shift the prefix
    uint32_t m_shift_prefix;

    /// The bitmap storing info about whether a
    /// specific prefix has been found
    std::vector<mapping_type> m_bitmap;

};


TEST(test_crowley2325, max_block_size)
{
    fifi::crowley2325 mapping;

    EXPECT_EQ(mapping.max_block_size(), 2147483640U);

}

void print_bits(uint32_t v)
{
    for(uint32_t i = 32; i--> 0;)
    {
        std::cout << (v >> i & 0x1) << " ";
    }
    std::cout << std::endl;
}

TEST(test_crowley2325, prefix_length)
{
    // 2^y => 1 << y

    EXPECT_EQ(fifi::crowley2325::prefix_length((1 << 1) - 1), 2U);
    EXPECT_EQ(fifi::crowley2325::prefix_length(1 << 1), 2U);
    EXPECT_EQ(fifi::crowley2325::prefix_length((1 << 1) + 1), 3U);

    EXPECT_EQ(fifi::crowley2325::prefix_length((1 << 2) - 1), 3U);
    EXPECT_EQ(fifi::crowley2325::prefix_length(1 << 2), 3U);
    EXPECT_EQ(fifi::crowley2325::prefix_length((1 << 2) + 1), 3U);

    EXPECT_EQ(fifi::crowley2325::prefix_length((1 << 9) - 2), 9U);
    EXPECT_EQ(fifi::crowley2325::prefix_length((1 << 9) - 1), 10U);
    EXPECT_EQ(fifi::crowley2325::prefix_length(1 << 9), 10U);
    EXPECT_EQ(fifi::crowley2325::prefix_length((1 << 9) + 1), 10U);
    EXPECT_EQ(fifi::crowley2325::prefix_length((1 << 10) - 2), 10U);
    EXPECT_EQ(fifi::crowley2325::prefix_length((1 << 10) - 1), 11U);
    EXPECT_EQ(fifi::crowley2325::prefix_length(1 << 10), 11U);
    EXPECT_EQ(fifi::crowley2325::prefix_length((1 << 10) + 1), 11U);

    // 2^29 - 2 is the maximum block length we support
    EXPECT_EQ(fifi::crowley2325::prefix_length((1 << 29) - 2), 29U);
}


TEST(test_crowley2325, find_prefix)
{
    uint32_t block_size = 254;
    std::vector<uint32_t> data(block_size);

    for(uint32_t i = 0; i < block_size; ++i)
    {
        data[i] = i << 24;
    }

    prefix2325_bitmap p(block_size);

    uint32_t prefix = p.find_prefix(sak::storage_list(data));

    for(uint32_t i = 0; i < data.size(); ++i)
    {
        print_bits(data[i]);
    }

    std::cout << std::endl << "Bitmap: " << std::endl;

    for(uint32_t i = 0; i < p.m_bitmap.size(); ++i)
    {
        print_bits(p.m_bitmap[i]);
    }

    std::cout << std::endl << "Prefix: " << std::endl;
    print_bits(prefix);
}

// 2^31 - 1 is also good
// 0111 1111 1111 1111 1111 1111 1111 1111
//
//
// a, b and a xor b
//
// 1000 0001 1001
// 0000 0001


