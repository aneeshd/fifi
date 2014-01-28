// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdlib>
#include <functional>

#include <fifi/binary.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>
#include <fifi/prime2325.hpp>

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

/// Arithmetic Method
enum arithmetic_method { DEFAULT, PACKED, REGION };

/// Expected results for unary functions i.e. functions taking one
/// argument and producing one output
template<class Field>
struct expected_result_unary
{
    typename Field::value_type m_input1;
    typename Field::value_type m_result;
};

template<class FieldImpl>
using unary_method_type =
    std::function<typename FieldImpl::value_type(
        const FieldImpl&,
        typename FieldImpl::value_type a)>;


/// Expected results for binary functions i.e. functions taking two
/// arguments and producing one output
template<class Field>
struct expected_result_binary
{
    typename Field::value_type m_input1;
    typename Field::value_type m_input2;
    typename Field::value_type m_result;
};

template<class FieldImpl>
using binary_method_type =
    std::function<typename FieldImpl::value_type(
        const FieldImpl&,
        typename FieldImpl::value_type a,
        typename FieldImpl::value_type b)>;

//------------------------------------------------------------------
// multiply
//------------------------------------------------------------------

/// Definition of the multiply_results struct
template<class Field, int Method = DEFAULT>
struct multiply_results;

/// Helper template function which takes a FieldImpl as its
/// template argument and runs its multiply function
template<class FieldImpl, int Method>
inline void check_results_multiply(binary_method_type<FieldImpl> arithmetic)
{
    typedef typename FieldImpl::field_type field_type;

    FieldImpl field;

    for(uint32_t i = 0; i < multiply_results<field_type, Method>::m_size; ++i)
    {
        expected_result_binary<field_type> res =
            multiply_results<field_type, Method>::m_results[i];

        EXPECT_EQ(arithmetic(field, res.m_input1, res.m_input2), res.m_result);
    }
}

template<class FieldImpl>
inline void check_results_multiply()
{
    binary_method_type<FieldImpl> multiply = &FieldImpl::multiply;
    check_results_multiply<FieldImpl, DEFAULT>(multiply);
}

template<class FieldImpl>
inline void check_results_packed_multiply()
{
    binary_method_type<FieldImpl> multiply = &FieldImpl::packed_multiply;
    check_results_multiply<FieldImpl, PACKED>(multiply);
}

template<class FieldImpl>
inline void check_results_region_multiply()
{
    binary_method_type<FieldImpl> multiply = &FieldImpl::region_multiply;
    check_results_multiply<FieldImpl, REGION>(multiply);
}

//------------------------------------------------------------------
// divide
//------------------------------------------------------------------

template<class Field, int Method = DEFAULT>
struct divide_results;

/// Helper template function which takes a FieldImpl as its
/// template argument and runs its divide function
template<class FieldImpl, int Method>
inline void check_results_divide(binary_method_type<FieldImpl> arithmetic)
{
    typedef typename FieldImpl::field_type field_type;

    FieldImpl field;

    for(uint32_t i = 0; i < divide_results<field_type, Method>::m_size; ++i)
    {
        expected_result_binary<field_type> res =
            divide_results<field_type, Method>::m_results[i];
        EXPECT_EQ(arithmetic(field, res.m_input1, res.m_input2), res.m_result);
    }
}

template<class FieldImpl>
inline void check_results_divide()
{
    binary_method_type<FieldImpl> divide = &FieldImpl::divide;
    check_results_divide<FieldImpl, DEFAULT>(divide);
}

template<class FieldImpl>
inline void check_results_packed_divide()
{
    binary_method_type<FieldImpl> divide = &FieldImpl::packed_divide;
    check_results_divide<FieldImpl, PACKED>(divide);
}

template<class FieldImpl>
inline void check_results_region_divide()
{
    binary_method_type<FieldImpl> divide = &FieldImpl::region_divide;
    check_results_divide<FieldImpl, REGION>(divide);
}

//------------------------------------------------------------------
// add
//------------------------------------------------------------------

template<class Field, int Method = DEFAULT>
struct add_results;

/// Helper template function which takes a FieldImpl as its
/// template argument and runs its add function
template<class FieldImpl, int Method>
inline void check_results_add(binary_method_type<FieldImpl> arithmetic)
{
    typedef typename FieldImpl::field_type field_type;

    FieldImpl field;

    for(uint32_t i = 0; i < add_results<field_type, Method>::m_size; ++i)
    {
        expected_result_binary<field_type> res =
            add_results<field_type, Method>::m_results[i];

        EXPECT_EQ(arithmetic(field, res.m_input1, res.m_input2), res.m_result);
    }
}

template<class FieldImpl>
inline void check_results_add()
{
    binary_method_type<FieldImpl> add = &FieldImpl::add;
    check_results_add<FieldImpl, DEFAULT>(add);
}

template<class FieldImpl>
inline void check_results_packed_add()
{
    binary_method_type<FieldImpl> add = &FieldImpl::packed_add;
    check_results_add<FieldImpl, PACKED>(add);
}

template<class FieldImpl>
inline void check_results_region_add()
{
    binary_method_type<FieldImpl> add = &FieldImpl::region_add;
    check_results_add<FieldImpl, REGION>(add);
}

//------------------------------------------------------------------
// subtract
//------------------------------------------------------------------

template<class Field, int Method = DEFAULT>
struct subtract_results;

/// Helper template function which takes a FieldImpl as its
/// template argument and runs its subtract function
template<class FieldImpl, int Method>
inline void check_results_subtract(binary_method_type<FieldImpl> arithmetic)
{
    typedef typename FieldImpl::field_type field_type;

    FieldImpl field;

    for(uint32_t i = 0; i < subtract_results<field_type, Method>::m_size; ++i)
    {
        expected_result_binary<field_type> res =
            subtract_results<field_type, Method>::m_results[i];

        EXPECT_EQ(arithmetic(field, res.m_input1, res.m_input2), res.m_result);
    }
}

template<class FieldImpl>
inline void check_results_subtract()
{
    binary_method_type<FieldImpl> subtract = &FieldImpl::subtract;
    check_results_subtract<FieldImpl, DEFAULT>(subtract);
}

template<class FieldImpl>
inline void check_results_packed_subtract()
{
    binary_method_type<FieldImpl> subtract = &FieldImpl::packed_subtract;
    check_results_subtract<FieldImpl, PACKED>(subtract);
}

template<class FieldImpl>
inline void check_results_region_subtract()
{
    binary_method_type<FieldImpl> subtract = &FieldImpl::region_subtract;
    check_results_subtract<FieldImpl, REGION>(subtract);
}

//------------------------------------------------------------------
// invert
//------------------------------------------------------------------

template<class Field, int Method = DEFAULT>
struct invert_results;

/// Helper template function which takes a FieldImpl as its
/// template argument and runs its invert function
template<class FieldImpl, int Method>
inline void check_results_invert(unary_method_type<FieldImpl> arithmetic)
{
    typedef typename FieldImpl::field_type field_type;

    FieldImpl field;

    for(uint32_t i = 0; i < invert_results<field_type, Method>::m_size; ++i)
    {
        expected_result_unary<field_type> res =
            invert_results<field_type, Method>::m_results[i];

        EXPECT_EQ(arithmetic(field, res.m_input1), res.m_result);
    }
}

template<class FieldImpl>
inline void check_results_invert()
{
    unary_method_type<FieldImpl> invert = &FieldImpl::invert;
    check_results_invert<FieldImpl, DEFAULT>(invert);
}

template<class FieldImpl>
inline void check_results_packed_invert()
{
    unary_method_type<FieldImpl> invert = &FieldImpl::packed_invert;
    check_results_invert<FieldImpl, PACKED>(invert);
}

template<class FieldImpl>
inline void check_results_region_invert()
{
    unary_method_type<FieldImpl> invert = &FieldImpl::region_invert;
    check_results_invert<FieldImpl, REGION>(invert);
}

//------------------------------------------------------------------
// check_random
//------------------------------------------------------------------

template<class FieldImpl>
inline void check_random(
    uint32_t elements,
    binary_method_type<FieldImpl> multiply,
    binary_method_type<FieldImpl> divide,
    unary_method_type<FieldImpl> invert)
{
    typedef typename FieldImpl::field_type field_type;

    FieldImpl field;

    for(uint32_t i = 0; i < elements; ++i)
    {
        typename field_type::value_type v = rand() % field_type::order;

        if(v == 0)
            ++v;
        EXPECT_EQ(multiply(field, v, invert(field, v)), 1U);
        EXPECT_EQ(multiply(field, v, divide(field, 1U, v)), 1U);
    }
}

template<class FieldImpl>
inline void check_random(uint32_t elements = 100)
{
    binary_method_type<FieldImpl> multiply = &FieldImpl::multiply;
    binary_method_type<FieldImpl> divide = &FieldImpl::divide;
    unary_method_type<FieldImpl> invert = &FieldImpl::invert;
    check_random<FieldImpl>(elements, multiply, divide, invert);
}

template<class FieldImpl>
inline void check_random_packed(uint32_t elements = 100)
{

    binary_method_type<FieldImpl> multiply = &FieldImpl::packed_multiply;
    binary_method_type<FieldImpl> divide = &FieldImpl::packed_divide;
    unary_method_type<FieldImpl> invert = &FieldImpl::packed_invert;
    check_random<FieldImpl>(elements, multiply, divide, invert);
}

template<class FieldImpl>
inline void check_random_region(uint32_t elements = 100)
{
    binary_method_type<FieldImpl> multiply = &FieldImpl::region_multiply;
    binary_method_type<FieldImpl> divide = &FieldImpl::region_divide;
    unary_method_type<FieldImpl> invert = &FieldImpl::region_invert;
    check_random<FieldImpl>(elements, multiply, divide, invert);
}

//------------------------------------------------------------------
// binary
//------------------------------------------------------------------

/// Specialized structs which contains the results for the binary field

template<>
struct multiply_results<fifi::binary>
{
    static const expected_result_binary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

template<>
struct divide_results<fifi::binary>
{
    static const expected_result_binary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

template<>
struct add_results<fifi::binary>
{
    static const expected_result_binary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

template<>
struct subtract_results<fifi::binary>
{
    static const expected_result_binary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

template<>
struct invert_results<fifi::binary>
{
    static const expected_result_unary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

//------------------------------------------------------------------
// binary4
//------------------------------------------------------------------

/// Specialized structs which contains the results for the binary4 field

template<>
struct multiply_results<fifi::binary4>
{
    static const expected_result_binary<fifi::binary4> m_results[];
    static const uint32_t m_size;
};

template<>
struct divide_results<fifi::binary4>
{
    static const expected_result_binary<fifi::binary4> m_results[];
    static const uint32_t m_size;
};

template<>
struct add_results<fifi::binary4>
{
    static const expected_result_binary<fifi::binary4> m_results[];
    static const uint32_t m_size;
};

template<>
struct subtract_results<fifi::binary4>
{
    static const expected_result_binary<fifi::binary4> m_results[];
    static const uint32_t m_size;
};

template<>
struct invert_results<fifi::binary4>
{
    static const expected_result_unary<fifi::binary4> m_results[];
    static const uint32_t m_size;
};

//------------------------------------------------------------------
// binary8
//------------------------------------------------------------------

/// Specialized structs which contains the results for the binary8 field

template<>
struct multiply_results<fifi::binary8>
{
    static const expected_result_binary<fifi::binary8> m_results[];
    static const uint32_t m_size;
};

template<>
struct divide_results<fifi::binary8>
{
    static const expected_result_binary<fifi::binary8> m_results[];
    static const uint32_t m_size;
};

template<>
struct add_results<fifi::binary8>
{
    static const expected_result_binary<fifi::binary8> m_results[];
    static const uint32_t m_size;
};

template<>
struct subtract_results<fifi::binary8>
{
    static const expected_result_binary<fifi::binary8> m_results[];
    static const uint32_t m_size;
};

template<>
struct invert_results<fifi::binary8>
{
    static const expected_result_unary<fifi::binary8> m_results[];
    static const uint32_t m_size;
};

//------------------------------------------------------------------
// binary16
//------------------------------------------------------------------

/// Specialized structs which contains the results for the binary16 field

template<>
struct multiply_results<fifi::binary16>
{
    static const expected_result_binary<fifi::binary16> m_results[];
    static const uint32_t m_size;
};

template<>
struct divide_results<fifi::binary16>
{
    static const expected_result_binary<fifi::binary16> m_results[];
    static const uint32_t m_size;
};

template<>
struct add_results<fifi::binary16>
{
    static const expected_result_binary<fifi::binary16> m_results[];
    static const uint32_t m_size;
};

template<>
struct subtract_results<fifi::binary16>
{
    static const expected_result_binary<fifi::binary16> m_results[];
    static const uint32_t m_size;
};

template<>
struct invert_results<fifi::binary16>
{
    static const expected_result_unary<fifi::binary16> m_results[];
    static const uint32_t m_size;
};

//------------------------------------------------------------------
// prime2325
//------------------------------------------------------------------

/// Specialized structs which contains the results for the prime2325 field

template<>
struct multiply_results<fifi::prime2325>
{
    static const expected_result_binary<fifi::prime2325> m_results[];
    static const uint32_t m_size;
};

template<>
struct divide_results<fifi::prime2325>
{
    static const expected_result_binary<fifi::prime2325> m_results[];
    static const uint32_t m_size;
};

template<>
struct add_results<fifi::prime2325>
{
    static const expected_result_binary<fifi::prime2325> m_results[];
    static const uint32_t m_size;
};

template<>
struct subtract_results<fifi::prime2325>
{
    static const expected_result_binary<fifi::prime2325> m_results[];
    static const uint32_t m_size;
};

template<>
struct invert_results<fifi::prime2325>
{
    static const expected_result_unary<fifi::prime2325> m_results[];
    static const uint32_t m_size;
};
