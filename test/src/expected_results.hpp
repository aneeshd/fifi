// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <vector>

#include <gtest/gtest.h>

#include <sak/aligned_allocator.hpp>

#include <fifi/binary.hpp>
#include <fifi/binary16.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/fifi_utils.hpp>
#include <fifi/prime2325.hpp>

#include <fifi/simple_online.hpp>

#include "helper_region_reference.hpp"
#include "helper_test_buffer.hpp"

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

template<class FieldImpl, template<class>class Results, class Function>
inline void check_results_binary(Function arithmetic)
{
    typedef typename FieldImpl::field_type field_type;
    FieldImpl field;
    for (uint32_t i = 0; i < Results<field_type>::m_size; ++i)
    {
        auto res = Results<field_type>::m_results[i];
        SCOPED_TRACE(testing::Message() << "a:" << res.m_input1);
        SCOPED_TRACE(testing::Message() << "b:" << res.m_input2);
        EXPECT_EQ(res.m_result, arithmetic(field, res.m_input1,
            res.m_input2));
    }
}

template<class FieldImpl, template<class>class Results, class Function>
inline void check_results_unary(Function arithmetic)
{
    typedef typename FieldImpl::field_type field_type;
    FieldImpl field;
    for (uint32_t i = 0; i < Results<field_type>::m_size; ++i)
    {
        auto res = Results<field_type>::m_results[i];
        SCOPED_TRACE(testing::Message() << "a:" << res.m_input1);
        EXPECT_EQ(res.m_result, arithmetic(field, res.m_input1));
    }
}

template<class FieldImpl, class FunctionUnary, class FunctionBinary>
inline void check_results_random(
    uint32_t elements,
    FunctionBinary multiply,
    FunctionBinary divide,
    FunctionUnary invert)
{
    typedef typename FieldImpl::field_type field_type;

    FieldImpl field;

    for (uint32_t i = 0; i < elements; ++i)
    {
        auto v = rand() % field_type::order;
        if (v == 0)
            ++v;

        EXPECT_EQ(multiply(field, v, invert(field,     v)), 1U);
        EXPECT_EQ(multiply(field, v, divide(field, 1U, v)), 1U);
    }
}

/// This function creates a random buffer of field elements to use for tests.
///
/// @tparam Field The field elements to create.
///
/// @param elements The number of field elements to create.
/// @param no_zero A boolean determining whether the buffer is allowed to
/// contain zero or not.
template<class Field>
fifi::helper_test_buffer<typename Field::value_type> create_data(uint32_t requested_elements,
    uint32_t alignment, uint32_t granularity, bool no_zero = false)
{
    assert((alignment % sizeof(typename Field::value_type)) == 0);
    // make sure the number of elements matches the granularity
    uint32_t length = (fifi::elements_to_length<Field>(requested_elements) /
        granularity) * granularity;

    assert((length % granularity) == 0);

    return fifi::create_random_buffer<Field>(length, alignment, no_zero);
}

/// This function checks whether the region arithmetics for the
/// "dest[i] = dest[i] _OPERATION_ src[i]" function works. Where
/// _OPERATION_ can be addition, subtraction, multiplication or
/// division.
///
/// @tparam TestImpl The stack class to test
/// @tparam ReferenceImpl The reference stack class to test against
/// @tparam TestFunction The function type to be invoked on the test stack. It
/// is assumed that the function takes two arguments; a pointer to the
/// destination buffer and a pointer to the source buffer.
/// @tparam ReferenceFunction The function type to be invoked on the reference
/// stack. It's assumed that the function takes two arguments; a pointer to the
/// destination buffer and a pointer to the source buffer.
///
/// @param test_arithmetic The arithmetic function used to compute the results
/// to test
/// @param reference_arithmetic The arithmetic function used to compute the
/// reference results to test against
/// @param devision A boolean determining whether arithmetic functions are
/// division. This is needed to prevent division by zero errors.
template
<
    class TestImpl, class ReferenceImpl,
    class TestFunction, class ReferenceFunction
>
inline void check_results_region_ptr_ptr(
    TestFunction test_arithmetic,
    ReferenceFunction reference_arithmetic,
    bool division = false)
{
    typedef typename TestImpl::field_type test_field;
    typedef typename ReferenceImpl::field_type reference_field;

    static_assert(std::is_same<test_field, reference_field>::value,
                  "Reference and field under test must use same field");

    TestImpl test_stack;
    ReferenceImpl reference_stack;

    // pick a random number of elementes between 128 and 128+256
    uint32_t elements = 128 + rand() % 256;

    uint32_t alignments = test_stack.max_alignment() + test_stack.alignment();
    uint32_t granularities = test_stack.max_granularity() +
        test_stack.granularity();

    for (uint32_t alignment = test_stack.alignment();
        alignment <= alignments;
        alignment += test_stack.alignment())
    {
        assert((alignment % sizeof(typename test_field::value_type)) == 0);
        for (uint32_t granularity = test_stack.granularity();
            granularity <= granularities;
            granularity += test_stack.granularity())
        {
            SCOPED_TRACE(testing::Message() << "alignment: " << alignment);
            SCOPED_TRACE(testing::Message() << "granularity: " << granularity);
            auto data = create_data<test_field>(elements, alignment,
                granularity);
            auto src = create_data<test_field>(elements, alignment, granularity,
                division);

            uint32_t length = data.length();

            // Create buffer and created the expected results using the
            // reference arithmetics
            auto test_data = data;
            auto reference_data = data;

            // Perform the calculations using the region arithmetics
            test_arithmetic(test_stack, test_data.data(), src.data(), length);
            reference_arithmetic(reference_stack, reference_data.data(),
                src.data(), length);

            EXPECT_EQ(reference_data, test_data);
        }
    }
}

/// This function checks whether the region arithmetics for the
/// "dest[i] = dest[i] _OPERATION_ constant" function works. Where
/// _OPERATION_ is multiplication.
///
/// @tparam TestImpl The stack class to test
/// @tparam ReferenceImpl The reference stack class to test against
/// @tparam TestFunction The function type to be invoked on the test stack. It
/// is assumed that the function takes two arguments; a pointer to the
/// destination buffer and a constant.
/// @tparam ReferenceFunction The function type to be invoked on the reference
/// stack. It's assumed that the function takes two arguments; a pointer to the
/// destination buffer and a constant.
///
/// @param test_arithmetic The arithmetic function used to compute the results
/// to test
/// @param reference_arithmetic The arithmetic function used to compute the
/// reference results to test against
template
<
    class TestImpl, class ReferenceImpl,
    class TestFunction, class ReferenceFunction
>
inline void check_results_region_ptr_const(
    TestFunction test_arithmetic,
    ReferenceFunction reference_arithmetic)
{
    typedef typename TestImpl::field_type test_field;
    typedef typename ReferenceImpl::field_type reference_field;

    static_assert(std::is_same<test_field, reference_field>::value,
                  "Reference and field under test must use same field");

    TestImpl test_stack;
    ReferenceImpl reference_stack;

    // pick a random number of elementes between 128 and 128+256
    uint32_t elements = 128 + rand() % 256;

    uint32_t alignments = test_stack.max_alignment() + test_stack.alignment();
    uint32_t granularities = test_stack.max_granularity() +
        test_stack.granularity();

    for (uint32_t alignment = test_stack.alignment();
        alignment <= alignments;
        alignment += test_stack.alignment())
    {
        assert((alignment % sizeof(typename test_field::value_type)) == 0);
        for (uint32_t granularity = test_stack.granularity();
            granularity <= granularities;
            granularity += test_stack.granularity())
        {
            SCOPED_TRACE(testing::Message() << "alignment: " << alignment);
            SCOPED_TRACE(testing::Message() << "granularity: " << granularity);
            auto data = create_data<test_field>(elements, alignment,
                granularity);

            uint32_t length = data.length();

            // We repeat the test a number of times with different constants
            uint32_t constants = 10;

            for (uint32_t j = 0; j < constants; ++j)
            {
                // Get the constant to multiply with
                auto constant = fifi::pack<test_field>(
                    rand() % test_field::order);
                SCOPED_TRACE(testing::Message() << "constant: " << constant);

                // Create buffer and created the expected results using the
                // reference arithmetics
                auto test_data = data;
                auto reference_data = data;

                // Perform the calculations using the region arithmetics
                test_arithmetic(test_stack, test_data.data(), constant, length);
                reference_arithmetic(reference_stack, reference_data.data(),
                    constant, length);

                EXPECT_EQ(reference_data, test_data);
            }
        }
    }
}

/// This function checks whether the region arithmetics for the
/// "dest[i] = (dest[i] * constant) _OPERATION_ src[i]" function works. Where
/// _OPERATION_ can be addition or subtraction.
///
/// @tparam TestImpl The stack class to test
/// @tparam ReferenceImpl The reference stack class to test against
/// @tparam TestFunction The function type to be invoked on the test stack. It
/// is assumed that the function takes three arguments; a pointer to the
/// destination buffer, a pointer to the source buffer, and a constant.
/// @tparam ReferenceFunction The function type to be invoked on the reference
/// stack. It's assumed that the function takes three arguments; a pointer to
/// the destination buffer, a pointer to the source buffer, and a constant.
///
/// @param test_arithmetic The arithmetic function used to compute the results
/// to test
/// @param reference_arithmetic The arithmetic function used to compute the
/// reference results to test against
template
<
    class TestImpl, class ReferenceImpl,
    class TestFunction, class ReferenceFunction
>
inline void check_results_region_ptr_ptr_const(
    TestFunction test_arithmetic,
    ReferenceFunction reference_arithmetic)
{
    typedef typename TestImpl::field_type test_field;
    typedef typename ReferenceImpl::field_type reference_field;

    static_assert(std::is_same<test_field, reference_field>::value,
                  "Reference and field under test must use same field");

    TestImpl test_stack;
    ReferenceImpl reference_stack;

    // pick a random number of elementes between 128 and 128+256
    uint32_t elements = 128 + rand() % 256;

    uint32_t alignments = test_stack.max_alignment() + test_stack.alignment();
    uint32_t granularities = test_stack.max_granularity() +
        test_stack.granularity();

    for (uint32_t alignment = test_stack.alignment();
        alignment <= alignments;
        alignment += test_stack.alignment())
    {
        assert((alignment % sizeof(typename test_field::value_type)) == 0);
        for (uint32_t granularity = test_stack.granularity();
            granularity <= granularities;
            granularity += test_stack.granularity())
        {
            SCOPED_TRACE(testing::Message() << "alignment: " << alignment);
            SCOPED_TRACE(testing::Message() << "granularity: " << granularity);

            auto data = create_data<test_field>(elements, alignment,
                granularity);
            auto src = create_data<test_field>(elements, alignment,
                granularity);

            uint32_t length = data.length();

            // We repeat the test a number of times with different constants
            uint32_t constants = 10;

            for (uint32_t j = 0; j < constants; ++j)
            {
                // Get the constant to multiply with
                auto constant = fifi::pack<test_field>(
                    rand() % test_field::order);
                SCOPED_TRACE(testing::Message() << "constant: " << constant);

                // Create buffer and created the expected results using the
                // reference arithmetics
                auto test_data = data;
                auto reference_data = data;
                // Perform the calculations using the region arithmetics
                test_arithmetic(test_stack, test_data.data(), src.data(),
                    constant, length);
                reference_arithmetic(reference_stack, reference_data.data(),
                    src.data(), constant, length);

                EXPECT_EQ(reference_data, test_data);
            }
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
        std::mem_fn(&FieldImpl::multiply));
}

template<class FieldImpl>
inline void check_results_packed_multiply()
{
    check_results_binary<FieldImpl, packed_multiply_results>(
        std::mem_fn(&FieldImpl::packed_multiply));
}

template
<
    class TestImpl,
    class ReferenceImpl = fifi::helper_region_reference<
        typename TestImpl::field_type>
>
inline void check_results_region_multiply()
{
    check_results_region_ptr_ptr<TestImpl, ReferenceImpl>(
        std::mem_fn(&TestImpl::region_multiply),
        std::mem_fn(&ReferenceImpl::region_multiply));
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
        std::mem_fn(&FieldImpl::divide));
}

template<class FieldImpl>
inline void check_results_packed_divide()
{
    check_results_binary<FieldImpl, packed_divide_results >(
        std::mem_fn(&FieldImpl::packed_divide));
}

template
<
    class TestImpl,
    class ReferenceImpl = fifi::helper_region_reference<
        typename TestImpl::field_type>
>
inline void check_results_region_divide()
{
    check_results_region_ptr_ptr<TestImpl, ReferenceImpl>(
        std::mem_fn(&TestImpl::region_divide),
        std::mem_fn(&ReferenceImpl::region_divide),
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
    check_results_binary<FieldImpl, add_results>(
        std::mem_fn(&FieldImpl::add));
}

template<class FieldImpl>
inline void check_results_packed_add()
{
    check_results_binary<FieldImpl, packed_add_results>(
        std::mem_fn(&FieldImpl::packed_add));
}

template
<
    class TestImpl,
    class ReferenceImpl = fifi::helper_region_reference<
        typename TestImpl::field_type>
>
inline void check_results_region_add()
{
    check_results_region_ptr_ptr<TestImpl, ReferenceImpl>(
        std::mem_fn(&TestImpl::region_add),
        std::mem_fn(&ReferenceImpl::region_add));
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
        std::mem_fn(&FieldImpl::subtract));
}

template<class FieldImpl>
inline void check_results_packed_subtract()
{
    check_results_binary<FieldImpl, packed_subtract_results>(
        std::mem_fn(&FieldImpl::packed_subtract));
}

template
<
    class TestImpl,
    class ReferenceImpl = fifi::helper_region_reference<
        typename TestImpl::field_type>
>
inline void check_results_region_subtract()
{
    check_results_region_ptr_ptr<TestImpl, ReferenceImpl>(
        std::mem_fn(&TestImpl::region_subtract),
        std::mem_fn(&ReferenceImpl::region_subtract));
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
    check_results_unary<FieldImpl, invert_results>(
        std::mem_fn(&FieldImpl::invert));
}

template<class FieldImpl>
inline void check_results_packed_invert()
{
    check_results_unary<FieldImpl, packed_invert_results>(
        std::mem_fn(&FieldImpl::packed_invert));
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
        std::mem_fn(&FieldImpl::find_degree));
}

//------------------------------------------------------------------
// sum_modulo
//------------------------------------------------------------------

template<class Field>
struct sum_modulo_results;

//------------------------------------------------------------------
// multiply constant
//------------------------------------------------------------------

template
<
    class TestImpl,
    class ReferenceImpl = fifi::helper_region_reference<
        typename TestImpl::field_type>
>
inline void check_results_region_multiply_constant()
{
    check_results_region_ptr_const<TestImpl, ReferenceImpl>(
        std::mem_fn(&TestImpl::region_multiply_constant),
        std::mem_fn(&ReferenceImpl::region_multiply_constant));
}

//------------------------------------------------------------------
// multiply add
//------------------------------------------------------------------

template
<
    class TestImpl,
    class ReferenceImpl = fifi::helper_region_reference<
        typename TestImpl::field_type>
>
inline void check_results_region_multiply_add()
{
    check_results_region_ptr_ptr_const<TestImpl, ReferenceImpl>(
        std::mem_fn(&TestImpl::region_multiply_add),
        std::mem_fn(&ReferenceImpl::region_multiply_add));
}

//------------------------------------------------------------------
// multiply subtract
//------------------------------------------------------------------

template
<
    class TestImpl,
    class ReferenceImpl = fifi::helper_region_reference<
        typename TestImpl::field_type>
>
inline void check_results_region_multiply_subtract()
{
    check_results_region_ptr_ptr_const<TestImpl, ReferenceImpl>(
        std::mem_fn(&TestImpl::region_multiply_subtract),
        std::mem_fn(&ReferenceImpl::region_multiply_subtract));
}

//------------------------------------------------------------------
// check random
//------------------------------------------------------------------

template<class FieldImpl>
inline void check_random_default(uint32_t elements = 100)
{
    check_results_random<FieldImpl>(
        elements,
        std::mem_fn(&FieldImpl::multiply),
        std::mem_fn(&FieldImpl::divide),
        std::mem_fn(&FieldImpl::invert));
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
