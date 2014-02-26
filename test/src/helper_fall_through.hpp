// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <fifi/fifi_utils.hpp>
#include <tuple>
#include <random>

namespace fifi
{

    template<class Field>
    struct random_constant
    {
        typedef Field field_type;
        typedef typename field_type::value_type value_type;

        random_constant()
            : m_distribution(field_type::min_value, field_type::max_value)
        { }

        value_type value()
        {
            return m_distribution(m_generator);
        }

        value_type pack()
        {
            return fifi::pack<field_type>(m_distribution(m_generator));
        }

        std::uniform_int_distribution<value_type> m_distribution;
        std::mt19937 m_generator;

    };


    struct fall_through_counter
    {
        void zero_counter()
        {
            m_count_multiply = 0;
            m_count_divide = 0;
            m_count_invert = 0;
            m_count_add = 0;
            m_count_subtract = 0;

            m_count_packed_multiply = 0;
            m_count_packed_divide = 0;
            m_count_packed_invert = 0;
            m_count_packed_add = 0;
            m_count_packed_subtract = 0;

            m_count_region_multiply = 0;
            m_count_region_divide = 0;
            m_count_region_invert = 0;
            m_count_region_add = 0;
            m_count_region_subtract = 0;
        }

        uint32_t m_count_multiply;
        uint32_t m_count_divide;
        uint32_t m_count_invert;
        uint32_t m_count_add;
        uint32_t m_count_subtract;

        uint32_t m_count_packed_multiply;
        uint32_t m_count_packed_divide;
        uint32_t m_count_packed_invert;
        uint32_t m_count_packed_add;
        uint32_t m_count_packed_subtract;

        uint32_t m_count_region_multiply;
        uint32_t m_count_region_divide;
        uint32_t m_count_region_invert;
        uint32_t m_count_region_add;
        uint32_t m_count_region_subtract;
    };

    inline bool operator==(const fall_through_counter& a,
                           const fall_through_counter& b)
    {
        if(a.m_count_multiply != b.m_count_multiply)
            return false;

        if(a.m_count_divide != b.m_count_divide)
            return false;

        if(a.m_count_invert != b.m_count_invert)
            return false;

        if(a.m_count_add != b.m_count_add)
            return false;

        if(a.m_count_subtract != b.m_count_subtract)
            return false;

        if(a.m_count_packed_multiply != b.m_count_packed_multiply)
            return false;

        if(a.m_count_packed_divide != b.m_count_packed_divide)
            return false;

        if(a.m_count_packed_invert != b.m_count_packed_invert)
            return false;

        if(a.m_count_packed_add != b.m_count_packed_add)
            return false;

        if(a.m_count_packed_subtract != b.m_count_packed_subtract)
            return false;

        if(a.m_count_region_multiply != b.m_count_region_multiply)
            return false;

        if(a.m_count_region_divide != b.m_count_region_divide)
            return false;

        if(a.m_count_region_invert != b.m_count_region_invert)
            return false;

        if(a.m_count_region_add != b.m_count_region_add)
            return false;

        if(a.m_count_region_subtract != b.m_count_region_subtract)
            return false;

        return true;
    }

    template<class ValueType>
    struct capture_calls
    {
        typedef std::tuple<ValueType> args1;
        typedef std::tuple<ValueType, ValueType> args2;

        std::vector<args2> m_call_multiply;
        std::vector<args2> m_call_divide;
        std::vector<args1> m_call_invert;
        std::vector<args2> m_call_add;
        std::vector<args2> m_call_subtract;

        std::vector<args1> m_return_multiply;
        std::vector<args1> m_return_divide;
        std::vector<args1> m_return_invert;
        std::vector<args1> m_return_add;
        std::vector<args1> m_return_subtract;

        std::vector<args2> m_call_packed_multiply;
        std::vector<args2> m_call_packed_divide;
        std::vector<args1> m_call_packed_invert;
        std::vector<args2> m_call_packed_add;
        std::vector<args2> m_call_packed_subtract;

        std::vector<args1> m_return_packed_multiply;
        std::vector<args1> m_return_packed_divide;
        std::vector<args1> m_return_packed_invert;
        std::vector<args1> m_return_packed_add;
        std::vector<args1> m_return_packed_subtract;

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
        void return_packed_add(Args&&... args)
        {
            m_return_packed_add.emplace_back(args...);
        }
        template <class... Args>
        void return_packed_subtract(Args&&... args)
        {
            m_return_packed_subtract.emplace_back(args...);
        }

        void clear()
        {
            m_call_multiply.clear();
            m_call_divide.clear();
            m_call_invert.clear();
            m_call_add.clear();
            m_call_subtract.clear();

            m_return_multiply.clear();
            m_return_divide.clear();
            m_return_invert.clear();
            m_return_add.clear();
            m_return_subtract.clear();

            m_call_packed_multiply.clear();
            m_call_packed_divide.clear();
            m_call_packed_invert.clear();
            m_call_packed_add.clear();
            m_call_packed_subtract.clear();

            m_return_packed_multiply.clear();
            m_return_packed_divide.clear();
            m_return_packed_invert.clear();
            m_return_packed_add.clear();
            m_return_packed_subtract.clear();
        }
    };


    template<class ValueType>
    inline bool operator==(const capture_calls<ValueType>& a,
                           const capture_calls<ValueType>& b)
    {
        if (a.m_call_multiply != b.m_call_multiply)
            return false;

        if (a.m_call_divide != b.m_call_divide)
            return false;

        if (a.m_call_invert != b.m_call_invert)
            return false;

        if (a.m_call_add != b.m_call_add)
            return false;

        if (a.m_call_subtract != b.m_call_subtract)
            return false;

        if (a.m_return_multiply != b.m_return_multiply)
            return false;

        if (a.m_return_divide != b.m_return_divide)
            return false;

        if (a.m_return_invert != b.m_return_invert)
            return false;

        if (a.m_return_add != b.m_return_add)
            return false;

        if (a.m_return_subtract != b.m_return_subtract)
            return false;

        if (a.m_call_packed_multiply != b.m_call_packed_multiply)
            return false;

        if (a.m_call_packed_divide != b.m_call_packed_divide)
            return false;

        if (a.m_call_packed_invert != b.m_call_packed_invert)
            return false;

        if (a.m_call_packed_add != b.m_call_packed_add)
            return false;

        if (a.m_call_packed_subtract != b.m_call_packed_subtract)
            return false;

        if (a.m_return_packed_multiply != b.m_return_packed_multiply)
            return false;

        if (a.m_return_packed_divide != b.m_return_packed_divide)
            return false;

        if (a.m_return_packed_invert != b.m_return_packed_invert)
            return false;

        if (a.m_return_packed_add != b.m_return_packed_add)
            return false;

        if (a.m_return_packed_subtract != b.m_return_packed_subtract)
            return false;

        return true;

    }

    template<class ValueType>
    inline std::ostream& operator<<(std::ostream& out,
                                    const capture_calls<ValueType>& calls)
    {
        out << "call packed_multiply:" << std::endl;
        for(const auto& v : calls.m_call_packed_multiply)
        {
            out << "\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t)std::get<1>(v)) << std::endl;
        }

        out << "call packed_add:" << std::endl;
        for(const auto& v : calls.m_call_packed_add)
        {
            out << "\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t)std::get<1>(v)) << std::endl;
        }


        return out;
    }


    /// @todo Add documentation
    template<class Field>
    struct helper_fall_through
    {

        typedef Field field_type;

        typedef typename Field::value_type value_type;

        value_type multiply(value_type a, value_type b) const
        {
            m_calls.call_multiply(a, b);
            ++m_counter.m_count_multiply;

            auto r = m_constants.value();
            m_calls.return_multiply(r);

            return r;
        }

        value_type divide(value_type numerator,
                          value_type denominator) const
        {
            m_calls.call_divide(numerator, denominator);
            ++m_counter.m_count_divide;

            auto r = m_constants.value();
            m_calls.return_divide(r);

            return r;
        }

        value_type invert(value_type a) const
        {
            m_calls.call_invert(a);
            ++m_counter.m_count_invert;

            auto r = m_constants.value();
            m_calls.return_invert(r);

            return r;
        }

        value_type add(value_type a, value_type b) const
        {
            m_calls.call_add(a, b);
            ++m_counter.m_count_add;

            auto r = m_constants.value();
            m_calls.return_add(r);

            return r;
        }

        value_type subtract(value_type a, value_type b) const
        {
            m_calls.call_subtract(a, b);
            ++m_counter.m_count_subtract;

            auto r = m_constants.value();
            m_calls.return_subtract(r);

            return r;
        }

        value_type packed_multiply(value_type a, value_type b) const
        {
            m_calls.call_packed_multiply(a, b);
            ++m_counter.m_count_packed_multiply;

            auto r = m_constants.pack();
            m_calls.return_packed_multiply(r);

            return r;
        }

        value_type packed_divide(value_type numerator,
                                 value_type denominator) const
        {
            m_calls.call_packed_divide(numerator, denominator);
            ++m_counter.m_count_packed_divide;

            auto r = m_constants.pack();
            m_calls.return_packed_divide(r);

            return r;
        }

        value_type packed_invert(value_type a) const
        {
            m_calls.call_packed_invert(a);
            ++m_counter.m_count_packed_invert;

            auto r = m_constants.pack();
            m_calls.return_packed_invert(r);

            return r;
        }

        value_type packed_add(value_type a, value_type b) const
        {
            m_calls.call_packed_add(a, b);
            ++m_counter.m_count_packed_add;

            auto r = m_constants.pack();
            m_calls.return_packed_add(r);

            return r;
        }

        value_type packed_subtract(value_type a, value_type b) const
        {
            m_calls.call_packed_subtract(a, b);
            ++m_counter.m_count_packed_subtract;

            auto r = m_constants.pack();
            m_calls.return_packed_subtract(r);

            return r;
        }

        mutable capture_calls<value_type> m_calls;
        mutable random_constant<field_type> m_constants;

        mutable bool m_fall_through;
        mutable fall_through_counter m_counter;
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


    /// This test helper invokes all the packed arithmetic functions
    /// and checks that the corresponding arithmetic functions are
    /// called the correct number of times.
    template<class Stack>
    void test_packed_multiply_counters(const fall_through_counter& expected)
    {
        Stack stack;

        stack.m_counter.zero_counter();
        stack.packed_multiply(1U, 1U);

        EXPECT_EQ(expected, stack.m_counter);
    }

    template<class Stack>
    void test_packed_divide_counters(const fall_through_counter& expected)
    {
        Stack stack;

        auto v = pack<typename Stack::field_type>(1U);

        stack.m_counter.zero_counter();
        stack.packed_divide(v, v);

        EXPECT_EQ(expected, stack.m_counter);
    }

    template<class Stack>
    void test_packed_invert_counters(const fall_through_counter& expected)
    {
        Stack stack;

        auto v = pack<typename Stack::field_type>(1U);

        stack.m_counter.zero_counter();
        stack.packed_invert(v);

        EXPECT_EQ(expected, stack.m_counter);
    }

    template<class Stack>
    void test_packed_add_counters(const fall_through_counter& expected)
    {
        Stack stack;

        auto v = pack<typename Stack::field_type>(1U);

        stack.m_counter.zero_counter();
        stack.packed_add(v, v);

        EXPECT_EQ(expected, stack.m_counter);
    }

    template<class Stack>
    void test_packed_subtract_counters(const fall_through_counter& expected)
    {
        Stack stack;

        auto v = pack<typename Stack::field_type>(1U);

        stack.m_counter.zero_counter();
        stack.packed_subtract(v, v);

        EXPECT_EQ(expected, stack.m_counter);
    }

    template<class Stack>
    void test_packed_counters(const fall_through_counter& overall)
    {
        // Derive the expected from the overall counter
        fall_through_counter expected;

        expected.zero_counter();
        expected.m_count_multiply = overall.m_count_multiply;
        expected.m_count_packed_multiply = overall.m_count_packed_multiply;
        fifi::test_packed_multiply_counters<Stack>(expected);

        expected.zero_counter();
        expected.m_count_divide = overall.m_count_divide;
        expected.m_count_packed_divide = overall.m_count_packed_divide;
        fifi::test_packed_divide_counters<Stack>(expected);

        expected.zero_counter();
        expected.m_count_invert = overall.m_count_invert;
        expected.m_count_packed_invert = overall.m_count_packed_invert;
        fifi::test_packed_invert_counters<Stack>(expected);

        expected.zero_counter();
        expected.m_count_add = overall.m_count_add;
        expected.m_count_packed_add = overall.m_count_packed_add;
        fifi::test_packed_add_counters<Stack>(expected);

        expected.zero_counter();
        expected.m_count_subtract = overall.m_count_subtract;
        expected.m_count_packed_subtract = overall.m_count_packed_subtract;
        fifi::test_packed_subtract_counters<Stack>(expected);
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
        value_type b = 1;
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
    void test_fall_through()
    {
        test_fall_through_add<Stack>();
        test_fall_through_subtract<Stack>();
        test_fall_through_multiply<Stack>();
        test_fall_through_divide<Stack>();
        test_fall_through_invert<Stack>();
    }
}
