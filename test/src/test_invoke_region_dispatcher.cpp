// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <sak/easy_bind.hpp>

#include <fifi/invoke_region_dispatcher.hpp>
#include <fifi/binary8.hpp>

#include <gtest/gtest.h>

#include <stub/call.hpp>

// Put dummy layers and tests classes in an anonymous namespace
// to avoid violations of ODF (one-definition-rule) in other
// translation units
namespace
{
    class dummy_super
    {
    public:

        using field_type = fifi::binary8;
        using value_type = field_type::value_type;

        using call_region_add = std::function<
            void (value_type*, const value_type*, uint32_t)>;

        using call_region_subtract = std::function<
            void (value_type*, const value_type*, uint32_t)>;

        using call_region_divide = std::function<
            void (value_type*, const value_type*, uint32_t)>;

        using call_region_multiply = std::function<
            void (value_type*, const value_type*, uint32_t)>;

        using call_region_multiply_constant = std::function<
            void (value_type*, value_type, uint32_t)>;

        using call_region_multiply_add = std::function<
            void (value_type*, const value_type*, value_type, uint32_t)>;

        using call_region_multiply_subtract = std::function<
            void (value_type*, const value_type*, value_type, uint32_t)>;

    public:

        call_region_add dispatch_region_add() const
        {
            return std::bind(std::cref(m_add), std::placeholders::_1,
                             std::placeholders::_2, std::placeholders::_3);
        }

        call_region_subtract dispatch_region_subtract() const
        {
            return std::bind(std::cref(m_subtract), std::placeholders::_1,
                             std::placeholders::_2, std::placeholders::_3);
        }

        call_region_divide dispatch_region_divide() const
        {
            return std::bind(std::cref(m_divide), std::placeholders::_1,
                             std::placeholders::_2, std::placeholders::_3);
        }

        call_region_multiply dispatch_region_multiply() const
        {
            return std::bind(std::cref(m_multiply), std::placeholders::_1,
                             std::placeholders::_2, std::placeholders::_3);
        }

        call_region_multiply_constant dispatch_region_multiply_constant() const
        {
            return std::bind(std::cref(m_multiply_constant),
                             std::placeholders::_1, std::placeholders::_2,
                             std::placeholders::_3);
        }

        call_region_multiply_add dispatch_region_multiply_add() const
        {
            return std::bind(std::cref(m_multiply_add), std::placeholders::_1,
                             std::placeholders::_2, std::placeholders::_3,
                             std::placeholders::_4);
        }

        call_region_multiply_subtract dispatch_region_multiply_subtract() const
        {
            return std::bind(std::cref(m_multiply_subtract),
                             std::placeholders::_1, std::placeholders::_2,
                             std::placeholders::_3, std::placeholders::_4);
        }

        stub::call<void (value_type*,const value_type*,uint32_t)>
            m_add;

        stub::call<void (value_type*,const value_type*,uint32_t)>
            m_subtract;

        stub::call<void (value_type*,const value_type*,uint32_t)>
            m_divide;

        stub::call<void (value_type*,const value_type*,uint32_t)>
            m_multiply;

        stub::call<void (value_type*,value_type,uint32_t)>
            m_multiply_constant;

        stub::call<void (value_type*,const value_type*,value_type,uint32_t)>
            m_multiply_add;

        stub::call<void (value_type*,const value_type*,value_type,uint32_t)>
            m_multiply_subtract;
    };

    class dummy_stack : public fifi::invoke_region_dispatcher<dummy_super>
    { };
}

/// Check that the code compiles with a stack that does not provide
/// the same field
TEST(test_invoke_region_dispatcher, api)
{
    dummy_stack stack;

    stack.region_add(0,0,0);
    EXPECT_TRUE(stack.m_add.called_once_with(0,0,0));

    stack.region_subtract(0,0,1);
    EXPECT_TRUE(stack.m_subtract.called_once_with(0,0,1));

    stack.region_divide(0,0,2);
    EXPECT_TRUE(stack.m_divide.called_once_with(0,0,2));

    stack.region_multiply(0,0,3);
    EXPECT_TRUE(stack.m_multiply.called_once_with(0,0,3));

    stack.region_multiply_constant(0,1,3);
    EXPECT_TRUE(stack.m_multiply_constant.called_once_with(0,1,3));

    stack.region_multiply_add(0,0,1,3);
    EXPECT_TRUE(stack.m_multiply_add.called_once_with(0,0,1,3));

    stack.region_multiply_subtract(0,0,2,3);
    EXPECT_TRUE(stack.m_multiply_subtract.called_once_with(0,0,2,3));
}
