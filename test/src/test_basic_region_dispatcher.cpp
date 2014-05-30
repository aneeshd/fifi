// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <fifi/basic_region_dispatcher.hpp>
#include <fifi/binary8.hpp>

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

    public:

        void region_add(value_type* dest, const value_type* src,
                        uint32_t length) const
        {
            m_add(dest,src,length);
        }

        void region_subtract(value_type* dest, const value_type* src,
                             uint32_t length) const
        {
            m_subtract(dest,src,length);
        }

        void region_divide(value_type* dest, const value_type* src,
                           uint32_t length) const
        {
            m_divide(dest,src,length);
        }

        void region_multiply(value_type* dest, const value_type* src,
                             uint32_t length) const
        {
            m_multiply(dest,src,length);
        }

        void region_multiply_constant(value_type* dest, value_type constant,
                                      uint32_t length) const
        {
            m_multiply_constant(dest,constant,length);
        }

        void region_multiply_add(value_type* dest,
                                 const value_type* src,
                                 value_type constant,
                                 uint32_t length) const
        {
            m_multiply_add(dest,src,constant,length);
        }

        void region_multiply_subtract(value_type* dest,
                                      const value_type* src,
                                      value_type constant,
                                      uint32_t length) const
        {
            m_multiply_subtract(dest,src,constant,length);
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

    class dummy_stack : public kodo::basic_region_dispatcher<dummy_super>
    { };
}

/// Check that the code compiles with a stack that does not provide
/// the same field
TEST(basic_region_dispatcher, api)
{
    dummy_stack stack;

    auto add = stack.dispatch_region_add();
    auto subtract = stack.dispatch_region_subtract();
    auto divide = stack.dispatch_region_divide();
    auto multiply = stack.dispatch_region_multiply();
    auto multiply_constant = stack.dispatch_region_multiply_constant();
    auto multiply_add = stack.dispatch_region_multiply_add();
    auto multiply_subtract = stack.dispatch_region_multiply_subtract();


}
