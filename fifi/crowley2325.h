// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#ifndef FIFI_CROWLEY_2325_H
#define FIFI_CROWLEY_2325_H

#include <stdint.h>
#include "field_types.h"

namespace fifi
{

    /// This mapping algorithm was proposed by Cowley et al.
    /// and allows an efficient mapping of arbitarty binary data
    /// to the 2^32 - 5 prime field.
    struct crowley2325
    {
        /// A chunk of data which belongs to a block
        /// A block may consist of serveral chunks, but
        /// the total size should stay below the max_block_size().
        typedef std::pair<uint8_t*, uint32_t> chunk;

        /// @returns the maximum size in bytes a block can be
        uint32_t max_block_size();

        /// Adds a data chunk to the block
        /// @param c
        void add_chunk(const chunk &chunk);

        /// Searches for a unused bit prefix which can be used to
        /// pefrom the sub-field mapping
        /// @return the found prefix
        uint32_t find_prefix();

        /// Vector to keep track of the different chunks of a
        /// specific block.
        std::vector<chunk> m_chunks;

        /// Keeps track of the current block size
        uint64_t m_block_size;
    };

    inline uint32_t crowley2325::max_block_size()
    {
        // 2^29 - 1 data words (where every word is
        // 32 bits).
        return 2147483644U;
    }

    inline void crowley2325::add_chunk(const chunk &c)
    {
        assert(c.second + m_block_size <= max_block_size());

        m_chunks.push_back(c);
        m_block_size += c.second;
    }

    inline uint32_t crowley2325::find_prefix()
    {
        assert(m_chunks.size() > 0);
        assert(m_block_size > 0);

        std::vector<uint8_t> m_prefix;


    }

}

#endif

