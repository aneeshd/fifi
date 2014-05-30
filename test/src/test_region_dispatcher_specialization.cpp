// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/region_dispatcher.hpp>
#include <fifi/binary.hpp>

#include <gtest/gtest.h>

#include <stub/call.hpp>

#include "fifi_unit_test/helper_region_info.hpp"

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

        // Dummy function types required by the
        // region_dispatcher_specialization
        using call_region_add = std::function<void(int,int,int)>;
        using call_region_subtract = std::function<void(int,int,int)>;
        using call_region_divide = std::function<void(int,int,int)>;
        using call_region_multiply = std::function<void(int, int, int)>;
        using call_region_multiply_constant = std::function<void(int,int,int)>;

        using call_region_multiply_add = std::function<void(int,int,int,int)>;

        using call_region_multiply_subtract =
            std::function<void(int,int,int,int)>;

    public:

        dummy_super()
        {
            m_add.set_return(call_region_add());
            m_subtract.set_return(call_region_subtract());
            m_divide.set_return(call_region_divide());
            m_multiply.set_return(call_region_multiply());
            m_multiply_constant.set_return(call_region_multiply_constant());
            m_multiply_add.set_return(call_region_multiply_add());
            m_multiply_subtract.set_return(call_region_multiply_subtract());
        }

        call_region_add dispatch_region_add() const
        {
            return m_add();
        }

        call_region_subtract dispatch_region_subtract() const
        {
            return m_subtract();
        }

        call_region_divide dispatch_region_divide() const
        {
            return m_divide();
        }

        call_region_multiply dispatch_region_multiply() const
        {
            return m_multiply();
        }

        call_region_multiply_constant dispatch_region_multiply_constant() const
        {
            return m_multiply_constant();
        }

        call_region_multiply_add dispatch_region_multiply_add() const
        {
            return m_multiply_add();
        }

        call_region_multiply_subtract dispatch_region_multiply_subtract() const
        {
            return m_multiply_subtract();
        }

        stub::call<call_region_add ()> m_add;
        stub::call<call_region_subtract ()> m_subtract;
        stub::call<call_region_divide ()> m_divide;
        stub::call<call_region_multiply ()> m_multiply;
        stub::call<call_region_multiply_constant ()> m_multiply_constant;
        stub::call<call_region_multiply_add ()> m_multiply_add;
        stub::call<call_region_multiply_subtract ()> m_multiply_subtract;

    };

    // Stack with different field than the dummy stack so it should
    // trigger the empty region_dispatcher_specialization to be used.
    class no_use_stack
    {
    public:
        using field_type = fifi::binary;
    };

    // Stack with same field as the dummy stack so it will be enable the
    // region_dispatcher_specialization
    class use_stack
    {
    public:
        using field_type = fifi::binary8;

    public:

        use_stack()
            : m_enabled(true)
        { }

        void region_add(int,int,int) const
        {
            m_add();
        }

        void region_subtract(int,int,int) const
        {
            m_subtract();
        }

        void region_divide(int,int,int) const
        {
            m_divide();
        }

        void region_multiply(int,int,int) const
        {
            m_multiply();
        }

        void region_multiply_constant(int,int,int) const
        {
            m_multiply_constant();
        }

        void region_multiply_add(int,int,int,int) const
        {
            m_multiply_add();
        }

        void region_multiply_subtract(int,int,int,int) const
        {
            m_multiply_subtract();
        }

        bool enabled() const
        {
            return m_enabled;
        }

        stub::call<void()> m_add;
        stub::call<void()> m_subtract;
        stub::call<void()> m_divide;
        stub::call<void()> m_multiply;
        stub::call<void()> m_multiply_constant;
        stub::call<void()> m_multiply_add;
        stub::call<void()> m_multiply_subtract;

        bool m_enabled;
    };

    // Stack with same field as the dummy stack but where only some of
    // the region functions are available
    class use_partial_stack
    {
    public:
        using field_type = fifi::binary8;

    public:

        use_partial_stack()
            : m_enabled(true)
        { }

        void region_add(int,int,int) const
        {
            m_add();
        }

        void region_divide(int,int,int) const
        {
            m_divide();
        }

        void region_multiply_constant(int,int,int) const
        {
            m_multiply_constant();
        }

        void region_multiply_subtract(int,int,int,int) const
        {
            m_multiply_subtract();
        }

        bool enabled() const
        {
            return m_enabled;
        }

        stub::call<void()> m_add;
        stub::call<void()> m_subtract;
        stub::call<void()> m_divide;
        stub::call<void()> m_multiply;
        stub::call<void()> m_multiply_constant;
        stub::call<void()> m_multiply_add;
        stub::call<void()> m_multiply_subtract;

        bool m_enabled;
    };

    // Layer exposing the stack for testing purposes
    template<class Super>
    class expose_stack : public Super
    {
    public:

        using Super::m_stack;

        auto testing_stack() -> decltype(m_stack)&
        {
            return m_stack;
        }
    };
}

/// Check that the code compiles with a stack that does not provide
/// the same field
TEST(region_dispatcher_specialization, no_use)
{
    fifi::region_dispatcher<no_use_stack, dummy_super> stack;
    (void)stack;
}

/// Use a stack that provides the same field, all region arithmetic
/// functions and that
TEST(region_dispatcher_specilization, use_enabled)
{
    expose_stack<fifi::region_dispatcher<use_stack, dummy_super>> stack;

    auto add = stack.dispatch_region_add();
    auto subtract = stack.dispatch_region_subtract();
    auto divide = stack.dispatch_region_divide();
    auto multiply = stack.dispatch_region_multiply();
    auto multiply_constant = stack.dispatch_region_multiply_constant();
    auto multiply_add = stack.dispatch_region_multiply_add();
    auto multiply_subtract = stack.dispatch_region_multiply_subtract();

    // Everything should have been redirected to the stack
    EXPECT_TRUE(stack.m_add.no_calls());
    EXPECT_TRUE(stack.m_subtract.no_calls());
    EXPECT_TRUE(stack.m_divide.no_calls());
    EXPECT_TRUE(stack.m_multiply.no_calls());
    EXPECT_TRUE(stack.m_multiply_constant.no_calls());
    EXPECT_TRUE(stack.m_multiply_add.no_calls());
    EXPECT_TRUE(stack.m_multiply_subtract.no_calls());

    // Invoke the returned function objects and check that the right
    // functions in the stack was called
    add(0,0,0);
    subtract(0,0,0);
    divide(0,0,0);
    multiply(0,0,0);
    multiply_constant(0,0,0);
    multiply_add(0,0,0,0);
    multiply_subtract(0,0,0,0);

    auto& s = stack.testing_stack();

    EXPECT_TRUE(s.m_add.called_once_with());
    EXPECT_TRUE(s.m_subtract.called_once_with());
    EXPECT_TRUE(s.m_divide.called_once_with());
    EXPECT_TRUE(s.m_multiply.called_once_with());
    EXPECT_TRUE(s.m_multiply_constant.called_once_with());
    EXPECT_TRUE(s.m_multiply_add.called_once_with());
    EXPECT_TRUE(s.m_multiply_subtract.called_once_with());
}

/// Use a stack that provides the same field and all region arithmetic
/// functions
TEST(region_dispatcher_specilization, use_not_enabled)
{
    expose_stack<fifi::region_dispatcher<use_stack, dummy_super>> stack;

    // Set enabled equal to false in the embedded stack
    auto& s = stack.testing_stack();
    s.m_enabled = false;

    auto add = stack.dispatch_region_add();
    auto subtract = stack.dispatch_region_subtract();
    auto divide = stack.dispatch_region_divide();
    auto multiply = stack.dispatch_region_multiply();
    auto multiply_constant = stack.dispatch_region_multiply_constant();
    auto multiply_add = stack.dispatch_region_multiply_add();
    auto multiply_subtract = stack.dispatch_region_multiply_subtract();

    // Everything should to the Super
    EXPECT_TRUE(stack.m_add.called_once_with());
    EXPECT_TRUE(stack.m_subtract.called_once_with());
    EXPECT_TRUE(stack.m_divide.called_once_with());
    EXPECT_TRUE(stack.m_multiply.called_once_with());
    EXPECT_TRUE(stack.m_multiply_constant.called_once_with());
    EXPECT_TRUE(stack.m_multiply_add.called_once_with());
    EXPECT_TRUE(stack.m_multiply_subtract.called_once_with());
}

/// Use a stack that provides the same field, all region arithmetic
/// functions and that
TEST(region_dispatcher_specilization, use_partial_enabled)
{
    expose_stack<fifi::region_dispatcher<use_partial_stack, dummy_super>>
        stack;

    auto add = stack.dispatch_region_add();
    auto subtract = stack.dispatch_region_subtract();
    auto divide = stack.dispatch_region_divide();
    auto multiply = stack.dispatch_region_multiply();
    auto multiply_constant = stack.dispatch_region_multiply_constant();
    auto multiply_add = stack.dispatch_region_multiply_add();
    auto multiply_subtract = stack.dispatch_region_multiply_subtract();

    // Check the correct calls were redirected
    EXPECT_TRUE(stack.m_add.no_calls());
    EXPECT_TRUE(stack.m_subtract.called_once_with());
    EXPECT_TRUE(stack.m_divide.no_calls());
    EXPECT_TRUE(stack.m_multiply.called_once_with());
    EXPECT_TRUE(stack.m_multiply_constant.no_calls());
    EXPECT_TRUE(stack.m_multiply_add.called_once_with());
    EXPECT_TRUE(stack.m_multiply_subtract.no_calls());

    // Invoke the returned function objects and check that the right
    // functions in the stack was called
    add(0,0,0);
    // subtract(0,0,0);
    divide(0,0,0);
    // multiply(0,0,0);
    multiply_constant(0,0,0);
    // multiply_add(0,0,0,0);
    multiply_subtract(0,0,0,0);

    auto& s = stack.testing_stack();

    EXPECT_TRUE(s.m_add.called_once_with());
    // EXPECT_TRUE(s.m_subtract.called_once_with());
    EXPECT_TRUE(s.m_divide.called_once_with());
    // EXPECT_TRUE(s.m_multiply.called_once_with());
    EXPECT_TRUE(s.m_multiply_constant.called_once_with());
    // EXPECT_TRUE(s.m_multiply_add.called_once_with());
    EXPECT_TRUE(s.m_multiply_subtract.called_once_with());
}

/// Use a stack that provides the same field and all region arithmetic
/// functions
TEST(region_dispatcher_specilization, use_partial_not_enabled)
{
    expose_stack<fifi::region_dispatcher<use_partial_stack, dummy_super>>
        stack;

    // Set enabled equal to false in the embedded stack
    auto& s = stack.testing_stack();
    s.m_enabled = false;

    auto add = stack.dispatch_region_add();
    auto subtract = stack.dispatch_region_subtract();
    auto divide = stack.dispatch_region_divide();
    auto multiply = stack.dispatch_region_multiply();
    auto multiply_constant = stack.dispatch_region_multiply_constant();
    auto multiply_add = stack.dispatch_region_multiply_add();
    auto multiply_subtract = stack.dispatch_region_multiply_subtract();

    // Everything should to the Super
    EXPECT_TRUE(stack.m_add.called_once_with());
    EXPECT_TRUE(stack.m_subtract.called_once_with());
    EXPECT_TRUE(stack.m_divide.called_once_with());
    EXPECT_TRUE(stack.m_multiply.called_once_with());
    EXPECT_TRUE(stack.m_multiply_constant.called_once_with());
    EXPECT_TRUE(stack.m_multiply_add.called_once_with());
    EXPECT_TRUE(stack.m_multiply_subtract.called_once_with());
}

/// @todo re-enable unit tests

TEST(test_region_dispatcher_specialization, alignment)
{
//     fifi::dummy_stack_disabled disabled_stack;
//     fifi::dummy_stack_enabled enabled_stack;

//     EXPECT_EQ(disabled_stack.alignment(), 1U);
//     EXPECT_EQ(enabled_stack.alignment(), 2U);
}

TEST(test_region_dispatcher_specialization, max_alignment)
{
    // fifi::dummy_stack_disabled disabled_stack;
    // fifi::dummy_stack_enabled enabled_stack;

    // EXPECT_EQ(disabled_stack.max_alignment(), 10U);
    // EXPECT_EQ(enabled_stack.max_alignment(), 20U);
}

TEST(test_region_dispatcher_specialization, granularity)
{
    // fifi::dummy_stack_disabled disabled_stack;
    // fifi::dummy_stack_enabled enabled_stack;

    // EXPECT_EQ(disabled_stack.granularity(), 3U);
    // EXPECT_EQ(enabled_stack.granularity(), 4U);
}

TEST(test_region_dispatcher_specialization, max_granularity)
{
    // fifi::dummy_stack_disabled disabled_stack;
    // fifi::dummy_stack_enabled enabled_stack;

    // EXPECT_EQ(disabled_stack.max_granularity(), 30U);
    // EXPECT_EQ(enabled_stack.max_granularity(), 40U);
}

TEST(test_region_dispatcher_specialization, region_multiply_constant)
{
    // fifi::dummy_stack_enabled enabled_stack;
    // fifi::dummy_stack_disabled disabled_stack;

    // uint32_t length = 1;
    // std::vector<uint8_t> dest(length);
    // std::vector<uint8_t> src(length);
    // uint8_t constant = 255;

    // disabled_stack.region_add(dest.data(), src.data(), length);
    // disabled_stack.region_subtract(dest.data(), src.data(), length);
    // disabled_stack.region_multiply(dest.data(), src.data(), length);
    // disabled_stack.region_divide(dest.data(), src.data(), length);
    // disabled_stack.region_multiply_constant(dest.data(), constant, length);
    // disabled_stack.region_multiply_add(
    //     dest.data(), src.data(), constant, length);
    // disabled_stack.region_multiply_subtract(
    //     dest.data(), src.data(), constant, length);

    // enabled_stack.region_add(dest.data(), src.data(), length);
    // enabled_stack.region_subtract(dest.data(), src.data(), length);
    // enabled_stack.region_multiply(dest.data(), src.data(), length);
    // enabled_stack.region_divide(dest.data(), src.data(), length);
    // enabled_stack.region_multiply_constant(dest.data(), constant, length);
    // enabled_stack.region_multiply_add(
    //     dest.data(), src.data(), constant, length);
    // enabled_stack.region_multiply_subtract(
    //     dest.data(), src.data(), constant, length);
}
