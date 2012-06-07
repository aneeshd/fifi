// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#ifndef FIFI_PRIME_2325_BINARY_SEARCH_H
#define FIFI_PRIME_2325_BINARY_SEARCH_H

#include "field_types.h"
#include <sak/storage.h>

namespace fifi
{

    /// Binary search algorithms for finding an unused bit
    /// prefix in arbitrary binary data. The algorithms can
    /// search for the prefix using k passes. When k = 2 the
    /// algorithms will have to pass over the entire block of
    /// data twice, when k = 3 the algorithms will pass over the
    /// data three times etc. This requires additional time,
    /// however the larger k is the smaller the memory consumption
    /// becomes.
    /// Using the found prefix we may map arbitrary data to
    /// the 2^32 - 5 prime field an approach which was suggested
    /// by Crowley et al.
    struct prime2325_binary_search
    {
        /// The data type used for the bitmap
        typedef uint32_t counter_type;

        /// Create a new prefix bitmap
        ///
        /// @param max_block_size denotes the largest block size in bytes
        ///        that can be searched using this algorithm.
        prime2325_binary_search(uint32_t max_block_length, uint32_t k_pass = 2)
            : m_max_block_length(max_block_length),
              m_max_block_size(m_max_block_length * 4),
              m_k_pass(k_pass)
            {
                assert(m_max_block_length <= prime2325::max_block_length);
                assert(m_max_block_length > 0);
                assert(m_k_pass > 0);

                // log2 of the maximum block size gives us the
                // maximum bit prefix needed
                uint32_t max_prefix_bits =
                    prime2325::prefix_length(m_max_block_length);

                // The number of bits inspected on every pass
                // ceil(x/y) = ((x - 1) / y) + 1
                m_k_pass_bits = ((max_prefix_bits - 1) / k_pass) + 1;

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

                m_shift_prefix = 32 - m_k_pass_bits;


                // We need one bucket with counter possible prefix value we have
                // 2^k_pass_bits possible values
                uint32_t number_of_buckets = 1 << m_k_pass_bits;

                m_buckets.resize(number_of_buckets);
            }

        /// @return the size in bytes needed for the bitmap depending on
        ///         the block length i.e. the number of 32-bit integers
        ///         in the block.
        static uint32_t size_needed(uint32_t block_length)
            {
                assert(block_length > 0);
                assert(block_length <= prime2325::max_block_length);

                uint32_t prefix_bits = prime2325::prefix_length(block_length);

                // ceil(x/y) = ((x - 1) / y) + 1
                uint32_t size_bytes = (((1 << prefix_bits) - 1) / 8) + 1;
                assert(size_bytes > 0);

                return size_bytes;
            }

        /// Finds a returns an unused prefix in the storage sequence
        /// @param sequence a storage sequence @see sak::storage_list
        /// @return an unused prefix
        template<class StorageSequence>
        uint32_t find_prefix(const StorageSequence &sequence)
            {
                return find_prefix(sequence.begin(), sequence.end());
            }

        /// Finds a returns an unused prefix in the storage objects
        /// which conform to the API of sak::mutable_storage or
        /// sak::const_storage
        /// @param first iterator to a storage object
        /// @param last iterator to the last storage object
        /// @return an unused prefix
        template<class StorageIterator>
        uint32_t find_prefix(StorageIterator first, StorageIterator last)
            {
                // @see prime2325::max_block_size()
                uint32_t size = sak::storage_size(first, last);

                assert(size <= m_max_block_size);
                assert(size > 0);

                uint32_t prefix = 0;

                for(uint32_t k = 0; k < m_k_pass; ++k)
                {
                    update_buckets(first, last, k, prefix);
                    update_prefix(k, &prefix);
                }

                return prefix;
            }

        /// Iterates through the bitmap looking for the unused prefix
        /// @param prefix will contain the unused prefix
        /// @return returns true if the prefix was found otherwise false
        void update_prefix(uint32_t k, uint32_t *prefix) const
            {

                uint32_t shift_prefix = 32 - m_k_pass_bits - k * m_k_pass_bits;
                uint32_t min_index = 0;

                for(uint32_t i = 1; i < m_buckets.size(); ++i)
                {
                    if(m_buckets[i] < m_buckets[min_index])
                    {
                        min_index = i;
                    }
                }

                *prefix = *prefix | (min_index << shift_prefix);

            }

        template<class StorageIterator>
        void update_buckets(StorageIterator first, StorageIterator last,
                            uint32_t k, uint32_t prefix)
            {
                assert((m_k_pass_bits + k*m_k_pass_bits) < 32);

                // Empty buckets
                std::fill(m_buckets.begin(), m_buckets.end(), 0);

                // Example m_k_pass_bits = 4
                // For k = 0, shift_prefix = 28
                // For k = 1, shift_prefix = 24
                // For k = 2, shift_prefix = 20
                // Etc.
                uint32_t shift_prefix = 32 - m_k_pass_bits - k * m_k_pass_bits;

                // Since we only look at m_k_pass_bits at-a-time we need to zero
                // everything else after shifting the prefix down
                // I.e. so we get 00000....0001111 if m_k_pass_bits = 4
                uint32_t shift_mask = ~(~0U << m_k_pass_bits);

                // We only look at values that match our already found
                // prefix, this mask
                // For k = 0, mask = 00000000000...0000000000
                // For k = 1, mask = 11110000000...0000000000
                // For k = 2, maks = 11111111000...0000000000
                // Etc.
                uint32_t prefix_mask = ~(~0U >> (k*m_k_pass_bits));

                while(first != last)
                {
                    // Size must be multiple of 4 bytes due to the field
                    // 2^32 - 5
                    assert((first->m_size % 4) == 0);

                    uint32_t block_size = first->m_size / 4;
                    const uint32_t *block_data =
                        sak::cast_storage<uint32_t>(*first);

                    for(uint32_t i = 0; i < block_size; ++i)
                    {
                        // We only count for values which match the already
                        // found prefix
                        if((block_data[i] & prefix_mask) == prefix)
                        {
                            uint32_t bucket_index =
                                (block_data[i] >> shift_prefix) & shift_mask;

                            assert(bucket_index < m_buckets.size());

                            ++m_buckets[bucket_index];
                        }
                    }

                    ++first;
                }
            }

        /// The maximum block length in elements of uint32_t
        uint32_t m_max_block_length;

        /// The maximum block size in bytes
        uint32_t m_max_block_size;

        /// The bits in the
        uint32_t m_mapping_bits;

        /// The number of passes over the data
        uint32_t m_k_pass;

        /// The bits inspected for every pass
        uint32_t m_k_pass_bits;

        /// The amount we need to shift the prefix
        uint32_t m_shift_prefix;

        /// The bitmap storing info about whether a
        /// specific prefix has been found
        std::vector<counter_type> m_buckets;

    };

}

#endif


