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
struct method
{

    typedef std::function<typename FieldImpl::value_type(
            const FieldImpl&,
            typename FieldImpl::value_type a)> unary;

    typedef std::function<typename FieldImpl::value_type(
            const FieldImpl&,
            typename FieldImpl::value_type a,
            typename FieldImpl::value_type b)> binary;
};

template<class FieldImpl, template<class,int>class Results, int Method>
inline void check_results_binary(typename method<FieldImpl>::binary arithmetic)
{
    typedef typename FieldImpl::field_type field_type;

    FieldImpl field;

    for(uint32_t i = 0; i < Results<field_type, Method>::m_size; ++i)
    {
        expected_result_binary<field_type> res =
            Results<field_type, Method>::m_results[i];

        EXPECT_EQ(arithmetic(field, res.m_input1, res.m_input2), res.m_result);
    }
}

template<class FieldImpl, template<class,int>class Results, int Method>
inline void check_results_buffer(typename method<FieldImpl>::binary arithmetic)
{
    typedef typename FieldImpl::field_type field_type;

    FieldImpl field;

    for(uint32_t i = 0; i < Results<field_type, Method>::m_size; ++i)
    {
        expected_result_binary<field_type> res =
            Results<field_type, Method>::m_results[i];
        assert(0);
        EXPECT_EQ(arithmetic(field, res.m_input1, res.m_input2), res.m_result);
    }
}


template<class FieldImpl, template<class,int>class Results, int Method>
inline void check_results_unary(typename method<FieldImpl>::unary arithmetic)
{
    typedef typename FieldImpl::field_type field_type;

    FieldImpl field;

    for(uint32_t i = 0; i < Results<field_type, Method>::m_size; ++i)
    {
        expected_result_unary<field_type> res =
            Results<field_type, Method>::m_results[i];

        EXPECT_EQ(arithmetic(field, res.m_input1), res.m_result);
    }
}

//------------------------------------------------------------------
// multiply
//------------------------------------------------------------------

/// Definition of the multiply_results struct
template<class Field, int Method = DEFAULT>
struct multiply_results;

template<class FieldImpl>
inline void check_results_multiply()
{
    typename method<FieldImpl>::binary multiply = &FieldImpl::multiply;
    check_results_binary<FieldImpl, multiply_results, DEFAULT>(multiply);
}

template<class FieldImpl>
inline void check_results_packed_multiply()
{
    typename method<FieldImpl>::binary multiply = &FieldImpl::packed_multiply;
    check_results_binary<FieldImpl, multiply_results, PACKED>(multiply);
}

template<class FieldImpl>
inline void check_results_region_multiply()
{
    typename method<FieldImpl>::binary multiply = &FieldImpl::region_multiply;
    check_results_binary<FieldImpl, multiply_results, REGION>(multiply);
}

//------------------------------------------------------------------
// divide
//------------------------------------------------------------------

template<class Field, int Method = DEFAULT>
struct divide_results;

template<class FieldImpl>
inline void check_results_divide()
{
    typename method<FieldImpl>::binary divide = &FieldImpl::divide;
    check_results_binary<FieldImpl, divide_results, DEFAULT>(divide);
}

template<class FieldImpl>
inline void check_results_packed_divide()
{
    typename method<FieldImpl>::binary divide = &FieldImpl::packed_divide;
    check_results_binary<FieldImpl, divide_results, PACKED>(divide);
}

template<class FieldImpl>
inline void check_results_region_divide()
{
    typename method<FieldImpl>::binary divide = &FieldImpl::region_divide;
    check_results_binary<FieldImpl, divide_results, REGION>(divide);
}

//------------------------------------------------------------------
// add
//------------------------------------------------------------------

template<class Field, int Method = DEFAULT>
struct add_results;

template<class FieldImpl>
inline void check_results_add()
{
    typename method<FieldImpl>::binary add = &FieldImpl::add;
    check_results_binary<FieldImpl, add_results, DEFAULT>(add);
}

template<class FieldImpl>
inline void check_results_packed_add()
{
    typename method<FieldImpl>::binary add = &FieldImpl::packed_add;
    check_results_binary<FieldImpl, add_results, PACKED>(add);
}

template<class FieldImpl>
inline void check_results_region_add()
{
    typename method<FieldImpl>::binary add = &FieldImpl::region_add;
    check_results_binary<FieldImpl, add_results, REGION>(add);
}

//------------------------------------------------------------------
// subtract
//------------------------------------------------------------------

template<class Field, int Method = DEFAULT>
struct subtract_results;

template<class FieldImpl>
inline void check_results_subtract()
{
    typename method<FieldImpl>::binary subtract = &FieldImpl::subtract;
    check_results_binary<FieldImpl, subtract_results, DEFAULT>(subtract);
}

template<class FieldImpl>
inline void check_results_packed_subtract()
{
    typename method<FieldImpl>::binary subtract = &FieldImpl::packed_subtract;
    check_results_binary<FieldImpl, subtract_results, PACKED>(subtract);
}

template<class FieldImpl>
inline void check_results_region_subtract()
{
    typename method<FieldImpl>::binary subtract = &FieldImpl::region_subtract;
    check_results_binary<FieldImpl, subtract_results, REGION>(subtract);
}

//------------------------------------------------------------------
// invert
//------------------------------------------------------------------

template<class Field, int Method = DEFAULT>
struct invert_results;

template<class FieldImpl>
inline void check_results_invert()
{
    typename method<FieldImpl>::unary invert = &FieldImpl::invert;
    check_results_unary<FieldImpl, invert_results, DEFAULT>(invert);
}

template<class FieldImpl>
inline void check_results_packed_invert()
{
    typename method<FieldImpl>::unary invert = &FieldImpl::packed_invert;
    check_results_unary<FieldImpl, invert_results, PACKED>(invert);
}

template<class FieldImpl>
inline void check_results_region_invert()
{
    typename method<FieldImpl>::unary invert = &FieldImpl::region_invert;
    check_results_unary<FieldImpl, invert_results, REGION>(invert);
}

//------------------------------------------------------------------
// check_random
//------------------------------------------------------------------

template<class FieldImpl>
inline void check_random(
    uint32_t elements,
    typename method<FieldImpl>::binary multiply,
    typename method<FieldImpl>::binary divide,
    typename method<FieldImpl>::unary invert)
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
    typedef typename method<FieldImpl>::unary unary;
    typedef typename method<FieldImpl>::binary binary;

    binary multiply = &FieldImpl::multiply;
    binary divide = &FieldImpl::divide;
    unary invert = &FieldImpl::invert;
    check_random<FieldImpl>(elements, multiply, divide, invert);
}

template<class FieldImpl>
inline void check_random_packed(uint32_t elements = 100)
{
    typedef typename method<FieldImpl>::unary unary;
    typedef typename method<FieldImpl>::binary binary;

    binary multiply = &FieldImpl::multiply;
    binary divide = &FieldImpl::divide;
    unary invert = &FieldImpl::invert;
    check_random<FieldImpl>(elements, multiply, divide, invert);
}

template<class FieldImpl>
inline void check_random_region(uint32_t elements = 100)
{
    typedef typename method<FieldImpl>::unary unary;
    typedef typename method<FieldImpl>::binary binary;

    binary multiply = &FieldImpl::multiply;
    binary divide = &FieldImpl::divide;
    unary invert = &FieldImpl::invert;
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

/// Specialized structs which contains the packed results for the binary field

template<>
struct multiply_results<fifi::binary, PACKED>
{
    static const expected_result_binary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

template<>
struct divide_results<fifi::binary, PACKED>
{
    static const expected_result_binary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

template<>
struct add_results<fifi::binary, PACKED>
{
    static const expected_result_binary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

template<>
struct subtract_results<fifi::binary, PACKED>
{
    static const expected_result_binary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

template<>
struct invert_results<fifi::binary, PACKED>
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
