// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <functional>

#include <fifi/fifi_utils.hpp>

#include "random_constant.hpp"
#include "capture_calls.hpp"

namespace fifi
{


    /// @todo Add documentation
    template<class Field>
    struct helper_fall_through
    {

        typedef Field field_type;

        typedef typename Field::value_type value_type;

        value_type add(value_type a, value_type b) const
        {
            m_calls.call_add(a, b);

            auto r = m_constants.value();
            m_calls.return_add(r);

            return r;
        }

        value_type subtract(value_type a, value_type b) const
        {
            m_calls.call_subtract(a, b);

            auto r = m_constants.value();
            m_calls.return_subtract(r);

            return r;
        }

        value_type multiply(value_type a, value_type b) const
        {
            m_calls.call_multiply(a, b);

            auto r = m_constants.value();
            m_calls.return_multiply(r);

            return r;
        }

        value_type divide(value_type numerator,
                          value_type denominator) const
        {
            m_calls.call_divide(numerator, denominator);

            auto r = m_constants.value();
            m_calls.return_divide(r);

            return r;
        }

        value_type invert(value_type a) const
        {
            m_calls.call_invert(a);

            auto r = m_constants.value();
            m_calls.return_invert(r);

            return r;
        }

        value_type packed_add(value_type a, value_type b) const
        {
            m_calls.call_packed_add(a, b);

            auto r = m_constants.pack();
            m_calls.return_packed_add(r);

            return r;
        }

        value_type packed_subtract(value_type a, value_type b) const
        {
            m_calls.call_packed_subtract(a, b);

            auto r = m_constants.pack();
            m_calls.return_packed_subtract(r);

            return r;
        }

        value_type packed_multiply(value_type a, value_type b) const
        {
            m_calls.call_packed_multiply(a, b);

            auto r = m_constants.pack();
            m_calls.return_packed_multiply(r);

            return r;
        }

        value_type packed_divide(value_type numerator,
                                 value_type denominator) const
        {
            m_calls.call_packed_divide(numerator, denominator);

            auto r = m_constants.pack();
            m_calls.return_packed_divide(r);

            return r;
        }

        value_type packed_invert(value_type a) const
        {
            m_calls.call_packed_invert(a);

            auto r = m_constants.pack();
            m_calls.return_packed_invert(r);

            return r;
        }

        void region_add(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            m_calls.call_region_add(dest, src, length);
        }

        void region_subtract(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            m_calls.call_region_subtract(dest, src, length);
        }

        void region_multiply(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            m_calls.call_region_multiply(dest, src, length);
        }

        void region_divide(value_type* dest, const value_type* src,
            uint32_t length) const
        {
            m_calls.call_region_divide(dest, src, length);
        }

        void region_multiply_constant(value_type* dest, value_type constant,
            uint32_t length) const
        {
            m_calls.call_region_multiply_constant(dest, constant, length);
        }

        void region_multiply_add(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            m_calls.call_region_multiply_add(dest, src, constant, length);
        }

        void region_multiply_subtract(value_type* dest, const value_type* src,
            value_type constant, uint32_t length) const
        {
            m_calls.call_region_multiply_subtract(dest, src, constant, length);
        }

        mutable capture_calls<value_type> m_calls;
        mutable random_constant<field_type> m_constants;
    };

    template<class Stack, class Function, class CallFunction, class CallReturn>
    void test_fall_through_value(Function function,
        CallFunction call_function, CallReturn call_return,
        typename Stack::value_type a = 1)
    {
        fifi::capture_calls<typename Stack::value_type> expected_calls;
        Stack s;

        s.m_calls.clear();
        expected_calls.clear();

        call_function(expected_calls, a);

        auto r = function(s, a);

        call_return(expected_calls, r);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack, class Function, class CallFunction, class CallReturn>
    void test_fall_through_value_value(Function function,
        CallFunction call_function, CallReturn call_return,
        typename Stack::value_type a = 1, typename Stack::value_type b = 1)
    {
        fifi::capture_calls<typename Stack::value_type> expected_calls;
        Stack s;

        s.m_calls.clear();
        expected_calls.clear();

        call_function(expected_calls, a, b);

        auto r = function(s, a, b);

        call_return(expected_calls, r);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack, class Function, class CallFunction>
    void test_fall_through_ptr_ptr_length(Function function,
        CallFunction call_function)
    {
        typedef typename Stack::value_type value_type;

        uint32_t length = 10;
        auto dest_vector = std::vector<value_type>(length);
        auto src_vector = std::vector<value_type>(length,
            std::numeric_limits<value_type>::max());

        fifi::capture_calls<value_type> expected_calls;

        Stack s;

        s.m_calls.clear();
        expected_calls.clear();

        call_function(expected_calls, dest_vector.data(), src_vector.data(),
            length);

        function(s, dest_vector.data(), src_vector.data(), length);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack, class Function, class CallFunction>
    void test_fall_through_ptr_ptr_value_length(Function function,
        CallFunction call_function)
    {
        typedef typename Stack::value_type value_type;

        uint32_t length = 10;
        auto dest_vector = std::vector<value_type>(length);
        auto src_vector = std::vector<value_type>(length,
            std::numeric_limits<value_type>::max());
        auto constant = std::numeric_limits<value_type>::max();

        fifi::capture_calls<value_type> expected_calls;

        Stack s;

        s.m_calls.clear();
        expected_calls.clear();

        call_function(expected_calls, dest_vector.data(), src_vector.data(),
            constant, length);

        function(s, dest_vector.data(), src_vector.data(), constant, length);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_add()
    {
        typedef typename fifi::capture_calls<typename Stack::value_type> calls;
        test_fall_through_value_value<Stack>(
            std::mem_fn(&Stack::add),
            std::mem_fn(&calls::call_add),
            std::mem_fn(&calls::return_add));
    }

    template<class Stack>
    void test_fall_through_subtract()
    {
        typedef typename fifi::capture_calls<typename Stack::value_type> calls;
        test_fall_through_value_value<Stack>(
            std::mem_fn(&Stack::subtract),
            std::mem_fn(&calls::call_subtract),
            std::mem_fn(&calls::return_subtract));
    }

    template<class Stack>
    void test_fall_through_multiply()
    {
        typedef typename fifi::capture_calls<typename Stack::value_type> calls;
        test_fall_through_value_value<Stack>(
            std::mem_fn(&Stack::multiply),
            std::mem_fn(&calls::call_multiply),
            std::mem_fn(&calls::return_multiply));
    }

    template<class Stack>
    void test_fall_through_divide()
    {
        typedef typename fifi::capture_calls<typename Stack::value_type> calls;
        test_fall_through_value_value<Stack>(
            std::mem_fn(&Stack::divide),
            std::mem_fn(&calls::call_divide),
            std::mem_fn(&calls::return_divide));
    }

    template<class Stack>
    void test_fall_through_invert()
    {
        typedef typename fifi::capture_calls<typename Stack::value_type> calls;
        test_fall_through_value<Stack>(
            std::mem_fn(&Stack::invert),
            std::mem_fn(&calls::call_invert),
            std::mem_fn(&calls::return_invert));
    }


    template<class Stack>
    void test_fall_through_packed_add()
    {
        typedef typename fifi::capture_calls<typename Stack::value_type> calls;
        test_fall_through_value_value<Stack>(
            std::mem_fn(&Stack::packed_add),
            std::mem_fn(&calls::call_packed_add),
            std::mem_fn(&calls::return_packed_add));
    }

    template<class Stack>
    void test_fall_through_packed_subtract()
    {
        typedef typename fifi::capture_calls<typename Stack::value_type> calls;
        test_fall_through_value_value<Stack>(
            std::mem_fn(&Stack::packed_subtract),
            std::mem_fn(&calls::call_packed_subtract),
            std::mem_fn(&calls::return_packed_subtract));
    }

    template<class Stack>
    void test_fall_through_packed_multiply()
    {
        typedef typename fifi::capture_calls<typename Stack::value_type> calls;
        test_fall_through_value_value<Stack>(
            std::mem_fn(&Stack::packed_multiply),
            std::mem_fn(&calls::call_packed_multiply),
            std::mem_fn(&calls::return_packed_multiply));
    }

    template<class Stack>
    void test_fall_through_packed_divide()
    {
        typedef typename Stack::value_type value_type;
        typedef typename fifi::capture_calls<value_type> calls;
        test_fall_through_value_value<Stack>(
            std::mem_fn(&Stack::packed_divide),
            std::mem_fn(&calls::call_packed_divide),
            std::mem_fn(&calls::return_packed_divide),
            std::numeric_limits<value_type>::max(),
            std::numeric_limits<value_type>::max());
    }

    template<class Stack>
    void test_fall_through_packed_invert()
    {
        typedef typename Stack::value_type value_type;
        typedef typename fifi::capture_calls<value_type> calls;
        test_fall_through_value<Stack>(
            std::mem_fn(&Stack::packed_invert),
            std::mem_fn(&calls::call_packed_invert),
            std::mem_fn(&calls::return_packed_invert),
            std::numeric_limits<value_type>::max());
    }

    template<class Stack>
    void test_fall_through_region_add()
    {
        typedef typename fifi::capture_calls<typename Stack::value_type> calls;
        test_fall_through_ptr_ptr_length<Stack>(
            std::mem_fn(&Stack::region_add),
            std::mem_fn(&calls::call_region_add));
    }

    template<class Stack>
    void test_fall_through_region_subtract()
    {
        typedef typename fifi::capture_calls<typename Stack::value_type> calls;
        test_fall_through_ptr_ptr_length<Stack>(
            std::mem_fn(&Stack::region_subtract),
            std::mem_fn(&calls::call_region_subtract));
    }

    template<class Stack>
    void test_fall_through_region_multiply()
    {
        typedef typename fifi::capture_calls<typename Stack::value_type> calls;
        test_fall_through_ptr_ptr_length<Stack>(
            std::mem_fn(&Stack::region_multiply),
            std::mem_fn(&calls::call_region_multiply));
    }

    template<class Stack>
    void test_fall_through_region_divide()
    {
        typedef typename fifi::capture_calls<typename Stack::value_type> calls;
        test_fall_through_ptr_ptr_length<Stack>(
            std::mem_fn(&Stack::region_divide),
            std::mem_fn(&calls::call_region_divide));
    }

    template<class Stack>
    void test_fall_through_region_multiply_constant()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        uint32_t length = 10;
        auto dest_vector = std::vector<value_type>(length);
        auto constant = fifi::pack<field_type>(1);

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_region_multiply_constant(dest_vector.data(),
            constant, length);

        s.region_multiply_constant(dest_vector.data(), constant, length);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_region_multiply_add()
    {
        typedef typename fifi::capture_calls<typename Stack::value_type> calls;
        test_fall_through_ptr_ptr_value_length<Stack>(
            std::mem_fn(&Stack::region_multiply_add),
            std::mem_fn(&calls::call_region_multiply_add));
    }

    template<class Stack>
    void test_fall_through_region_multiply_subtract()
    {
        typedef typename fifi::capture_calls<typename Stack::value_type> calls;
        test_fall_through_ptr_ptr_value_length<Stack>(
            std::mem_fn(&Stack::region_multiply_subtract),
            std::mem_fn(&calls::call_region_multiply_subtract));
    }

    template<class Stack>
    void test_fall_through()
    {
        test_fall_through_add<Stack>();
        test_fall_through_subtract<Stack>();
        test_fall_through_multiply<Stack>();
        test_fall_through_divide<Stack>();
        test_fall_through_invert<Stack>();
    }

    template<class Stack>
    void test_packed_fall_through()
    {
        test_fall_through_packed_add<Stack>();
        test_fall_through_packed_subtract<Stack>();
        test_fall_through_packed_multiply<Stack>();
        test_fall_through_packed_divide<Stack>();
        test_fall_through_packed_invert<Stack>();
    }

    template<class Stack>
    void test_region_fall_through()
    {
        test_fall_through_region_add<Stack>();
        test_fall_through_region_subtract<Stack>();
        test_fall_through_region_multiply<Stack>();
        test_fall_through_region_divide<Stack>();
        test_fall_through_region_multiply_constant<Stack>();
        test_fall_through_region_multiply_add<Stack>();
        test_fall_through_region_multiply_subtract<Stack>();
    }
}
