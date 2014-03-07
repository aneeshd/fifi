// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "expected_results.hpp"

/// @todo Make this file (and its cpp file), meet our standard of one class per
/// file.

// Small helper function to get the size of the arrays
template<class T, uint32_t N>
inline uint32_t dimension_of(T (&)[N])
{
    return N;
}


//------------------------------------------------------------------
// binary
//------------------------------------------------------------------

const expected_result_binary<fifi::binary>
multiply_results<fifi::binary>::m_results[] =
{
    // m_input1, m_input2, m_result
    { 0, 0, 0 },
    { 0, 1, 0 },
    { 1, 0, 0 },
    { 1, 1, 1 },
};

const uint32_t multiply_results<fifi::binary>::m_size =
    dimension_of(multiply_results<fifi::binary>::m_results);

const expected_result_binary<fifi::binary>
divide_results<fifi::binary>::m_results[] =
{
    // m_input1, m_input2, m_result
    { 0, 1, 0 },
    { 1, 1, 1 },
};

const uint32_t divide_results<fifi::binary>::m_size =
    dimension_of(divide_results<fifi::binary>::m_results);

const expected_result_binary<fifi::binary>
add_results<fifi::binary>::m_results[] =
{
    // m_input1, m_input2, m_result
    { 0, 0, 0 },
    { 0, 1, 1 },
    { 1, 0, 1 },
    { 1, 1, 0 },
};

const uint32_t add_results<fifi::binary>::m_size =
    dimension_of(add_results<fifi::binary>::m_results);

// Zero has no inverse and one is its own inverse
const expected_result_unary<fifi::binary>
invert_results<fifi::binary>::m_results[] =
{
    // m_input1, m_result
    { 1, 1 },
};

const uint32_t invert_results<fifi::binary>::m_size =
    dimension_of(invert_results<fifi::binary>::m_results);

const expected_result_unary<fifi::binary>
find_degree_results<fifi::binary>::m_results[] =
{
    // m_input1, m_result
    { 0, 0 },
    { 1, 0 },
};

const uint32_t find_degree_results<fifi::binary>::m_size =
    dimension_of(find_degree_results<fifi::binary>::m_results);

const expected_result_binary<fifi::binary>
sum_modulo_results<fifi::binary>::m_results[] =
{
    // m_input1, m_input2, m_result
    { 0, 0, 0 },
    { 0, 1, 1 },
    { 1, 0, 1 },
    { 1, 1, 1 },
};

const uint32_t sum_modulo_results<fifi::binary>::m_size =
    dimension_of(sum_modulo_results<fifi::binary>::m_results);

//////////////////////
/// packed results ///
//////////////////////

const expected_result_binary<fifi::binary>
packed_multiply_results<fifi::binary>::m_results[] =
{
    // m_input1, m_input2, m_result
    {   1, 255,   1 },
    {  14, 255,  14 },
    {  15, 255,  15 },
    {  16, 255,  16 },
    {  32,   1,   0 },
    {  33,   1,   1 },
    {  33, 255,  33 },
    {  64, 255,  64 },
    { 128, 255, 128 },
    { 129, 255, 129 },
    { 255,   1,   1 },
    { 255,   1,   1 },
    { 255,  14,  14 },
    { 255,  15,  15 },
    { 255,  16,  16 },
    { 255,  33,  33 },
    { 255,  64,  64 },
    { 255, 128, 128 },
    { 255, 129, 129 },
};

const uint32_t packed_multiply_results<fifi::binary>::m_size =
    dimension_of(packed_multiply_results<fifi::binary>::m_results);

const expected_result_binary<fifi::binary>
packed_divide_results<fifi::binary>::m_results[] =
{
    // m_input1, m_input2, m_result
    {   1, 255,   1 },
    {  14, 255,  14 },
    {  15, 255,  15 },
    {  16, 255,  16 },
    {  33, 255,  33 },
    {  64, 255,  64 },
    { 128, 255, 128 },
    { 129, 255, 129 },
};

const uint32_t packed_divide_results<fifi::binary>::m_size =
    dimension_of(packed_divide_results<fifi::binary>::m_results);

const expected_result_binary<fifi::binary>
packed_add_results<fifi::binary>::m_results[] =
{
    // m_input1, m_input2, m_result
    {   0,   0,   0 },
    {   0,   1,   1 },
    {   1,   0,   1 },
    {   1,   1,   0 },
    { 128, 255, 127 },
    { 255,   0, 255 },
    { 255, 255,   0 },
};

const uint32_t packed_add_results<fifi::binary>::m_size =
    dimension_of(packed_add_results<fifi::binary>::m_results);

// Zero has no inverse and one is its own inverse
const expected_result_unary<fifi::binary>
packed_invert_results<fifi::binary>::m_results[] =
{
    // m_input1, m_result
    { 255, 255},
};

const uint32_t packed_invert_results<fifi::binary>::m_size =
    dimension_of(packed_invert_results<fifi::binary>::m_results);

//------------------------------------------------------------------
// binary4
//------------------------------------------------------------------

const expected_result_binary<fifi::binary4>
multiply_results<fifi::binary4>::m_results[] =
{
    // m_input1, m_input2, m_result
    {  0, 13,  0 },
    {  0, 14,  0 },
    {  1,  1,  1 },
    {  2,  9,  1 },
    {  2, 11,  5 },
    {  3,  2,  6 },
    {  4,  8,  6 },
    {  5, 11,  1 },
    {  5, 14,  3 },
    {  5, 15,  6 },
    {  6,  6,  7 },
    {  6, 11, 15 },
    {  7, 15, 11 },
    {  8, 12, 10 },
    {  9,  5, 11 },
    {  9,  9, 13 },
    { 10,  0,  0 },
    { 11,  9, 12 },
    { 12,  4,  5 },
    { 12,  8, 10 },
    { 13,  1, 13 },
    { 13, 15,  7 },
    { 14,  7, 12 },
    { 14,  8,  9 },
    { 15,  5,  6 },
};

const uint32_t multiply_results<fifi::binary4>::m_size =
    dimension_of(multiply_results<fifi::binary4>::m_results);

const expected_result_binary<fifi::binary4>
divide_results<fifi::binary4>::m_results[] =
{
    // m_input1, m_input2, m_result
    {  0,  4,  0 },
    {  0,  7,  0 },
    {  0,  8,  0 },
    {  0,  9,  0 },
    {  0,  9,  0 },
    {  0, 13,  0 },
    {  1,  1,  1 },
    {  1, 12, 10 },
    {  2,  9,  4 },
    {  2, 14,  6 },
    {  4,  8,  9 },
    {  6,  3,  2 },
    {  6,  4,  8 },
    {  9,  1,  9 },
    {  9, 13,  2 },
    { 10, 10,  1 },
    { 11,  6,  4 },
    { 11,  8,  3 },
    { 11,  8,  3 },
    { 11, 12,  2 },
    { 11, 14, 14 },
    { 12,  2,  6 },
    { 12,  8,  8 },
    { 14,  5,  8 },
    { 14, 14,  1 },
};

const uint32_t divide_results<fifi::binary4>::m_size =
    dimension_of(divide_results<fifi::binary4>::m_results);

const expected_result_binary<fifi::binary4>
add_results<fifi::binary4>::m_results[] =
{
    // m_input1, m_input2, m_result
    {  1,  6,  7 },
    {  2,  5,  7 },
    {  2,  6,  4 },
    {  3,  0,  3 },
    {  3,  5,  6 },
    {  3, 13, 14 },
    {  5,  1,  4 },
    {  5,  3,  6 },
    {  6,  7,  1 },
    {  6, 12, 10 },
    {  7,  1,  6 },
    {  7,  6,  1 },
    {  8,  4, 12 },
    { 10,  4, 14 },
    { 10,  6, 12 },
    { 11,  4, 15 },
    { 11, 14,  5 },
    { 12,  0, 12 },
    { 12,  1, 13 },
    { 12, 13,  1 },
    { 13,  7, 10 },
    { 14,  4, 10 },
    { 14,  6,  8 },
    { 15,  0, 15 },
    { 15,  1, 14 },
};

const uint32_t add_results<fifi::binary4>::m_size =
    dimension_of(add_results<fifi::binary4>::m_results);

const expected_result_unary<fifi::binary4>
invert_results<fifi::binary4>::m_results[] =
{
    // m_input1, m_result
    {  1,  1 },
    {  2,  9 },
    {  3, 14 },
    {  3, 14 },
    {  4, 13 },
    {  4, 13 },
    {  5, 11 },
    {  5, 11 },
    {  5, 11 },
    {  6,  7 },
    {  6,  7 },
    {  9,  2 },
    { 10, 12 },
    { 10, 12 },
    { 10, 12 },
    { 11,  5 },
    { 11,  5 },
    { 12, 10 },
    { 14,  3 },
    { 14,  3 },
    { 14,  3 },
    { 15,  8 },
    { 15,  8 },
    { 15,  8 },
    { 15,  8 },
};

const uint32_t invert_results<fifi::binary4>::m_size =
    dimension_of(invert_results<fifi::binary4>::m_results);

const expected_result_unary<fifi::binary4>
find_degree_results<fifi::binary4>::m_results[] =
{
    // m_input1, m_result
    {  0, 0 },
    {  1, 0 },
    {  2, 1 },
    {  3, 1 },
    {  4, 2 },
    {  5, 2 },
    {  6, 2 },
    {  7, 2 },
    {  8, 3 },
    {  9, 3 },
    { 10, 3 },
    { 11, 3 },
    { 12, 3 },
    { 13, 3 },
    { 14, 3 },
    { 15, 3 },
};

const uint32_t find_degree_results<fifi::binary4>::m_size =
    dimension_of(find_degree_results<fifi::binary4>::m_results);

const expected_result_binary<fifi::binary4>
sum_modulo_results<fifi::binary4>::m_results[] =
{
    // m_input1, m_input2, m_result
    {  0,  0,  0 },
    {  0,  1,  1 },
    {  0, 15, 15 },
    {  1,  0,  1 },
    {  1,  1,  2 },
    {  5,  5, 10 },
    { 10, 10,  5 },
    { 15, 10, 10 },
    { 15, 15, 15 },
};

const uint32_t sum_modulo_results<fifi::binary4>::m_size =
    dimension_of(sum_modulo_results<fifi::binary4>::m_results);

//////////////////////
/// packed results ///
//////////////////////

const expected_result_binary<fifi::binary4>
packed_multiply_results<fifi::binary4>::m_results[] =
{
    // m_input1, m_input2, m_result
    {  0, 13,  0 },
    {  0, 14,  0 },
    {  1,  1,  1 },
    {  2,  9,  1 },
    {  2, 11,  5 },
    {  3,  2,  6 },
    {  4,  8,  6 },
    {  5, 11,  1 },
    {  5, 14,  3 },
    {  5, 15,  6 },
    {  6,  6,  7 },
    {  6, 11, 15 },
    {  7, 15, 11 },
    {  8, 12, 10 },
    {  9,  5, 11 },
    {  9,  9, 13 },
    { 10,  0,  0 },
    { 11,  9, 12 },
    { 12,  4,  5 },
    { 12,  8, 10 },
    { 13,  1, 13 },
    { 13, 15,  7 },
    { 14,  7, 12 },
    { 14,  8,  9 },
    { 15,  5,  6 },
};

const uint32_t packed_multiply_results<fifi::binary4>::m_size =
    dimension_of(packed_multiply_results<fifi::binary4>::m_results);

const expected_result_binary<fifi::binary4>
packed_divide_results<fifi::binary4>::m_results[] =
{
    // m_input1, m_input2, m_result
    {  0, 20,  0 },
    {  0, 23,  0 },
    {  0, 24,  0 },
    {  0, 25,  0 },
    {  0, 25,  0 },
    {  0, 29,  0 },
    {  1, 17,  1 },
    {  1, 28, 10 },
    {  2, 25,  4 },
    {  2, 30,  6 },
    {  4, 24,  9 },
    {  6, 19,  2 },
    {  6, 20,  8 },
    {  9, 17,  9 },
    {  9, 29,  2 },
    { 10, 26,  1 },
    { 11, 22,  4 },
    { 11, 24,  3 },
    { 11, 24,  3 },
    { 11, 28,  2 },
    { 11, 30, 14 },
    { 12, 18,  6 },
    { 12, 24,  8 },
    { 14, 21,  8 },
    { 14, 30,  1 },
};

const uint32_t packed_divide_results<fifi::binary4>::m_size =
    dimension_of(packed_divide_results<fifi::binary4>::m_results);

///@todo, add testing values spanning a whole byte
const expected_result_binary<fifi::binary4>
packed_add_results<fifi::binary4>::m_results[] =
{
    // m_input1, m_input2, m_result
    {  1,  6,  7 },
    {  1,  9,  8 },
    {  1, 12, 13 },
    {  1, 15, 14 },
    {  2,  3,  1 },
    {  2,  5,  7 },
    {  2,  6,  4 },
    {  2, 10,  8 },
    {  2, 11,  9 },
    {  3,  0,  3 },
    {  3,  2,  1 },
    {  3,  5,  6 },
    {  3, 13, 14 },
    {  4,  2,  6 },
    {  4, 11, 15 },
    {  5,  1,  4 },
    {  5,  3,  6 },
    {  6,  7,  1 },
    {  6,  8, 14 },
    {  6, 12, 10 },
    {  7,  1,  6 },
    {  7,  6,  1 },
    {  7, 12, 11 },
    {  8,  4, 12 },
    {  9,  3, 10 },
    {  9,  6, 15 },
    { 10,  4, 14 },
    { 10,  6, 12 },
    { 10, 13,  7 },
    { 11,  4, 15 },
    { 11, 12,  7 },
    { 11, 14,  5 },
    { 12,  0, 12 },
    { 12,  1, 13 },
    { 12, 13,  1 },
    { 13,  3, 14 },
    { 13,  7, 10 },
    { 13,  9,  4 },
    { 13, 13,  0 },
    { 14,  4, 10 },
    { 14,  6,  8 },
    { 14,  8,  6 },
    { 14,  9,  7 },
    { 14, 11,  5 },
    { 15,  0, 15 },
    { 15,  1, 14 },
    { 17, 17,  0 },
};

const uint32_t packed_add_results<fifi::binary4>::m_size =
    dimension_of(packed_add_results<fifi::binary4>::m_results);

const expected_result_unary<fifi::binary4>
packed_invert_results<fifi::binary4>::m_results[] =
{
    // m_input1, m_result
    {  21,  27 },
    {  36, 157 },
    {  51, 238 },
    {  51, 238 },
    {  66, 217 },
    {  73, 210 },
    {  81, 177 },
    {  91, 181 },
    {  95, 184 },
    { 108, 122 },
    { 111, 120 },
    { 148,  45 },
    { 170, 204 },
    { 170, 204 },
    { 175, 200 },
    { 181,  91 },
    { 191,  88 },
    { 198, 167 },
    { 238,  51 },
    { 238,  51 },
    { 238,  51 },
    { 245, 139 },
    { 246, 135 },
    { 250, 140 },
    { 251, 133 },
};

const uint32_t packed_invert_results<fifi::binary4>::m_size =
    dimension_of(packed_invert_results<fifi::binary4>::m_results);

//------------------------------------------------------------------
// binary8
//------------------------------------------------------------------

const expected_result_binary<fifi::binary8>
multiply_results<fifi::binary8>::m_results[] =
{
    // arg1, arg2, result
    {   0,   0,   0 },
    {   0,   2,   0 },
    {   1,   1,   1 },
    {   1,   2,   2 },
    {   1,  46,  46 },
    {   2,   1,   2 },
    {   4, 200,   7 },
    {   5,   5,  17 },
    {  10,  10,  68 },
    {  10,  20, 136 },
    {  12,  87, 195 },
    {  25,  10, 250 },
    {  25,  15, 135 },
    {  25,  66,  60 },
    {  30, 242,  78 },
    {  67,   1,  67 },
    { 110,   7,  23 },
    { 110, 253, 232 },
    { 144,  66, 206 },
    { 176, 132, 204 },
    { 200, 200, 158 },
    { 251, 133, 104 },
    { 254, 254, 227 },
    { 255, 255, 226 },
};

const uint32_t multiply_results<fifi::binary8>::m_size =
    dimension_of(multiply_results<fifi::binary8>::m_results);


const expected_result_binary<fifi::binary8>
divide_results<fifi::binary8>::m_results[] =
{
    // arg1, arg2, result
    {   0,   2,   0 },
    {   1,   1,   1 },
    {   1,   2, 142 },
    {   1,  46,  51 },
    {   2,   1,   2 },
    {   4, 200, 111 },
    {   5,   5,   1 },
    {  10,  10,   1 },
    {  10,  20, 142 },
    {  12,  87, 182 },
    {  25,  10,  42 },
    {  25,  15, 199 },
    {  25,  66,  80 },
    {  30, 242, 199 },
    {  67,   1,  67 },
    { 110,   7, 125 },
    { 110, 253,  52 },
    { 144,  66, 254 },
    { 176, 132,  68 },
    { 200, 200,   1 },
    { 251, 133,  52 },
    { 254, 254,   1 },
    { 255, 255,   1 },
};

const uint32_t divide_results<fifi::binary8>::m_size =
    dimension_of(divide_results<fifi::binary8>::m_results);

// Add binary8
//
// Computed using the following Matlab script:
//
//     m = 8
//     n = 2^m - 1
//     max = 20
//
//     for j = 0:max
//       v1 = uint8(rand(1) * n);
//       v2 = uint8(rand(1) * n);
//
//       gf1 = gf(v1, m);
//       gf2 = gf(v2, m);
//
//       xgf = gf1 + gf2;
//
//       str = sprintf('{ %4d, %4d, %4d }', uint8(gf1.x), uint8(gf2.x), uint8(xgf.x));
//       disp(str)
//     end
const expected_result_binary<fifi::binary8>
add_results<fifi::binary8>::m_results[] =
{
    // arg1, arg2, result
    {    4,  196,  192 },
    {   13,  106,  103 },
    {   15,  154,  149 },
    {   53,  155,  174 },
    {   54,  214,  224 },
    {   68,  112,   52 },
    {   78,  223,  145 },
    {   97,  200,  169 },
    {  105,  190,  215 },
    {  127,   55,   72 },
    {  145,  203,   90 },
    {  160,   34,  130 },
    {  161,   94,  255 },
    {  163,   53,  150 },
    {  164,   82,  246 },
    {  174,  118,  216 },
    {  194,  135,   69 },
    {  201,  112,  185 },
    {  238,  174,   64 },
    {  245,  185,   76 },
    {  248,  252,    4 },
};

const uint32_t add_results<fifi::binary8>::m_size =
    dimension_of(add_results<fifi::binary8>::m_results);

// Invert binary8
const expected_result_unary<fifi::binary8>
invert_results<fifi::binary8>::m_results[] =
{
    // arg1, result
    {   1,   1 },
    {   2, 142 },
    {   5, 167 },
    {  10, 221 },
    {  15, 150 },
    {  20, 224 },
    {  25, 222 },
    {  46,  51 },
    {  66, 248 },
    {  67, 213 },
    {  87,  97 },
    { 110,  47 },
    { 132, 124 },
    { 133, 204 },
    { 144,  24 },
    { 200, 210 },
    { 242, 181 },
    { 253, 255 },
    { 254, 126 },
    { 255, 253 },
};

const uint32_t invert_results<fifi::binary8>::m_size =
    dimension_of(invert_results<fifi::binary8>::m_results);

const expected_result_unary<fifi::binary8>
find_degree_results<fifi::binary8>::m_results[] =
{
    // m_input1, m_result
    {   0, 0 },
    {   1, 0 },
    {   2, 1 },
    {   3, 1 },
    {   4, 2 },
    {   5, 2 },
    {   6, 2 },
    {   7, 2 },
    {   8, 3 },
    {   9, 3 },
    {  10, 3 },
    {  11, 3 },
    {  12, 3 },
    {  13, 3 },
    {  14, 3 },
    {  15, 3 },
    {  16, 4 },
    {  17, 4 },
    {  31, 4 },
    {  32, 5 },
    {  63, 5 },
    {  64, 6 },
    { 127, 6 },
    { 128, 7 },
    { 254, 7 },
    { 255, 7 },
};

const uint32_t find_degree_results<fifi::binary8>::m_size =
    dimension_of(find_degree_results<fifi::binary8>::m_results);

const expected_result_binary<fifi::binary8>
sum_modulo_results<fifi::binary8>::m_results[] =
{
    // arg1, arg2, result
    {   4,   4,   8 },
    {  11,   7,  18 },
    {  15,  94, 109 },
    {  24,   9,  33 },
    {  48, 150, 198 },
    {  59, 205,   9 },
    {  65, 221,  31 },
    {  80,   3,  83 },
    {  90,  39, 129 },
    { 200, 200, 145 },
};

const uint32_t sum_modulo_results<fifi::binary8>::m_size =
    dimension_of(sum_modulo_results<fifi::binary8>::m_results);

//------------------------------------------------------------------
// binary16
//------------------------------------------------------------------

const expected_result_binary<fifi::binary16>
multiply_results<fifi::binary16>::m_results[] =
{
    // arg1, arg2, result
    {   0,   0,     0 },
    {   0,   2,     0 },
    {   1,   1,     1 },
    {   1,   2,     2 },
    {   1,  46,    46 },
    {   2,   1,     2 },
    {   4, 200,   800 },
    {   5,   5,    17 },
    {  10,  10,    68 },
    {  10,  20,   136 },
    {  12,  87,   996 },
    {  25,  10,   250 },
    {  25,  15,   135 },
    {  25,  66,  1650 },
    {  30, 242,  2716 },
    {  67,   1,    67 },
    { 110,   7,   266 },
    { 110, 253,  9478 },
    { 144,  66,  9504 },
    { 176, 132, 23232 },
    { 200, 200, 20544 },
    { 251, 133, 32407 },
    { 254, 254, 21844 },
    { 255, 255, 21845 },
};

const uint32_t multiply_results<fifi::binary16>::m_size =
    dimension_of(multiply_results<fifi::binary16>::m_results);



const expected_result_binary<fifi::binary16>
divide_results<fifi::binary16>::m_results[] =
{
    // arg1, arg2, result
    {   0,   2,     0 },
    {   1,   1,     1 },
    {   1,   2, 34821 },
    {   1,  46,  2983 },
    {   2,   1,     2 },
    {   4, 200, 28050 },
    {   5,   5,     1 },
    {  10,  10,     1 },
    {  10,  20, 34821 },
    {  12,  87, 46287 },
    {  25,  10, 55300 },
    {  25,  15, 24577 },
    {  25,  66, 55164 },
    {  30, 242, 34597 },
    {  67,   1,    67 },
    { 110,   7, 54984 },
    { 110, 253,   825 },
    { 144,  66, 54045 },
    { 176, 132,  2247 },
    { 200, 200,     1 },
    { 251, 133, 46436 },
    { 254, 254,     1 },
    { 255, 255,     1 },
};

const uint32_t divide_results<fifi::binary16>::m_size =
    dimension_of(divide_results<fifi::binary16>::m_results);


// Add binary16
//
// Computed using the following Matlab script:
//
//     m = 16
//     n = 2^m - 1
//     prime = 69643
//     max = 20
//
//     for j = 0:max
//       v1 = uint16(rand(1) * n);
//       v2 = uint16(rand(1) * n);
//
//       gf1 = gf(v1, m, prime);
//       gf2 = gf(v2, m, prime);
//
//       xgf = gf1 + gf2;
//
//       str = sprintf('{ %6dU, %6dU, %6dU }', ...
//                     uint16(gf1.x), uint16(gf2.x), ...
//                     uint16(xgf.x));
//       disp(str)
//     end
const expected_result_binary<fifi::binary16>
add_results<fifi::binary16>::m_results[] =
{
    // arg1, arg2, result
    {   4245U,  64771U,  60822U },
    {   8947U,    770U,   8689U },
    {  11335U,  64208U,  54935U },
    {  13701U,  24891U,  21694U },
    {  17789U,  16536U,   1509U },
    {  18639U,  30751U,  12496U },
    {  19577U,  43348U,  58669U },
    {  27222U,  19988U,   9282U },
    {  28371U,  14808U,  22283U },
    {  30218U,  37213U,  59223U },
    {  33784U,  21886U,  54918U },
    {  34722U,  41977U,   9307U },
    {  37998U,  49831U,  22217U },
    {  38193U,  27754U,  63835U },
    {  39509U,   3294U,  38539U },
    {  50328U,  63624U,  15376U },
    {  51335U,  44619U,  26316U },
    {  52049U,   3879U,  50294U },
    {  57302U,    984U,  56334U },
    {  57392U,  48319U,  23695U },
    {  58582U,  13051U,  54829U },
};

const uint32_t add_results<fifi::binary16>::m_size =
    dimension_of(add_results<fifi::binary16>::m_results);

// Invert binary16
const expected_result_unary<fifi::binary16>
invert_results<fifi::binary16>::m_results[] =
{
    // arg1, result
    {   1,     1 },
    {   2, 34821 },
    {   5, 20482 },
    {  10, 10241 },
    {  15, 49159 },
    {  20, 39941 },
    {  25, 56100 },
    {  46,  2983 },
    {  66, 19094 },
    {  67, 56530 },
    {  87, 55062 },
    { 110, 61399 },
    { 132,  9547 },
    { 133, 63805 },
    { 144, 25710 },
    { 200, 37729 },
    { 242, 46215 },
    { 253, 38174 },
    { 254, 12174 },
    { 255,  7372 },
};

const uint32_t invert_results<fifi::binary16>::m_size =
    dimension_of(invert_results<fifi::binary16>::m_results);

const expected_result_unary<fifi::binary16>
find_degree_results<fifi::binary16>::m_results[] =
{
    // m_input1, m_result
    {     0,  0 },
    {     1,  0 },
    {     2,  1 },
    {     3,  1 },
    {     4,  2 },
    {     5,  2 },
    {     6,  2 },
    {     7,  2 },
    {     8,  3 },
    {     9,  3 },
    {    10,  3 },
    {    11,  3 },
    {    12,  3 },
    {    13,  3 },
    {    14,  3 },
    {    15,  3 },
    {    16,  4 },
    {    17,  4 },
    {    31,  4 },
    {    32,  5 },
    {    63,  5 },
    {    64,  6 },
    {   127,  6 },
    {   128,  7 },
    {   254,  7 },
    {   255,  7 },
    {   256,  8 },
    {   511,  8 },
    {   512,  9 },
    {  1023,  9 },
    {  1024, 10 },
    {  2047, 10 },
    {  2048, 11 },
    {  4095, 11 },
    {  4096, 12 },
    {  8191, 12 },
    {  8192, 13 },
    { 16383, 13 },
    { 16384, 14 },
    { 32767, 14 },
    { 32768, 15 },
    { 65535, 15 },
};

const uint32_t find_degree_results<fifi::binary16>::m_size =
    dimension_of(find_degree_results<fifi::binary16>::m_results);

const expected_result_binary<fifi::binary16>
sum_modulo_results<fifi::binary16>::m_results[] =
{
    // arg1,    arg2,    result
    {  3261U,  5137U,  8398U },
    {  5510U, 29776U, 35286U },
    {  7848U,  2499U, 10347U },
    {  7933U, 29540U, 37473U },
    { 10067U, 44278U, 54345U },
    { 11193U, 65161U, 10819U },
    { 15197U, 15683U, 30880U },
    { 17898U, 16696U, 34594U },
    { 20592U, 23925U, 44517U },
    { 25771U, 38766U, 64537U },
    { 28822U, 22285U, 51107U },
    { 28955U, 23150U, 52105U },
    { 30054U, 57007U, 21526U },
    { 31351U, 36362U,  2178U },
    { 41996U, 12510U, 54506U },
    { 45823U, 47677U, 27965U },
    { 46915U, 58512U, 39892U },
    { 47030U, 45394U, 26889U },
    { 52747U, 59532U, 46744U },
    { 55303U, 11397U,  1165U },
    { 56727U, 15227U,  6419U },
};

const uint32_t sum_modulo_results<fifi::binary16>::m_size =
    dimension_of(sum_modulo_results<fifi::binary16>::m_results);

//------------------------------------------------------------------
// prime2325
//------------------------------------------------------------------

const expected_result_binary<fifi::prime2325>
multiply_results<fifi::prime2325>::m_results[] =
{
    // arg1,       arg2,        result
    {          0U,          0U,          0U },
    {    8961698U, 1454316048U, 2844647930U },
    {  188377222U, 2440371958U, 1837383177U },
    {  366785572U, 3273833947U, 1357321858U },
    {  484124441U, 2513732051U, 2038062075U },
    {  549534826U, 3692094631U, 3813011302U },
    {  591588585U, 2298808855U, 2016341846U },
    {  628824443U, 2882587157U, 2414550839U },
    {  714307256U, 4017788735U, 2552564636U },
    {  890246292U, 3115294715U, 3374921530U },
    { 1135999486U, 2298616897U, 2948135396U },
    { 1241752606U, 2682856520U, 1016247841U },
    { 1319528055U, 3213225118U,  472935279U },
    { 1501780748U,  772682526U,  464840319U },
    { 1516764886U, 2487733786U, 1221426309U },
    { 1921500106U, 1581124167U, 2064202209U },
    { 1923821210U,    4910817U, 1727198145U },
    { 2747836187U,  606517521U, 4005335094U },
    { 2755140095U, 3176782815U, 3071678684U },
    { 2865873554U, 4023346111U, 1390523154U },
    { 2898832361U, 3285799624U,  205888686U },
    { 3216464703U, 2321361148U, 2159784831U },
    { 3301510135U, 2380300242U, 3460816498U },
    { 3791215484U,  823219598U, 3413971131U },
    { 3916985401U, 2885578550U, 3986996714U },
    { 3948329266U, 1846670630U, 2958898160U },
    { 4057832578U,  783228777U, 1061113545U },
    { 4071004727U, 3893610017U, 3098938562U },
    { 4294967290U,          1U, 4294967290U },
    { 4294967290U,          2U, 4294967289U },
    { 4294967290U, 4294967290U,          1U },
};

const uint32_t multiply_results<fifi::prime2325>::m_size =
    dimension_of(multiply_results<fifi::prime2325>::m_results);



const expected_result_binary<fifi::prime2325>
divide_results<fifi::prime2325>::m_results[] =
{
    // arg1,       arg2,        result
    {          1U, 4294967290U, 4294967290U },
    {          2U, 4294967290U, 4294967289U },
    {  163139403U, 1828949500U, 2835205604U },
    {  623898484U,   59902254U, 1708820736U },
    { 1078074232U, 1671507801U, 2817715425U },
    { 1190843567U, 1126933466U, 3113318947U },
    { 1336522198U, 1280630940U,   91488717U },
    { 1380709308U, 3151385314U, 4242837144U },
    { 2019008287U, 1889765579U, 2374943388U },
    { 2271514114U,  542032264U, 2085796361U },
    { 2622046040U,  209860049U, 1117407655U },
    { 2639979264U, 1669621279U, 3855275193U },
    { 3170796863U, 1056595135U, 2349732681U },
    { 3235144123U,  393597417U, 3381961331U },
    { 3846022732U, 2429951133U, 2542996908U },
    { 4026952922U,  589957415U, 1126790683U },
    { 4031746231U, 1150048672U, 2067171649U },
    { 4161263482U, 1084683978U,   57951883U },
    { 4188684512U,  871209300U, 4103154428U },
    { 4294967290U,          1U, 4294967290U },
    { 4294967290U,          2U, 2147483645U },
    { 4294967290U, 4294967290U,          1U },
};


const uint32_t divide_results<fifi::prime2325>::m_size =
    dimension_of(divide_results<fifi::prime2325>::m_results);


const expected_result_binary<fifi::prime2325>
add_results<fifi::prime2325>::m_results[] =
{
    // arg1,       arg2,        result
    {          0U,          0U,          0U },
    {   13775737U, 3832303341U, 3846079078U },
    {  416764808U, 2952672146U, 3369436954U },
    {  954547203U, 3403230939U,   62810851U },
    { 1304171116U, 2058347943U, 3362519059U },
    { 1997027658U, 1158755251U, 3155782909U },
    { 2228876704U, 3769080616U, 1702990029U },
    { 2699559732U, 4130167990U, 2534760431U },
    { 2721360764U, 3099915689U, 1526309162U },
    { 2761881503U, 3727769459U, 2194683671U },
    { 2780503337U,  508086692U, 3288590029U },
    { 3164597666U,  249577394U, 3414175060U },
    { 3275759048U,  318206772U, 3593965820U },
    { 3393423153U, 2569499151U, 1667955013U },
    { 3549012440U, 3097460608U, 2351505757U },
    { 3562900696U,     433428U, 3563334124U },
    { 3733613168U, 4250233244U, 3688879121U },
    { 3860097427U, 3766812989U, 3331943125U },
    { 4294967290U,          1U,          0U },
    { 4294967290U,          2U,          1U },
    { 4294967290U, 4294967290U, 4294967289U },

};

const uint32_t add_results<fifi::prime2325>::m_size =
    dimension_of(add_results<fifi::prime2325>::m_results);

const expected_result_binary<fifi::prime2325>
subtract_results<fifi::prime2325>::m_results[] =
{
    // arg1,       arg2,        result
    {          0U,          0U,          0U },
    {          1U, 4294967290U,          2U },
    {          2U, 4294967290U,          3U },
    {  815150013U, 2783628454U, 2326488850U },
    { 1111197069U, 3288497105U, 2117667255U },
    { 1376464298U, 3719246614U, 1952184975U },
    { 1555616877U, 417999038U,  1137617839U },
    { 1591755985U, 760357706U,   831398279U },
    { 1646681944U, 2090570642U, 3851078593U },
    { 1718415100U, 3764394937U, 2248987454U },
    { 2021566441U, 1563544409U,  458022032U },
    { 2279203252U, 2364542188U, 4209628355U },
    { 2313466124U, 1242826905U, 1070639219U },
    { 2486487802U, 4101049708U, 2680405385U },
    { 3007334859U, 2068575905U,  938758954U },
    { 3267843829U, 3990959519U, 3571851601U },
    { 3448691623U, 2270397823U, 1178293800U },
    { 3601154686U, 238248285U,  3362906401U },
    { 3850830140U, 4242429948U, 3903367483U },
    { 4181356062U, 2914712094U, 1266643968U },
    { 4294967290U,          1U, 4294967289U },
    { 4294967290U,          2U, 4294967288U },
    { 4294967290U, 4294967290U,          0U },
};

const uint32_t subtract_results<fifi::prime2325>::m_size =
    dimension_of(subtract_results<fifi::prime2325>::m_results);


// Invert prime2325
const expected_result_unary<fifi::prime2325>
invert_results<fifi::prime2325>::m_results[] =
{
    // arg1,       result
    {          1U,          1U },
    {          2U, 2147483646U },
    {  272572125U, 1887955081U },
    { 1351905135U, 4218730939U },
    { 1353929616U, 2406667616U },
    { 1444146446U,  811575873U },
    { 1630048742U, 3481329838U },
    { 1879748638U, 4180067651U },
    { 1909520067U,  527117708U },
    { 2001693299U, 2659441565U },
    { 2037479732U,  770197497U },
    { 2399533030U,  403603339U },
    { 2832328698U, 1639852349U },
    { 2968542519U, 2207640096U },
    { 3319742702U, 2900579629U },
    { 3477593642U, 2778157346U },
    { 3795789800U,  915126934U },
    { 3909187862U, 1505740374U },
    { 4175463158U, 2780563524U },
    { 4294967290U, 4294967290U },
};

const uint32_t invert_results<fifi::prime2325>::m_size =
    dimension_of(invert_results<fifi::prime2325>::m_results);


const expected_result_unary<fifi::prime2325>
find_degree_results<fifi::prime2325>::m_results[] =
{
    // m_input1, m_result
    {           0,  0 },
    {           1,  0 },
    {           2,  1 },
    {           3,  1 },
    {           4,  2 },
    {           5,  2 },
    {           6,  2 },
    {           7,  2 },
    {           8,  3 },
    {           9,  3 },
    {          10,  3 },
    {          11,  3 },
    {          12,  3 },
    {          13,  3 },
    {          14,  3 },
    {          15,  3 },
    {          16,  4 },
    {          17,  4 },
    {          31,  4 },
    {          32,  5 },
    {          63,  5 },
    {          64,  6 },
    {         127,  6 },
    {         128,  7 },
    {         254,  7 },
    {         255,  7 },
    {         256,  8 },
    {         511,  8 },
    {         512,  9 },
    {        1023,  9 },
    {        1024, 10 },
    {        2047, 10 },
    {        2048, 11 },
    {        4095, 11 },
    {        4096, 12 },
    {        8191, 12 },
    {        8192, 13 },
    {       16383, 13 },
    {       16384, 14 },
    {       32767, 14 },
    {       32768, 15 },
    {       65535, 15 },
    { 4294967290U, 31 },
};

const uint32_t find_degree_results<fifi::prime2325>::m_size =
    dimension_of(find_degree_results<fifi::prime2325>::m_results);

const expected_result_binary<fifi::prime2325>
sum_modulo_results<fifi::prime2325>::m_results[] =
{
    // arg1,       arg2,        result
    {          0U,          0U,          0U },
    {          1U, 4294967290U,          1U },
    {          2U, 4294967290U,          2U },
    {       3261U,       5137U,       8398U },
    {       5510U,      29776U,      35286U },
    {       7848U,       2499U,      10347U },
    {       7933U,      29540U,      37473U },
    {      10067U,      44278U,      54345U },
    {      11193U,      65161U,      76354U },
    {      15197U,      15683U,      30880U },
    {      17898U,      16696U,      34594U },
    {      20592U,      23925U,      44517U },
    {      25771U,      38766U,      64537U },
    {      28822U,      22285U,      51107U },
    {      28955U,      23150U,      52105U },
    {      30054U,      57007U,      87061U },
    {      31351U,      36362U,      67713U },
    {      41996U,      12510U,      54506U },
    {      45823U,      47677U,      93500U },
    {      46915U,      58512U,     105427U },
    {      47030U,      45394U,      92424U },
    {      52747U,      59532U,     112279U },
    {      55303U,      11397U,      66700U },
    {      56727U,      15227U,      71954U },
    {  815150013U, 2783628454U, 3598778467U },
    { 1111197069U, 3288497105U,  104726879U },
    { 3850830140U, 4242429948U, 3798292793U },
    { 4181356062U, 2914712094U, 2801100861U },
    { 4294967290U,          1U,          1U },
    { 4294967290U,          2U,          2U },
    { 4294967290U, 4294967290U, 4294967285U },
};

const uint32_t sum_modulo_results<fifi::prime2325>::m_size =
    dimension_of(sum_modulo_results<fifi::prime2325>::m_results);
