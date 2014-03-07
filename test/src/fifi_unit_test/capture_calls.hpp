// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <tuple>

namespace fifi
{
    template<class ValueType>
    struct capture_calls
    {
        typedef std::tuple<ValueType> value;
        typedef std::tuple<ValueType, ValueType> value_value;
        typedef std::tuple<ValueType*, const ValueType*, uint32_t>
            ptr_ptr_length;
        typedef std::tuple<ValueType*, ValueType, uint32_t> ptr_value_length;
        typedef std::tuple<ValueType*, const ValueType*, ValueType, uint32_t>
            ptr_ptr_value_length;

        std::vector<value_value> m_call_add;
        std::vector<value_value> m_call_subtract;
        std::vector<value_value> m_call_multiply;
        std::vector<value_value> m_call_divide;
        std::vector<value> m_call_invert;

        std::vector<value> m_return_add;
        std::vector<value> m_return_subtract;
        std::vector<value> m_return_multiply;
        std::vector<value> m_return_divide;
        std::vector<value> m_return_invert;

        std::vector<value_value> m_call_packed_add;
        std::vector<value_value> m_call_packed_subtract;
        std::vector<value_value> m_call_packed_multiply;
        std::vector<value_value> m_call_packed_divide;
        std::vector<value> m_call_packed_invert;

        std::vector<value> m_return_packed_add;
        std::vector<value> m_return_packed_subtract;
        std::vector<value> m_return_packed_multiply;
        std::vector<value> m_return_packed_divide;
        std::vector<value> m_return_packed_invert;

        std::vector<ptr_ptr_length> m_call_region_add;
        std::vector<ptr_ptr_length> m_call_region_subtract;
        std::vector<ptr_ptr_length> m_call_region_multiply;
        std::vector<ptr_ptr_length> m_call_region_divide;
        std::vector<ptr_value_length> m_call_region_multiply_constant;
        std::vector<ptr_ptr_value_length> m_call_region_multiply_add;
        std::vector<ptr_ptr_value_length> m_call_region_multiply_subtract;

        void call_add(ValueType a, ValueType b)
        {
            m_call_add.emplace_back(a, b);
        }

        void call_subtract(ValueType a, ValueType b)
        {
            m_call_subtract.emplace_back(a, b);
        }

        void call_multiply(ValueType a, ValueType b)
        {
            m_call_multiply.emplace_back(a, b);
        }

        void call_divide(ValueType a, ValueType b)
        {
            m_call_divide.emplace_back(a, b);
        }

        void call_invert(ValueType a)
        {
            m_call_invert.emplace_back(a);
        }

        void return_add(ValueType r)
        {
            m_return_add.emplace_back(r);
        }

        void return_subtract(ValueType r)
        {
            m_return_subtract.emplace_back(r);
        }

        void return_multiply(ValueType r)
        {
            m_return_multiply.emplace_back(r);
        }

        void return_divide(ValueType r)
        {
            m_return_divide.emplace_back(r);
        }

        void return_invert(ValueType r)
        {
            m_return_invert.emplace_back(r);
        }

        void call_packed_add(ValueType a, ValueType b)
        {
            m_call_packed_add.emplace_back(a, b);
        }

        void call_packed_subtract(ValueType a, ValueType b)
        {
            m_call_packed_subtract.emplace_back(a, b);
        }

        void call_packed_multiply(ValueType a, ValueType b)
        {
            m_call_packed_multiply.emplace_back(a, b);
        }

        void call_packed_divide(ValueType a, ValueType b)
        {
            m_call_packed_divide.emplace_back(a, b);
        }

        void call_packed_invert(ValueType a)
        {
            m_call_packed_invert.emplace_back(a);
        }

        void return_packed_add(ValueType r)
        {
            m_return_packed_add.emplace_back(r);
        }

        void return_packed_subtract(ValueType r)
        {
            m_return_packed_subtract.emplace_back(r);
        }

        void return_packed_multiply(ValueType r)
        {
            m_return_packed_multiply.emplace_back(r);
        }

        void return_packed_divide(ValueType r)
        {
            m_return_packed_divide.emplace_back(r);
        }

        void return_packed_invert(ValueType r)
        {
            m_return_packed_invert.emplace_back(r);
        }

        void call_region_add(ValueType* dest, const ValueType* src,
            uint32_t length)
        {
            m_call_region_add.emplace_back(dest, src, length);
        }

        void call_region_subtract(ValueType* dest, const ValueType* src,
            uint32_t length)
        {
            m_call_region_subtract.emplace_back(dest, src, length);
        }

        void call_region_multiply(ValueType* dest, const ValueType* src,
            uint32_t length)
        {
            m_call_region_multiply.emplace_back(dest, src, length);
        }

        void call_region_divide(ValueType* dest, const ValueType* src,
            uint32_t length)
        {
            m_call_region_divide.emplace_back(dest, src, length);
        }

        void call_region_multiply_constant(ValueType* dest,
            ValueType constant, uint32_t length)
        {
            m_call_region_multiply_constant.emplace_back(dest, constant,
                length);
        }

        void call_region_multiply_add(ValueType* dest, const ValueType* src,
            ValueType constant, uint32_t length)
        {
            m_call_region_multiply_add.emplace_back(dest, src, constant,
                length);
        }

        void call_region_multiply_subtract(ValueType* dest,
            const ValueType* src, ValueType constant, uint32_t length)
        {
            m_call_region_multiply_subtract.emplace_back(dest, src, constant,
                length);
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
    inline bool equal_call_count(const capture_calls<ValueType>& a,
                           const capture_calls<ValueType>& b)
    {
        if (a.m_call_add.size() != b.m_call_add.size())
            return false;

        if (a.m_call_subtract.size() != b.m_call_subtract.size())
            return false;

        if (a.m_call_multiply.size() != b.m_call_multiply.size())
            return false;

        if (a.m_call_divide.size() != b.m_call_divide.size())
            return false;

        if (a.m_call_invert.size() != b.m_call_invert.size())
            return false;

        if (a.m_return_add.size() != b.m_return_add.size())
            return false;

        if (a.m_return_subtract.size() != b.m_return_subtract.size())
            return false;

        if (a.m_return_multiply.size() != b.m_return_multiply.size())
            return false;

        if (a.m_return_divide.size() != b.m_return_divide.size())
            return false;

        if (a.m_return_invert.size() != b.m_return_invert.size())
            return false;

        if (a.m_call_packed_add.size() != b.m_call_packed_add.size())
            return false;

        if (a.m_call_packed_subtract.size() != b.m_call_packed_subtract.size())
            return false;

        if (a.m_call_packed_multiply.size() != b.m_call_packed_multiply.size())
            return false;

        if (a.m_call_packed_divide.size() != b.m_call_packed_divide.size())
            return false;

        if (a.m_call_packed_invert.size() != b.m_call_packed_invert.size())
            return false;

        if (a.m_return_packed_add.size() != b.m_return_packed_add.size())
            return false;

        if (a.m_return_packed_subtract.size() != b.m_return_packed_subtract.size())
            return false;

        if (a.m_return_packed_multiply.size() != b.m_return_packed_multiply.size())
            return false;

        if (a.m_return_packed_divide.size() != b.m_return_packed_divide.size())
            return false;

        if (a.m_return_packed_invert.size() != b.m_return_packed_invert.size())
            return false;

        if (a.m_call_region_add.size() != b.m_call_region_add.size())
            return false;

        if (a.m_call_region_subtract.size() != b.m_call_region_subtract.size())
            return false;

        if (a.m_call_region_multiply.size() != b.m_call_region_multiply.size())
            return false;

        if (a.m_call_region_divide.size() != b.m_call_region_divide.size())
            return false;

        if (a.m_call_region_multiply_constant.size() != b.m_call_region_multiply_constant.size())
            return false;

        if (a.m_call_region_multiply_add.size() != b.m_call_region_multiply_add.size())
            return false;

        if (a.m_call_region_multiply_subtract.size() != b.m_call_region_multiply_subtract.size())
            return false;

        return true;
    }

    template<class ValueType>
    inline std::ostream& operator<<(std::ostream& out,
                                    const capture_calls<ValueType>& calls)
    {
        out << std::endl;

        // Arithmetic

        if (!calls.m_call_add.empty())
            out << "\tm_call_add:" << std::endl;
        for (const auto& v : calls.m_call_add)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }

        if (!calls.m_call_subtract.empty())
            out << "\tm_call_subtract:" << std::endl;
        for (const auto& v : calls.m_call_subtract)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }

        if (!calls.m_call_multiply.empty())
            out << "\tm_call_multiply:" << std::endl;
        for (const auto& v : calls.m_call_multiply)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }

        if (!calls.m_call_divide.empty())
            out << "\tm_call_divide:" << std::endl;
        for (const auto& v : calls.m_call_divide)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }

        if (!calls.m_call_invert.empty())
            out << "\tm_call_invert:" << std::endl;
        for (const auto& v : calls.m_call_invert)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }

        // Arithmetic returns

        if (!calls.m_return_add.empty())
            out << "\tm_return_add:" << std::endl;
        for (const auto& v : calls.m_return_add)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }

        if (!calls.m_return_subtract.empty())
            out << "\tm_return_subtract:" << std::endl;
        for (const auto& v : calls.m_return_subtract)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }

        if (!calls.m_return_multiply.empty())
            out << "\tm_return_multiply:" << std::endl;
        for (const auto& v : calls.m_return_multiply)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }

        if (!calls.m_return_divide.empty())
            out << "\tm_return_divide:" << std::endl;
        for (const auto& v : calls.m_return_divide)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }

        if (!calls.m_return_invert.empty())
            out << "\tm_return_invert:" << std::endl;
        for (const auto& v : calls.m_return_invert)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }

        // Packed arithmetic

        if (!calls.m_call_packed_add.empty())
            out << "\tm_call_packed_add:" << std::endl;
        for (const auto& v : calls.m_call_packed_add)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }

        if (!calls.m_call_packed_subtract.empty())
            out << "\tm_call_packed_subtract:" << std::endl;
        for (const auto& v : calls.m_call_packed_subtract)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }

        if (!calls.m_call_packed_multiply.empty())
            out << "\tm_call_packed_multiply:" << std::endl;
        for (const auto& v : calls.m_call_packed_multiply)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }

        if (!calls.m_call_packed_divide.empty())
            out << "\tm_call_packed_divide:" << std::endl;
        for (const auto& v : calls.m_call_packed_divide)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v))
                << " b = " << ((uint32_t) std::get<1>(v)) << std::endl;
        }

        if (!calls.m_call_packed_invert.empty())
            out << "\tm_call_packed_invert:" << std::endl;
        for (const auto& v : calls.m_call_packed_invert)
        {
            out << "\t\t" << "a = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }

        // Packed arithmetic returns

        if (!calls.m_return_packed_add.empty())
            out << "\tm_return_packed_add:" << std::endl;
        for (const auto& v : calls.m_return_packed_add)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }

        if (!calls.m_return_packed_subtract.empty())
            out << "\tm_return_packed_subtract:" << std::endl;
        for (const auto& v : calls.m_return_packed_subtract)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }

        if (!calls.m_return_packed_multiply.empty())
            out << "\tm_return_packed_multiply:" << std::endl;
        for (const auto& v : calls.m_return_packed_multiply)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }

        if (!calls.m_return_packed_divide.empty())
            out << "\tm_return_packed_divide:" << std::endl;
        for (const auto& v : calls.m_return_packed_divide)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }

        if (!calls.m_return_packed_invert.empty())
            out << "\tm_return_packed_invert:" << std::endl;
        for (const auto& v : calls.m_return_packed_invert)
        {
            out << "\t\t" << "r = " << ((uint32_t) std::get<0>(v)) << std::endl;
        }

        // Region arithmetics

        if (!calls.m_call_region_add.empty())
            out << "\tm_call_region_add:" << std::endl;
        for (const auto& v : calls.m_call_region_add)
        {
            out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
                << " src = " << ((uintptr_t) std::get<1>(v))
                << " length = " << ((uint32_t) std::get<2>(v)) << std::endl;
        }

        if (!calls.m_call_region_subtract.empty())
            out << "\tm_call_region_subtract:" << std::endl;
        for (const auto& v : calls.m_call_region_subtract)
        {
            out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
                << " src = " << ((uintptr_t) std::get<1>(v))
                << " length = " << ((uint32_t) std::get<2>(v)) << std::endl;
        }

        if (!calls.m_call_region_multiply.empty())
            out << "\tm_call_region_multiply:" << std::endl;
        for (const auto& v : calls.m_call_region_multiply)
        {
            out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
                << " src = " << ((uintptr_t) std::get<1>(v))
                << " length = " << ((uint32_t) std::get<2>(v)) << std::endl;
        }

        if (!calls.m_call_region_divide.empty())
            out << "\tm_call_region_divide:" << std::endl;
        for (const auto& v : calls.m_call_region_divide)
        {
            out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
                << " src = " << ((uintptr_t) std::get<1>(v))
                << " length = " << ((uint32_t) std::get<2>(v)) << std::endl;
        }

        if (!calls.m_call_region_multiply_constant.empty())
            out << "\tm_call_region_multiply_constant:" << std::endl;
        for (const auto& v : calls.m_call_region_multiply_constant)
        {
            out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
                << " constant = " << ((uint32_t) std::get<1>(v))
                << " length = " << ((uint32_t) std::get<2>(v)) << std::endl;
        }

        if (!calls.m_call_region_multiply_add.empty())
            out << "\tm_call_region_multiply_add:" << std::endl;
        for (const auto& v : calls.m_call_region_multiply_add)
        {
            out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
                << " src = " << ((uintptr_t) std::get<1>(v))
                << " constant = " << ((uint32_t) std::get<2>(v))
                << " length = " << ((uint32_t) std::get<3>(v)) << std::endl;
        }

        if (!calls.m_call_region_multiply_subtract.empty())
            out << "\tm_call_region_multiply_subtract:" << std::endl;
        for (const auto& v : calls.m_call_region_multiply_subtract)
        {
            out << "\t\t" << "dest = " << ((uintptr_t) std::get<0>(v))
                << " src = " << ((uintptr_t) std::get<1>(v))
                << " constant = " << ((uint32_t) std::get<2>(v))
                << " length = " << ((uint32_t) std::get<3>(v)) << std::endl;
        }

        return out;
    }
}
