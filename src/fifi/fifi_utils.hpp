// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <limits>
#include <sak/ceil_division.hpp>

#include "binary.hpp"
#include "binary4.hpp"
#include "is_valid_element.hpp"

namespace fifi
{
    /// Returns the number of value_type elements needed to store a certain
    /// number of field elements
    /// @param elements the number of field elements
    /// @return the number of value_type elements needed
    template<class Field>
    inline uint32_t elements_to_length(uint32_t elements)
    {
        assert(elements > 0);

        return elements;
    }

    /// elements_to_length specialization for the binary field
    /// @copydoc elements_to_length(uint32_t)
    template<>
    inline uint32_t elements_to_length<binary>(uint32_t elements)
    {
        assert(elements > 0);

        return sak::ceil_division(
            elements, std::numeric_limits<binary::value_type>::digits);
    }

    /// elements_to_length specialization for the binary4 field
    /// @copydoc elements_to_length(uint32_t)
    template<>
    inline uint32_t elements_to_length<binary4>(uint32_t elements)
    {
        assert(elements > 0);

        return sak::ceil_division(elements, 2);
    }

    /// Returns the minimum size in bytes required to accommodate a certain
    /// number of field elements
    /// @param elements the number of field elements
    /// @return the size in bytes needed to store the field elements
    template<class Field>
    inline uint32_t elements_to_size(uint32_t elements)
    {
        assert(elements > 0);

        auto length = elements_to_length<Field>(elements);
        auto bytes_per_value = sizeof(typename Field::value_type);

        return length * bytes_per_value;
    }

    /// Returns the number of value_type elements needed to store
    /// a certain number of bytes
    /// @param bytes the number of bytes to store
    /// @return the number of value_type elements that need to be stored
    template<class Field>
    inline uint32_t size_to_length(uint32_t bytes)
    {
        assert(bytes > 0);

        uint32_t bytes_per_value = sizeof(typename Field::value_type);

        // Make sure that the number of bytes is a multiple of element size
        assert( (bytes % bytes_per_value) == 0);
        return bytes / bytes_per_value;
    }

    /// Returns the size in bytes needed to store a certain
    /// number of value_type elements
    /// @param length the number of value_type elements to store
    /// @return the size in bytes needed to store the value_type elements
    template<class Field>
    inline uint32_t length_to_size(uint32_t length)
    {
        assert(length > 0);

        return length * sizeof(typename Field::value_type);
    }

    /// length_to_size specialization for the binary field
    /// @copydoc length_to_size(uint32_t)
    template<>
    inline uint32_t length_to_size<binary>(uint32_t length)
    {
        assert(length > 0);

        return sak::ceil_division(
            length, std::numeric_limits<binary::value_type>::digits);
    }

    /// length_to_size specialization for the binary4 field
    /// @copydoc length_to_size(uint32_t)
    template<>
    inline uint32_t length_to_size<binary4>(uint32_t length)
    {
        assert(length > 0);

        return sak::ceil_division(length, 2);
    }

    /// Returns the number of field elements needed to store a certain
    /// number of value_type elements
    /// @param length the number of value_type elements
    /// @return the number of field elements needed
    template<class Field>
    inline uint32_t length_to_elements(uint32_t length)
    {
        assert(length > 0);

        return length;
    }

    /// length_to_elements specialization for the binary field
    /// @copydoc length_to_elements(uint32_t)
    template<>
    inline uint32_t length_to_elements<binary>(uint32_t length)
    {
        assert(length > 0);

        return length*std::numeric_limits<binary::value_type>::digits;
    }

    /// length_to_elements specialization for the binary4 field
    /// @copydoc length_to_elements(uint32_t)
    template<>
    inline uint32_t length_to_elements<binary4>(uint32_t length)
    {
        assert(length > 0);

        return length*2;
    }

    /// Returns the number of field elements that can fit within a certain
    /// number of bytes
    /// @param bytes the number of bytes to store the field elements
    /// @return the number of field elements stored within the bytes
    template<class Field>
    inline uint32_t size_to_elements(uint32_t bytes)
    {
        assert(bytes > 0);

        //return size_to_length<Field>(bytes);
        return length_to_elements<Field>((size_to_length<Field>(bytes)));
    }

    /// Useful abstraction functions for accessing field elements in a buffer
    /// Note this function assumes that values are packed.
    /// @param elements elements to get value from
    /// @param index index of element to access in the packed buffer
    /// @return the value of the element at specified index
    template<class Field>
    inline typename Field::value_type
    get_value(const typename Field::value_type *elements, uint32_t index)
    {
        assert(elements != 0);
        return elements[index];
    }

    /// get_value specialization for the binary field
    /// @copydoc get_value(value_type*, uint32_t)
    template<>
    inline binary::value_type
    get_value<binary>(const binary::value_type *elements, uint32_t index)
    {
        assert(elements != 0);

        uint32_t array_index =
            index / std::numeric_limits<binary::value_type>::digits;

        uint32_t offset =
            index % std::numeric_limits<binary::value_type>::digits;

        return (elements[array_index] >> offset) & 0x1;
    }

    /// get_value specialization for the binary4 field
    /// @copydoc get_value(value_type*, uint32_t)
    template<>
    inline binary4::value_type
    get_value<binary4>(const binary4::value_type *elements, uint32_t index)
    {
        assert(elements != 0);

        uint32_t array_index = index / 2;

        if (index % 2 == 1)
        {
            // get upper nibble
            return (elements[array_index] & 0xF0) >> 4;
        }
        else
        {
            // get lower nibble
            return elements[array_index] & 0x0F;
        }
    }

    /// Useful abstraction function for assigning field elements in a buffer
    /// a specific value. Note this function assumes that values are packed.
    /// @param elements elements to manipulate
    /// @param index index of element
    /// @param value value to assign element
    template<class Field>
    inline void set_value(typename Field::value_type* elements, uint32_t index,
                          typename Field::value_type value)
    {
        assert(elements != 0);
        elements[index] = value;
    }

    /// set_value specialization for the binary field
    /// @copydoc set_value(value_type*, uint32_t, value_type)
    template<>
    inline void set_value<binary>(binary::value_type* elements, uint32_t index,
                                  binary::value_type value)
    {
        assert(elements != 0);
        assert(value < 2); // only {0,1} allowed

        uint32_t array_index =
            index / std::numeric_limits<binary::value_type>::digits;
        uint32_t offset =
            index % std::numeric_limits<binary::value_type>::digits;

        binary::value_type mask = 1 << offset;

        if (value)
        {
            elements[array_index] |= mask;
        }
        else
        {
            elements[array_index] &= ~mask;
        }
    }

    /// set_value specialization for the binary4 field
    /// @copydoc set_value(value_type*, uint32_t, value_type)
    template<>
    inline void set_value<binary4>(
        binary4::value_type* elements,
        uint32_t index,
        binary4::value_type value)
    {
        assert(elements != 0);
        assert(value < 16);

        uint32_t array_index = index / 2;

        if (index % 2 == 1)
        {
            // write upper nibble
            elements[array_index] &= 0x0F;
            elements[array_index] |= (value << 4);
        }
        else
        {
            // write lower nibble
            elements[array_index] &= 0xF0;
            elements[array_index] |= value;
        }
    }

    /// Useful abstraction function for swapping two field elements
    /// @param elements elements to manipulate
    /// @param index1,index2 indexes of elements to swap
    template<class Field>
    inline void swap_values(typename Field::value_type* elements,
                            uint32_t index1,
                            uint32_t index2)
    {
        assert(elements != 0);

        typename Field::value_type value1 = get_value<Field>(elements, index1);
        typename Field::value_type value2 = get_value<Field>(elements, index2);

        set_value<Field>(elements, index1, value2);
        set_value<Field>(elements, index2, value1);
    }

    /// @todo This function can be optimized by specializing it to
    /// fields that do not need packing.
    ///
    /// Useful abstraction function for creating packed constants
    /// @param constant the constant to pack.
    template<class Field>
    inline typename Field::value_type pack(typename Field::value_type constant)
    {
        assert(is_valid_element<Field>(constant));

        typedef typename Field::value_type value_type;

        value_type result = 0;

        uint32_t elements = size_to_elements<Field>(sizeof(value_type));
        for (uint32_t i = 0; i < elements; ++i)
        {
            set_value<Field>(&result, i, constant);
        }

        return result;
    }
}
