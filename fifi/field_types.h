// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#ifndef FIFI_FIELD_TYPES_H
#define FIFI_FIELD_TYPES_H

#include <stdint.h>
#include <cassert>
#include <limits>

namespace fifi
{


    // The binary field, containing the two elements {0,1}
    // We do not provide the degree() function since this is
    // not an extension field.
    struct binary
    {

        // The data type used for each element
        typedef uint8_t value_type;

        // Pointer to a value_type
        typedef value_type* value_ptr;

        // Reference to a value_type
        typedef value_type& value_ref;

        // The data type used to hold the order of the field
        // i.e. the number of elements
        typedef uint8_t order_type;

        // The maximum decimal value of any field element
        const static value_type max_value = 1;

        // The minimum decimal value for any field element
        const static value_type min_value = 0;

        // The field order i.e. number of field elements
        const static order_type order = 2;

    };

    // A binary extension field with 2^8 elements
    struct binary8
    {
        // The data type used for each element
        typedef uint8_t value_type;

        // Pointer to a value_type
        typedef value_type* value_ptr;

        // Reference to a value_type
        typedef value_type& value_ref;

        // The data type used to hold the order of the field
        // i.e. the number of elements
        typedef uint32_t order_type;

        // The data type used to hold the degree of the field
        typedef uint32_t degree_type;

        // The maximum decimal value of any field element
        const static value_type max_value = 255;

        // The minimum decimal value for any field element
        const static value_type min_value = 0;

        // The field order i.e. number of field elements
        const static order_type order = 256;

        // The field degree
        const static degree_type degree = 8;

        // X^8+X^4+X^3+X^2+1 = 285
        // We do not need the top bit so we just use:
        // X^4+X^3+X^2+1 = 29
        // We do not need the top bit since this
        // bit is not representable in the field.
        // Our algorithms should manage whether it
        // it necessary to reduce an element, if needed
        // only lower bits of the prime is needed.
        const static value_type prime = 29;

    };

    // A binary extension field with 2^16 elements
    struct binary16
    {

        // The data type used for each element
        typedef uint16_t value_type;

        // Pointer to a value_type
        typedef value_type* value_ptr;

        // Reference to a value_type
        typedef value_type& value_ref;

        // The data type used to hold the order of the field
        // i.e. the number of elements
        typedef uint32_t order_type;

        // The data type used to hold the degree of the field
        typedef uint32_t degree_type;

        // The maximum decimal value of any field element
        const static value_type max_value = 65535;

        // The minimum decimal value for any field element
        const static value_type min_value = 0;

        // The field order i.e. number of field elements
        const static order_type order = 65536;

        // The field degree
        const static degree_type degree = 16;

        // X^16+X^12+X^3+X+1 = 69643
        // We do not need the top bit
        // so we just use:
        // X^12+X^3+X+1 = 4107
        // We do not need the top bit since this
        // bit is not representable in the field.
        // Our algorithms should manage whether it
        // it necessary to reduce an element, if needed
        // only lower bits of the prime is needed.
        const static value_type prime = 4107;

    };

    // A binary extension field with 2^32 elements
    struct binary32
    {
        typedef uint32_t value_type;

        // Pointer to a value_type
        typedef value_type* value_ptr;

        // Reference to a value_type
        typedef value_type& value_ref;

        static value_type max_value()
        { return 4294967295U; }

        static value_type min_value()
        { return 0; }

        static uint64_t order()
        { return 4294967296ULL; }

        static uint32_t degree()
        { return 32; }

    };

    // Prime field 2^32 - 5
    struct prime2325
    {

        // The data type used for each element
        typedef uint32_t value_type;

        // Pointer to a value_type
        typedef value_type* value_ptr;

        // Reference to a value_type
        typedef value_type& value_ref;

        // The data type used to hold the order of the field
        // i.e. the number of elements
        typedef uint32_t order_type;

        // The maximum decimal value of any field element
        const static value_type max_value = 4294967290U;

        // The minimum decimal value for any field element
        const static value_type min_value = 0;

        // The field order i.e. number of field elements
        const static order_type order = 4294967291U;

        // The prime number used i.e. (2^32 - 5)
        const static value_type prime = 4294967291U;
    };

    // Prime field 2^31 - 1
    struct prime2311
    {
        typedef uint32_t value_type;

        // Pointer to a value_type
        typedef value_type* value_ptr;

        // Reference to a value_type
        typedef value_type& value_ref;

        // The prime number used i.e. (2^31 - 1)
        const static value_type prime = 2147483647;
    };

}

#endif

