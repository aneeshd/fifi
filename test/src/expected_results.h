// Copyright Steinwurf APS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE_1_0.txt or
// http://www.steinwurf.dk/licensing

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
// They have been verified using Matlab.

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

// Multiply binary 8
extern const expected_result_2<fifi::binary8> expected_multiply_binary8[];
extern const uint32_t expected_multiply_binary8_size;

// Divide binary 8
extern const expected_result_2<fifi::binary8> expected_divide_binary8[];
extern const uint32_t expected_divide_binary8_size;

// Invert binary 8
extern const expected_result_1<fifi::binary8> expected_invert_binary8[];
extern const uint32_t expected_invert_binary8_size;


// Multiply binary 16
extern const expected_result_2<fifi::binary16> expected_multiply_binary16[];
extern const uint32_t expected_multiply_binary16_size;

// Divide binary 16
extern const expected_result_2<fifi::binary16> expected_divide_binary16[];
extern const uint32_t expected_divide_binary16_size;

// Invert binary 16
extern const expected_result_1<fifi::binary16> expected_invert_binary16[];
extern const uint32_t expected_invert_binary16_size;


#endif

