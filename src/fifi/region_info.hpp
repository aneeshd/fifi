// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include "fifi_utils.hpp"

#include <cstdint>
#include <cassert>

namespace fifi
{

    /// Layer store information about the size the memory regions over
    /// which we wish to perform finite field arithmetic.
    ///
    /// The API allows us to specify the size of the region in length,
    /// size or elements. These are defined as follows:
    ///
    /// Length: Corresponds to the number value_type elements defined
    /// in the chosen field
    ///
    /// Size: Corresponds to the memory region's size in bytes
    ///
    /// Elements: Corresponds to the number of finite field elements
    /// in the region
    ///
    /// Examples:
    ///
    /// binary uses a uint8_t as value_type setting the length equal
    /// to 4 is means we will have a size of 4 and 32 elements (since
    /// each element is one bit).
    ///
    /// binary8 uses an uint8_t as value_type setting length equal to
    /// 2 means we have a size of 2 and 2 elements
    ///
    /// binary16 uses an uint16_t as value_type setting length equal
    /// to 5 means we have a size of 10 and 5 elements.
    ///
    /// and so forth..
    template<class Field, class Super>
    class region_info : public Super
    {
    public:

        /// The field type
        typedef typename Super::field_type field_type;

        /// @copydoc layer::value_type
        typedef typename field_type::value_type value_type;

    public:

        /// Constructor
        region_info()
            : m_length(0),
              m_size(0),
              m_elements(0)
        { }

        /// Sets the length in the chosen field's value_type.
        /// @param length denotes the new length
        void set_length(uint32_t length)
        {
            assert(length > 0);
            assert((length % length_granularity()) == 0);

            m_length = length;
            m_size = length_to_size<field_type>(length);
            m_elements = length_to_elements<field_type>(length);
        }

        /// Gets the length i.e. the number of elements
        uint32_t length() const
        {
            assert(m_length > 0);
            return m_length;
        }

        /// Gets the size in of the elements in bytes
        uint32_t size() const
        {
            assert(m_size > 0);
            return m_size;
        }

        /// Gets the number of elements
        uint32_t elements() const
        {
            assert(m_elements > 0);
            return m_elements;
        }

        /// @return The granularity requirements for specifying a length
        uint32_t length_granularity() const
        {
            return 1U;
        }

    private:

        /// The length in Field elements
        uint32_t m_length;

        /// The size in bytes
        uint32_t m_size;

        /// The number of finite field elements
        uint32_t m_elements;

    };
}
