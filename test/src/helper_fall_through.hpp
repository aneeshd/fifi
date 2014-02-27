// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <tuple>

#include <fifi/fifi_utils.hpp>

#include "helper_random_constant.hpp"

namespace fifi
{
    template<class ValueType>
    struct capture_calls
    {
        typedef std::tuple<ValueType> args1;
        typedef std::tuple<ValueType, ValueType> args2;
        typedef std::tuple<ValueType*, const ValueType*, uint32_t> args3;
        typedef std::tuple<ValueType*, ValueType, uint32_t> args4;
        typedef std::tuple<ValueType*, const ValueType*, ValueType, uint32_t>
            args5;

        std::vector<args2> m_call_add;
        std::vector<args2> m_call_subtract;
        std::vector<args2> m_call_multiply;
        std::vector<args2> m_call_divide;
        std::vector<args1> m_call_invert;

        std::vector<args1> m_return_add;
        std::vector<args1> m_return_subtract;
        std::vector<args1> m_return_multiply;
        std::vector<args1> m_return_divide;
        std::vector<args1> m_return_invert;

        std::vector<args2> m_call_packed_add;
        std::vector<args2> m_call_packed_subtract;
        std::vector<args2> m_call_packed_multiply;
        std::vector<args2> m_call_packed_divide;
        std::vector<args1> m_call_packed_invert;

        std::vector<args1> m_return_packed_add;
        std::vector<args1> m_return_packed_subtract;
        std::vector<args1> m_return_packed_multiply;
        std::vector<args1> m_return_packed_divide;
        std::vector<args1> m_return_packed_invert;


        std::vector<args3> m_call_region_add;
        std::vector<args3> m_call_region_subtract;
        std::vector<args3> m_call_region_multiply;
        std::vector<args3> m_call_region_divide;
        std::vector<args4> m_call_region_multiply_constant;
        std::vector<args5> m_call_region_multiply_add;
        std::vector<args5> m_call_region_multiply_subtract;

        template <class... Args>
        void call_add(Args&&... args)
        {
            m_call_add.emplace_back(args...);
        }

        template <class... Args>
        void call_subtract(Args&&... args)
        {
            m_call_subtract.emplace_back(args...);
        }

        template <class... Args>
        void call_multiply(Args&&... args)
        {
            m_call_multiply.emplace_back(args...);
        }

        template <class... Args>
        void call_divide(Args&&... args)
        {
            m_call_divide.emplace_back(args...);
        }

        template <class... Args>
        void call_invert(Args&&... args)
        {
            m_call_invert.emplace_back(args...);
        }

        template <class... Args>
        void return_add(Args&&... args)
        {
            m_return_add.emplace_back(args...);
        }

        template <class... Args>
        void return_subtract(Args&&... args)
        {
            m_return_subtract.emplace_back(args...);
        }

        template <class... Args>
        void return_multiply(Args&&... args)
        {
            m_return_multiply.emplace_back(args...);
        }

        template <class... Args>
        void return_divide(Args&&... args)
        {
            m_return_divide.emplace_back(args...);
        }

        template <class... Args>
        void return_invert(Args&&... args)
        {
            m_return_invert.emplace_back(args...);
        }

        template <class... Args>
        void call_packed_add(Args&&... args)
        {
            m_call_packed_add.emplace_back(args...);
        }

        template <class... Args>
        void call_packed_subtract(Args&&... args)
        {
            m_call_packed_subtract.emplace_back(args...);
        }

        template <class... Args>
        void call_packed_multiply(Args&&... args)
        {
            m_call_packed_multiply.emplace_back(args...);
        }

        template <class... Args>
        void call_packed_divide(Args&&... args)
        {
            m_call_packed_divide.emplace_back(args...);
        }

        template <class... Args>
        void call_packed_invert(Args&&... args)
        {
            m_call_packed_invert.emplace_back(args...);
        }

        template <class... Args>
        void return_packed_add(Args&&... args)
        {
            m_return_packed_add.emplace_back(args...);
        }

        template <class... Args>
        void return_packed_subtract(Args&&... args)
        {
            m_return_packed_subtract.emplace_back(args...);
        }

        template <class... Args>
        void return_packed_multiply(Args&&... args)
        {
            m_return_packed_multiply.emplace_back(args...);
        }

        template <class... Args>
        void return_packed_divide(Args&&... args)
        {
            m_return_packed_divide.emplace_back(args...);
        }

        template <class... Args>
        void return_packed_invert(Args&&... args)
        {
            m_return_packed_invert.emplace_back(args...);
        }

        template <class... Args>
        void call_region_add(Args&&... args)
        {
            m_call_region_add.emplace_back(args...);
        }

        template <class... Args>
        void call_region_subtract(Args&&... args)
        {
            m_call_region_subtract.emplace_back(args...);
        }

        template <class... Args>
        void call_region_multiply(Args&&... args)
        {
            m_call_region_multiply.emplace_back(args...);
        }

        template <class... Args>
        void call_region_divide(Args&&... args)
        {
            m_call_region_divide.emplace_back(args...);
        }

        template <class... Args>
        void call_region_multiply_constant(Args&&... args)
        {
            m_call_region_multiply_constant.emplace_back(args...);
        }

        template <class... Args>
        void call_region_multiply_add(Args&&... args)
        {
            m_call_region_multiply_add.emplace_back(args...);
        }

        template <class... Args>
        void call_region_multiply_subtract(Args&&... args)
        {
            m_call_region_multiply_subtract.emplace_back(args...);
        }

        void clear()
        {

            m_call_add.clear();
            m_call_subtract.clear();
            m_call_multiply.clear();
            m_call_divide.clear();
            m_call_invert.clear();


            m_return_add.clear();
            m_return_subtract.clear();
            m_return_multiply.clear();
            m_return_divide.clear();
            m_return_invert.clear();


            m_call_packed_add.clear();
            m_call_packed_subtract.clear();
            m_call_packed_multiply.clear();
            m_call_packed_divide.clear();
            m_call_packed_invert.clear();

            m_return_packed_add.clear();
            m_return_packed_subtract.clear();
            m_return_packed_multiply.clear();
            m_return_packed_divide.clear();
            m_return_packed_invert.clear();

            m_call_region_add.clear();
            m_call_region_subtract.clear();
            m_call_region_multiply.clear();
            m_call_region_divide.clear();
            m_call_region_multiply_constant.clear();
            m_call_region_multiply_add.clear();
            m_call_region_multiply_subtract.clear();
        }
    };


    template<class ValueType>
    inline bool operator==(const capture_calls<ValueType>& a,
                           const capture_calls<ValueType>& b)
    {
        if (a.m_call_add != b.m_call_add)
            return false;

        if (a.m_call_subtract != b.m_call_subtract)
            return false;

        if (a.m_call_multiply != b.m_call_multiply)
            return false;

        if (a.m_call_divide != b.m_call_divide)
            return false;

        if (a.m_call_invert != b.m_call_invert)
            return false;

        if (a.m_return_add != b.m_return_add)
            return false;

        if (a.m_return_subtract != b.m_return_subtract)
            return false;

        if (a.m_return_multiply != b.m_return_multiply)
            return false;

        if (a.m_return_divide != b.m_return_divide)
            return false;

        if (a.m_return_invert != b.m_return_invert)
            return false;

        if (a.m_call_packed_add != b.m_call_packed_add)
            return false;

        if (a.m_call_packed_subtract != b.m_call_packed_subtract)
            return false;

        if (a.m_call_packed_multiply != b.m_call_packed_multiply)
            return false;

        if (a.m_call_packed_divide != b.m_call_packed_divide)
            return false;

        if (a.m_call_packed_invert != b.m_call_packed_invert)
            return false;

        if (a.m_return_packed_add != b.m_return_packed_add)
            return false;

        if (a.m_return_packed_subtract != b.m_return_packed_subtract)
            return false;

        if (a.m_return_packed_multiply != b.m_return_packed_multiply)
            return false;

        if (a.m_return_packed_divide != b.m_return_packed_divide)
            return false;

        if (a.m_return_packed_invert != b.m_return_packed_invert)
            return false;

        if (a.m_call_region_add != b.m_call_region_add)
            return false;

        if (a.m_call_region_subtract != b.m_call_region_subtract)
            return false;

        if (a.m_call_region_multiply != b.m_call_region_multiply)
            return false;

        if (a.m_call_region_divide != b.m_call_region_divide)
            return false;

        if (a.m_call_region_multiply_constant != b.m_call_region_multiply_constant)
            return false;

        if (a.m_call_region_multiply_add != b.m_call_region_multiply_add)
            return false;

        if (a.m_call_region_multiply_subtract != b.m_call_region_multiply_subtract)
            return false;

        return true;

    }

    template<class ValueType>
    inline std::ostream& operator<<(std::ostream& out,
                                    const capture_calls<ValueType>& calls)
    {
        out << std::endl;


        out << "\tcall m_call_add:" << std::endl;
        for(const auto& v : calls.m_call_add)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }
        out << "\tcall m_call_subtract:" << std::endl;
        for(const auto& v : calls.m_call_subtract)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }
        out << "\tcall m_call_multiply:" << std::endl;
        for(const auto& v : calls.m_call_multiply)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }
        out << "\tcall m_call_divide:" << std::endl;
        for(const auto& v : calls.m_call_divide)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }
        out << "\tcall m_call_invert:" << std::endl;
        for(const auto& v : calls.m_call_invert)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }


        out << "\tcall m_return_add:" << std::endl;
        for(const auto& v : calls.m_return_add)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }
        out << "\tcall m_return_subtract:" << std::endl;
        for(const auto& v : calls.m_return_subtract)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }
        out << "\tcall m_return_multiply:" << std::endl;
        for(const auto& v : calls.m_return_multiply)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }
        out << "\tcall m_return_divide:" << std::endl;
        for(const auto& v : calls.m_return_divide)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }
        out << "\tcall m_return_invert:" << std::endl;
        for(const auto& v : calls.m_return_invert)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }

        // Packed

        out << "\tcall m_call_packed_add:" << std::endl;
        for(const auto& v : calls.m_call_packed_add)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }
        out << "\tcall m_call_packed_subtract:" << std::endl;
        for(const auto& v : calls.m_call_packed_subtract)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }
        out << "\tcall m_call_packed_multiply:" << std::endl;
        for(const auto& v : calls.m_call_packed_multiply)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }
        out << "\tcall m_call_packed_divide:" << std::endl;
        for(const auto& v : calls.m_call_packed_divide)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }
        out << "\tcall m_call_packed_invert:" << std::endl;
        for(const auto& v : calls.m_call_packed_invert)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }


        out << "\tcall m_return_packed_add:" << std::endl;
        for(const auto& v : calls.m_return_packed_add)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }
        out << "\tcall m_return_packed_subtract:" << std::endl;
        for(const auto& v : calls.m_return_packed_subtract)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }
        out << "\tcall m_return_packed_multiply:" << std::endl;
        for(const auto& v : calls.m_return_packed_multiply)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }
        out << "\tcall m_return_packed_divide:" << std::endl;
        for(const auto& v : calls.m_return_packed_divide)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }
        out << "\tcall m_return_packed_invert:" << std::endl;
        for(const auto& v : calls.m_return_packed_invert)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }

        // Region

        out << "\tcall m_call_region_add:" << std::endl;
        for(const auto& v : calls.m_call_region_add)
        {
            out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
                << " src = " << ((uintptr_t) std::get<1>(v))
                << " length = " << ((uint32_t) std::get<2>(v)) << std::endl;
        }
        out << "\tcall m_call_region_subtract:" << std::endl;
        for(const auto& v : calls.m_call_region_subtract)
        {
            out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
                << " src = " << ((uintptr_t) std::get<1>(v))
                << " length = " << ((uint32_t) std::get<2>(v)) << std::endl;
        }
        out << "\tcall m_call_region_multiply:" << std::endl;
        for(const auto& v : calls.m_call_region_multiply)
        {
            out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
                << " src = " << ((uintptr_t) std::get<1>(v))
                << " length = " << ((uint32_t) std::get<2>(v)) << std::endl;
        }
        out << "\tcall m_call_region_divide:" << std::endl;
        for(const auto& v : calls.m_call_region_divide)
        {
            out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
                << " src = " << ((uintptr_t) std::get<1>(v))
                << " length = " << ((uint32_t) std::get<2>(v)) << std::endl;
        }
        out << "\tcall m_call_region_multiply_constant:" << std::endl;
        for(const auto& v : calls.m_call_region_multiply_constant)
        {
            out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
                << " constant = " << ((uint32_t) std::get<1>(v))
                << " length = " << ((uint32_t) std::get<2>(v)) << std::endl;
        }
        out << "\tcall m_call_region_multiply_add:" << std::endl;
        for(const auto& v : calls.m_call_region_multiply_add)
        {
            out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
                << " src = " << ((uintptr_t) std::get<1>(v))
                << " constant = " << ((uint32_t) std::get<2>(v))
                << " length = " << ((uint32_t) std::get<3>(v)) << std::endl;
        }
        out << "\tcall m_call_region_multiply_subtract:" << std::endl;
        for(const auto& v : calls.m_call_region_multiply_subtract)
        {
            out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
                << " src = " << ((uintptr_t) std::get<1>(v))
                << " constant = " << ((uint32_t) std::get<2>(v))
                << " length = " << ((uint32_t) std::get<3>(v)) << std::endl;
        }

        return out;
    }


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

        mutable bool m_fall_through;
    };



    struct fall_through_result
    {
        fall_through_result() :
            add(true),
            subtract(true),
            multiply(true),
            divide(true),
            invert(true)
        { }
        bool add;
        bool subtract;
        bool multiply;
        bool divide;
        bool invert;

        uint32_t m_count_multiply;
        uint32_t m_count_divide;
        uint32_t m_count_invert;
        uint32_t m_count_add;
        uint32_t m_count_subtract;
    };



    /// Initializes the fall_through_results helper with the expected value
    inline void set_expected(fall_through_result& result, bool expected)
    {
        result.add = expected;
        result.subtract = expected;
        result.multiply = expected;
        result.divide = expected;
        result.invert = expected;
    }

    template<class Field, class Stack>
    void helper_fall_through_test(const fall_through_result& expected)
    {
        Stack stack;

        typedef typename Field::value_type value_type;

        value_type value = 1;

        stack.m_fall_through = false;
        stack.add(value, value);
        EXPECT_EQ(expected.add, stack.m_fall_through);

        stack.m_fall_through = false;
        stack.subtract(value, value);
        EXPECT_EQ(expected.subtract, stack.m_fall_through);

        stack.m_fall_through = false;
        stack.multiply(value, value);
        EXPECT_EQ(expected.multiply, stack.m_fall_through);

        stack.m_fall_through = false;
        stack.divide(value, value);
        EXPECT_EQ(expected.divide, stack.m_fall_through);

        stack.m_fall_through = false;
        stack.invert(value);
        EXPECT_EQ(expected.invert, stack.m_fall_through);
    }





    template<class Stack>
    void test_fall_through_add()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        value_type a = 1;
        value_type b = 1;
        value_type r = 0;

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // Add
        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_add(a, b);

        r = s.add(a, b);

        expected_calls.return_add(r);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_subtract()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        value_type a = 1;
        value_type b = 1;
        value_type r = 0;

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // Subtract
        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_subtract(a, b);

        r = s.subtract(a, b);

        expected_calls.return_subtract(r);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_multiply()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        value_type a = 1;
        value_type b = 1;
        value_type r = 0;

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // Multiply
        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_multiply(a, b);

        r = s.multiply(a, b);

        expected_calls.return_multiply(r);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_divide()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        value_type a = 1;
        value_type b = 1;
        value_type r = 0;

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // Divide
        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_divide(a, b);

        r = s.divide(a, b);

        expected_calls.return_divide(r);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_invert()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        value_type a = 1;
        value_type r = 0;

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // Invert
        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_invert(a);

        r = s.invert(a);

        expected_calls.return_invert(r);

        EXPECT_EQ(expected_calls, s.m_calls);
    }


    template<class Stack>
    void test_fall_through_packed_add()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        value_type a = 1;
        value_type b = 1;
        value_type r = 0;

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // Add
        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_packed_add(a, b);

        r = s.packed_add(a, b);

        expected_calls.return_packed_add(r);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_packed_subtract()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        value_type a = 1;
        value_type b = 1;
        value_type r = 0;

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // Subtract
        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_packed_subtract(a, b);

        r = s.packed_subtract(a, b);

        expected_calls.return_packed_subtract(r);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_packed_multiply()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        value_type a = 1;
        value_type b = 1;
        value_type r = 0;

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // Multiply
        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_packed_multiply(a, b);

        r = s.packed_multiply(a, b);

        expected_calls.return_packed_multiply(r);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_packed_divide()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        value_type a = std::numeric_limits<value_type>::max();
        value_type b = 1;
        value_type r = 0;

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // Divide
        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_packed_divide(a, b);

        r = s.packed_divide(a, b);

        expected_calls.return_packed_divide(r);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_packed_invert()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        value_type a = std::numeric_limits<value_type>::max();
        value_type r = 0;

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // Invert
        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_packed_invert(a);

        r = s.packed_invert(a);

        expected_calls.return_packed_invert(r);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_region_add()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        uint32_t length = 10;
        auto dest_vector = std::vector<value_type>(length);
        auto src_vector = std::vector<value_type>(length);

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // region_add

        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_region_add(dest_vector.data(),
            src_vector.data(), length);

        s.region_add(dest_vector.data(), src_vector.data(), length);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_region_subtract()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        uint32_t length = 10;
        auto dest_vector = std::vector<value_type>(length);
        auto src_vector = std::vector<value_type>(length);

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // region_subtract

        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_region_subtract(dest_vector.data(),
            src_vector.data(), length);

        s.region_subtract(dest_vector.data(), src_vector.data(), length);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_region_multiply()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        uint32_t length = 10;
        auto dest_vector = std::vector<value_type>(length);
        auto src_vector = std::vector<value_type>(length);

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // region_multiply

        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_region_multiply(dest_vector.data(),
            src_vector.data(), length);

        s.region_multiply(dest_vector.data(), src_vector.data(), length);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_region_divide()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        uint32_t length = 10;
        auto dest_vector = std::vector<value_type>(length);
        auto src_vector = std::vector<value_type>(length);

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // region_divide

        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_region_divide(dest_vector.data(),
            src_vector.data(), length);

        s.region_divide(dest_vector.data(), src_vector.data(), length);

        EXPECT_EQ(expected_calls, s.m_calls);
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

        // region_multiply_constant

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
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        uint32_t length = 10;
        auto dest_vector = std::vector<value_type>(length);
        auto src_vector = std::vector<value_type>(length);
        auto constant = fifi::pack<field_type>(1);

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // region_multiply_add

        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_region_multiply_add(dest_vector.data(),
            src_vector.data(), constant, length);

        s.region_multiply_add(dest_vector.data(), src_vector.data(), constant,
            length);

        EXPECT_EQ(expected_calls, s.m_calls);
    }

    template<class Stack>
    void test_fall_through_region_multiply_subtract()
    {
        typedef Stack stack;
        typedef typename stack::field_type field_type;
        typedef typename field_type::value_type value_type;

        uint32_t length = 10;
        auto dest_vector = std::vector<value_type>(length);
        auto src_vector = std::vector<value_type>(length);
        auto constant = fifi::pack<field_type>(1);

        fifi::capture_calls<value_type> expected_calls;

        stack s;

        // region_multiply_subtract

        s.m_calls.clear();
        expected_calls.clear();

        expected_calls.call_region_multiply_subtract(dest_vector.data(),
            src_vector.data(), constant, length);

        s.region_multiply_subtract(dest_vector.data(), src_vector.data(),
            constant, length);

        EXPECT_EQ(expected_calls, s.m_calls);
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
