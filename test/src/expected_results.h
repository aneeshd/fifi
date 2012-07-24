// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#ifndef FIFI_TEST_EXPECTED_RESULTS_H
#define FIFI_TEST_EXPECTED_RESULTS_H

#include <fifi/field_types.h>

// The expected result of an arithmetic operation
// e.g. result == operation(arg1, arg2).
// Where operation can be add, subtract, multiply
// and divide.
//
// Note, we can use the same results for all algorithms
// since they are over the same field they should
// produce the same results.
//
// Feel free to add more results to the tables.
//

template<class Field>
struct expected_result_1
{
    typename Field::value_type arg1;
    typename Field::value_type result;
};

template<class Field>
struct expected_result_2
{
    typename Field::value_type arg1;
    typename Field::value_type arg2;
    typename Field::value_type result;
};

template<class Field>
struct multiply_results;

template<>
struct multiply_results<fifi::binary8>
{
    static const expected_result_2<fifi::binary8> m_results[];
};


// Multiply binary 8
extern const expected_result_2<fifi::binary8> expected_multiply_binary8[];
extern const uint32_t expected_multiply_binary8_size;

// Divide binary 8
extern const expected_result_2<fifi::binary8> expected_divide_binary8[];
extern const uint32_t expected_divide_binary8_size;

// Add binary 8
extern const expected_result_2<fifi::binary8> expected_add_binary8[];
extern const uint32_t expected_add_binary8_size;

// Subtract binary 8
extern const expected_result_2<fifi::binary8> expected_subtract_binary8[];
extern const uint32_t expected_subtract_binary8_size;

// Invert binary 8
extern const expected_result_1<fifi::binary8> expected_invert_binary8[];
extern const uint32_t expected_invert_binary8_size;

// Multiply binary 16
extern const expected_result_2<fifi::binary16> expected_multiply_binary16[];
extern const uint32_t expected_multiply_binary16_size;

// Divide binary 16
extern const expected_result_2<fifi::binary16> expected_divide_binary16[];
extern const uint32_t expected_divide_binary16_size;

// Add binary 16
extern const expected_result_2<fifi::binary16> expected_add_binary16[];
extern const uint32_t expected_add_binary16_size;

// Subtract binary 16
extern const expected_result_2<fifi::binary16> expected_subtract_binary16[];
extern const uint32_t expected_subtract_binary16_size;

// Invert binary 16
extern const expected_result_1<fifi::binary16> expected_invert_binary16[];
extern const uint32_t expected_invert_binary16_size;

// Multiply prime2325
extern const expected_result_2<fifi::prime2325> expected_multiply_prime2325[];
extern const uint32_t expected_multiply_prime2325_size;

// Divide prime2325
extern const expected_result_2<fifi::prime2325> expected_divide_prime2325[];
extern const uint32_t expected_divide_prime2325_size;

// Add prime2325
extern const expected_result_2<fifi::prime2325> expected_add_prime2325[];
extern const uint32_t expected_add_prime2325_size;

// Subtract prime2325
extern const expected_result_2<fifi::prime2325> expected_subtract_prime2325[];
extern const uint32_t expected_subtract_prime2325_size;

// Invert prime2325
extern const expected_result_1<fifi::prime2325> expected_invert_prime2325[];
extern const uint32_t expected_invert_prime2325_size;






#endif

