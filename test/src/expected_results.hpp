// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdlib>
#include <functional>
#include <vector>

#include <gtest/gtest.h>

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/fifi_utils.hpp>
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

    typedef typename FieldImpl::value_type (FieldImpl::*binary)(
        typename FieldImpl::value_type a,
        typename FieldImpl::value_type b) const;

    typedef std::function<void(
            const FieldImpl&,
                  typename FieldImpl::value_type* a,
            const typename FieldImpl::value_type* b)> binary_ptr_ptr;

    typedef std::function<void(
            const FieldImpl&,
            typename FieldImpl::value_type* a,
            typename FieldImpl::value_type b)> binary_ptr_const;

    typedef std::function<void(
            const FieldImpl&,
            typename FieldImpl::value_type* a,
            typename FieldImpl::value_type* b,
            typename FieldImpl::value_type  c)> binary_ptr_ptr_const;
};

template<class FieldImpl, template<class>class Results>
inline void check_results_binary(typename method<FieldImpl>::binary arithmetic)
{
    typedef typename FieldImpl::field_type field_type;
    FieldImpl field;
    for(uint32_t i = 0; i < Results<field_type>::m_size; ++i)
    {
        expected_result_binary<field_type> res =
            Results<field_type>::m_results[i];
        SCOPED_TRACE("a:");
        SCOPED_TRACE(res.m_input1);
        SCOPED_TRACE("b:");
        SCOPED_TRACE(res.m_input2);
        EXPECT_EQ(res.m_result, (field.*arithmetic)(res.m_input1, res.m_input2));
    }
}

template<class FieldImpl, template<class>class Results>
inline void check_results_unary(typename method<FieldImpl>::unary arithmetic)
{
    typedef typename FieldImpl::field_type field_type;

    FieldImpl field;

    for(uint32_t i = 0; i < Results<field_type>::m_size; ++i)
    {
        expected_result_unary<field_type> res =
            Results<field_type>::m_results[i];
        SCOPED_TRACE("a:");
        SCOPED_TRACE(res.m_input1);
        EXPECT_EQ(res.m_result, arithmetic(field, res.m_input1));
    }
}

template<class FieldImpl>
inline void check_results_random(
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
inline void check_results_region_ptr_ptr(
    typename method<FieldImpl>::binary packed_arithmetic,
    typename method<FieldImpl>::binary_ptr_ptr region_arithmetic,
    uint32_t elements,
    bool divison = false)
{
    typedef typename FieldImpl::field_type field_type;
    typedef typename field_type::value_type value_type;

    uint32_t length = fifi::elements_to_length<field_type>(elements);

    FieldImpl field;
    field.set_length(length);

    std::vector<value_type> dest(length);
    std::vector<value_type> src(length);

    for (uint32_t i = 0; i < elements; ++i)
    {
        value_type v1 = rand() % field_type::order;
        value_type v2 = rand() % field_type::order;

        if (divison && v2 == 0)
        {
            v2++;
        }
        fifi::set_value<field_type>(dest.data(), i, v1);
        fifi::set_value<field_type>(src.data(), i, v2);
    }

    std::vector<value_type> expected(length);
    for (uint32_t i = 0; i < length; ++i)
    {
        expected[i] = packed_arithmetic(field, dest[i], src[i]);
    }

    region_arithmetic(field, dest.data(), src.data());

    for (uint32_t i = 0; i < length; ++i)
    {
        EXPECT_EQ(expected[i], dest[i]);
    }
}

#include <iostream>

template<class FieldImpl>
inline void check_results_region_ptr_const(
    typename method<FieldImpl>::binary packed_arithmetic,
    typename method<FieldImpl>::binary_ptr_const region_arithmetic,
    uint32_t elements)
{
    typedef typename FieldImpl::field_type field_type;
    typedef typename field_type::value_type value_type;

    uint32_t length = fifi::elements_to_length<field_type>(elements);

    FieldImpl field;
    field.set_length(length);

    std::vector<value_type> data(length);
    for (uint32_t i = 0; i < elements; ++i)
    {
        fifi::set_value<field_type>(data.data(), i, rand() % field_type::order);
    }

    uint32_t tests = 10;

    for (uint32_t i = 0; i < tests; ++i)
    {
        value_type constant = fifi::pack<field_type>(rand() % field_type::order);
        SCOPED_TRACE("constant:");
        SCOPED_TRACE(constant);

        std::vector<value_type> dest = data;

        std::vector<value_type> expected(length);
        for (uint32_t j = 0; j < length; ++j)
        {
            expected[j] = packed_arithmetic(field, dest[j], constant);
        }

        region_arithmetic(field, dest.data(), constant);
        for (uint32_t j = 0; j < length; ++j)
        {
            EXPECT_EQ(expected[j], dest[j]);
        }
    }
}

template<class FieldImpl>
inline void check_results_region_ptr_ptr_const(
    typename method<FieldImpl>::binary packed_arithmetic1,
    typename method<FieldImpl>::binary packed_arithmetic2,
    typename method<FieldImpl>::binary_ptr_ptr_const region_arithmetic,
    uint32_t elements)
{
    typedef typename FieldImpl::field_type field_type;
    typedef typename field_type::value_type value_type;

    uint32_t length = fifi::elements_to_length<field_type>(elements);

    FieldImpl field;
    field.set_length(length);

    std::vector<value_type> data(length);
    std::vector<value_type> src(length);

    for (uint32_t i = 0; i < elements; ++i)
    {
        fifi::set_value<field_type>(data.data(), i, rand() % field_type::order);
        fifi::set_value<field_type>(src.data(), i, rand() % field_type::order);
    }

    uint32_t tests = 10;

    for (uint32_t i = 0; i < tests; ++i)
    {
        value_type constant = fifi::pack<field_type>(rand() % field_type::order);

        SCOPED_TRACE("constant:");
        SCOPED_TRACE(constant);

        std::vector<value_type> dest = data;

        std::vector<value_type> expected(length);
        for (uint32_t j = 0; j < length; ++j)
        {
            value_type v = packed_arithmetic1(field, src[j], constant);
            expected[j] = packed_arithmetic2(field, dest[j], v);
        }

        region_arithmetic(field, dest.data(), src.data(), constant);
        for (uint32_t j = 0; j < length; ++j)
        {
            EXPECT_EQ(expected[j], dest[j]);
        }
    }
}

//------------------------------------------------------------------
// multiply
//------------------------------------------------------------------

/// Definition of the multiply_results struct
template<class Field>
struct multiply_results;

template<class Field>
struct packed_multiply_results;

template<class FieldImpl>
inline void check_results_multiply()
{
    check_results_binary<FieldImpl, multiply_results>(
        &FieldImpl::multiply);
}

template<class FieldImpl>
inline void check_results_packed_multiply()
{
    check_results_binary<FieldImpl, packed_multiply_results>(
        &FieldImpl::packed_multiply);
}

template<class FieldImpl>
inline void check_results_region_multiply(uint32_t elements = 128)
{
    check_results_region_ptr_ptr<FieldImpl>(
        &FieldImpl::packed_multiply,
        &FieldImpl::region_multiply,
        elements);
}

//------------------------------------------------------------------
// divide
//------------------------------------------------------------------

template<class Field>
struct divide_results;

template<class Field>
struct packed_divide_results;

template<class FieldImpl>
inline void check_results_divide()
{
    check_results_binary<FieldImpl, divide_results >(
        &FieldImpl::divide);
}

template<class FieldImpl>
inline void check_results_packed_divide()
{
    check_results_binary<FieldImpl, packed_divide_results >(
        &FieldImpl::packed_divide);
}

template<class FieldImpl>
inline void check_results_region_divide(uint32_t elements = 128)
{
    check_results_region_ptr_ptr<FieldImpl>(
        &FieldImpl::packed_divide,
        &FieldImpl::region_divide,
        elements,
        true);
}

//------------------------------------------------------------------
// add
//------------------------------------------------------------------

template<class Field>
struct add_results;

template<class Field>
struct packed_add_results;

template<class FieldImpl>
inline void check_results_add()
{
    check_results_binary<FieldImpl, add_results>(&FieldImpl::add);
}

template<class FieldImpl>
inline void check_results_packed_add()
{
    check_results_binary<FieldImpl, packed_add_results>(
        &FieldImpl::packed_add);
}

template<class FieldImpl>
inline void check_results_region_add(uint32_t elements = 128)
{
    check_results_region_ptr_ptr<FieldImpl>(
        &FieldImpl::packed_add,
        &FieldImpl::region_add,
        elements);
}

//------------------------------------------------------------------
// subtract
//------------------------------------------------------------------

template<class Field>
struct subtract_results;

template<class Field>
struct packed_subtract_results;

template<class FieldImpl>
inline void check_results_subtract()
{
    check_results_binary<FieldImpl, subtract_results>(
        &FieldImpl::subtract);
}

template<class FieldImpl>
inline void check_results_packed_subtract()
{
    check_results_binary<FieldImpl, packed_subtract_results>(
        &FieldImpl::packed_subtract);
}

template<class FieldImpl>
inline void check_results_region_subtract(uint32_t elements = 128)
{
    check_results_region_ptr_ptr<FieldImpl >(
        &FieldImpl::packed_subtract,
        &FieldImpl::region_subtract,
        elements);
}

//------------------------------------------------------------------
// invert
//------------------------------------------------------------------

template<class Field>
struct invert_results;

template<class Field>
struct packed_invert_results;

template<class FieldImpl>
inline void check_results_invert()
{
    check_results_unary<FieldImpl, invert_results>(&FieldImpl::invert);
}

template<class FieldImpl>
inline void check_results_packed_invert()
{
    check_results_unary<FieldImpl, packed_invert_results>(
        &FieldImpl::packed_invert);
}

//------------------------------------------------------------------
// find degree
//------------------------------------------------------------------

template<class Field>
struct find_degree_results;

template<class FieldImpl>
inline void check_results_find_degree()
{
    check_results_unary<FieldImpl, find_degree_results>(
        &FieldImpl::find_degree);
}

//------------------------------------------------------------------
// sum modulo
//------------------------------------------------------------------

template<class Field>
struct sum_modulo_results;

template<class FieldImpl>
inline void check_results_sum_modulo()
{
    check_results_binary<FieldImpl, sum_modulo_results>(
        typename method<FieldImpl>::binary(&FieldImpl::template calculate_sum_modulo<>));
}

//------------------------------------------------------------------
// multiply constant
//------------------------------------------------------------------

template<class FieldImpl>
inline void check_results_region_multiply_constant(uint32_t elements = 128)
{
    check_results_region_ptr_const<FieldImpl>(
        &FieldImpl::packed_multiply,
        &FieldImpl::region_multiply_constant,
        elements);
}

//------------------------------------------------------------------
// multiply add
//------------------------------------------------------------------

template<class FieldImpl>
inline void check_results_region_multiply_add(uint32_t elements = 128)
{
    check_results_region_ptr_ptr_const<FieldImpl>(
        &FieldImpl::packed_multiply,
        &FieldImpl::packed_add,
        &FieldImpl::region_multiply_add,
        elements);
}

//------------------------------------------------------------------
// multiply subtract
//------------------------------------------------------------------

template<class FieldImpl>
inline void check_results_region_multiply_subtract(uint32_t elements = 128)
{
    check_results_region_ptr_ptr_const<FieldImpl>(
        &FieldImpl::packed_multiply,
        &FieldImpl::packed_subtract,
        &FieldImpl::region_multiply_subtract,
        elements);
}

//------------------------------------------------------------------
// check random
//------------------------------------------------------------------

template<class FieldImpl>
inline void check_random_default(uint32_t elements = 100)
{
    check_results_random<FieldImpl>(
        elements,
        &FieldImpl::multiply,
        &FieldImpl::divide,
        &FieldImpl::invert);
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
struct subtract_results<fifi::binary> : add_results<fifi::binary>
{ };

template<>
struct invert_results<fifi::binary>
{
    static const expected_result_unary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

template<>
struct find_degree_results<fifi::binary>
{
    static const expected_result_unary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

template<>
struct sum_modulo_results<fifi::binary>
{
    static const expected_result_binary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

/// Specialized structs which contains the packed results for the binary field

template<>
struct packed_multiply_results<fifi::binary>
{
    static const expected_result_binary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

template<>
struct packed_divide_results<fifi::binary>
{
    static const expected_result_binary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

template<>
struct packed_add_results<fifi::binary>
{
    static const expected_result_binary<fifi::binary> m_results[];
    static const uint32_t m_size;
};

template<>
struct packed_subtract_results<fifi::binary> : packed_add_results<fifi::binary>
{ };

template<>
struct packed_invert_results<fifi::binary>
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
struct subtract_results<fifi::binary4> : add_results<fifi::binary4>
{ };

template<>
struct invert_results<fifi::binary4>
{
    static const expected_result_unary<fifi::binary4> m_results[];
    static const uint32_t m_size;
};

template<>
struct find_degree_results<fifi::binary4>
{
    static const expected_result_unary<fifi::binary4> m_results[];
    static const uint32_t m_size;
};

template<>
struct sum_modulo_results<fifi::binary4>
{
    static const expected_result_binary<fifi::binary4> m_results[];
    static const uint32_t m_size;
};

/// Specialized structs which contains the packed results for the binary4 field

template<>
struct packed_multiply_results<fifi::binary4>
{
    static const expected_result_binary<fifi::binary4> m_results[];
    static const uint32_t m_size;
};

template<>
struct packed_divide_results<fifi::binary4>
{
    static const expected_result_binary<fifi::binary4> m_results[];
    static const uint32_t m_size;
};

template<>
struct packed_add_results<fifi::binary4>
{
    static const expected_result_binary<fifi::binary4> m_results[];
    static const uint32_t m_size;
};


// add and subtract is the same for this field.
template<>
struct packed_subtract_results<fifi::binary4> :
    packed_add_results<fifi::binary4>
{ };

template<>
struct packed_invert_results<fifi::binary4>
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
struct subtract_results<fifi::binary8> : add_results<fifi::binary8>
{ };

template<>
struct invert_results<fifi::binary8>
{
    static const expected_result_unary<fifi::binary8> m_results[];
    static const uint32_t m_size;
};

template<>
struct find_degree_results<fifi::binary8>
{
    static const expected_result_unary<fifi::binary8> m_results[];
    static const uint32_t m_size;
};

template<>
struct sum_modulo_results<fifi::binary8>
{
    static const expected_result_binary<fifi::binary8> m_results[];
    static const uint32_t m_size;
};

/// Specialized structs which contains the packed results for the binary8 field

template<>
struct packed_multiply_results<fifi::binary8>
    : public multiply_results<fifi::binary8>
{ };

template<>
struct packed_divide_results<fifi::binary8>
    : public divide_results<fifi::binary8>
{ };

template<>
struct packed_add_results<fifi::binary8>
    : public add_results<fifi::binary8>
{ };

template<>
struct packed_subtract_results<fifi::binary8>
    : public packed_add_results<fifi::binary8>
{ };

template<>
struct packed_invert_results<fifi::binary8>
    : public invert_results<fifi::binary8>
{ };

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
struct subtract_results<fifi::binary16> : add_results<fifi::binary16>
{ };

template<>
struct invert_results<fifi::binary16>
{
    static const expected_result_unary<fifi::binary16> m_results[];
    static const uint32_t m_size;
};

template<>
struct find_degree_results<fifi::binary16>
{
    static const expected_result_unary<fifi::binary16> m_results[];
    static const uint32_t m_size;
};

template<>
struct sum_modulo_results<fifi::binary16>
{
    static const expected_result_binary<fifi::binary16> m_results[];
    static const uint32_t m_size;
};

/// Specialized structs which contains the packed results for the binary16 field

template<>
struct packed_multiply_results<fifi::binary16>
    : public multiply_results<fifi::binary16>
{ };

template<>
struct packed_divide_results<fifi::binary16>
    : public divide_results<fifi::binary16>
{ };

template<>
struct packed_add_results<fifi::binary16>
    : public add_results<fifi::binary16>
{ };

template<>
struct packed_subtract_results<fifi::binary16>
    : public packed_add_results<fifi::binary16>
{ };

template<>
struct packed_invert_results<fifi::binary16>
    : public invert_results<fifi::binary16>
{ };

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

template<>
struct find_degree_results<fifi::prime2325>
{
    static const expected_result_unary<fifi::prime2325> m_results[];
    static const uint32_t m_size;
};

template<>
struct sum_modulo_results<fifi::prime2325>
{
    static const expected_result_binary<fifi::prime2325> m_results[];
    static const uint32_t m_size;
};

/// Specialized structs which contains the packed results for the prime2325 field

template<>
struct packed_multiply_results<fifi::prime2325>
    : public multiply_results<fifi::prime2325>
{ };

template<>
struct packed_divide_results<fifi::prime2325>
    : public divide_results<fifi::prime2325>
{ };

template<>
struct packed_add_results<fifi::prime2325>
    : public add_results<fifi::prime2325>
{ };

template<>
struct packed_subtract_results<fifi::prime2325>
    : public subtract_results<fifi::prime2325>
{ };

template<>
struct packed_invert_results<fifi::prime2325>
    : public invert_results<fifi::prime2325>
{ };
