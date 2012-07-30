// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/simple_online.h>
#include <fifi/full_table.h>
#include <fifi/log_table.h>
#include <fifi/extended_log_table.h>
#include <fifi/field_types.h>
#include <fifi/arithmetics.h>
#include <fifi/default_field_impl.h>

template<class FieldImpl>
class test_arithmetics
{
public:

    typedef typename FieldImpl::value_type value_type;
    typedef typename FieldImpl::field_type field_type;

    test_arithmetics()
        : m_length(100)
        {
            m_dest.resize(m_length);
            m_temp.resize(m_length);
            m_src.resize(m_length);
            m_dest_check.resize(m_length);
            m_src_check.resize(m_length);
        }

    void setup()
        {
            for(uint32_t i = 0; i < m_length; ++i)
            {
                value_type d = rand() % field_type::order;
                value_type s = rand() % field_type::order;

                m_dest[i] = d;
                m_src[i]  = s;

                m_dest_check[i] = d;
                m_src_check[i]  = s;
            }
        }

    void test_add()
        {
            setup();

            fifi::add(m_impl, &m_dest[0], &m_src[0], m_length);

            // Now we verify that we have computed:
            // dest[i] = dest[i] + src[i]
            for(uint32_t i = 0; i < m_length; ++i)
            {
                value_type result =
                    m_impl.add(m_dest_check[i], m_src_check[i]);

                ASSERT_EQ(result, m_dest[i]);
            }
        }


    void test_subtract()
        {
            setup();

            fifi::subtract(m_impl, &m_dest[0], &m_src[0], m_length);

            // Now we verify that we have computed:
            // dest[i] = dest[i] + src[i]
            for(uint32_t i = 0; i < m_length; ++i)
            {
                value_type result =
                    m_impl.subtract(m_dest_check[i], m_src_check[i]);

                ASSERT_EQ(result, m_dest[i]);
            }
        }

    void test_multiply()
        {
            setup();

            fifi::multiply(m_impl, &m_dest[0], &m_src[0], m_length);

            // Now we verify that we have computed:
            // dest[i] = dest[i] + src[i]
            for(uint32_t i = 0; i < m_length; ++i)
            {
                value_type result =
                    m_impl.multiply(m_dest_check[i], m_src_check[i]);

                ASSERT_EQ(result, m_dest[i]);
            }
        }


    void test_multiply_constant()
        {
            setup();

            value_type coefficient = rand() % field_type::order;

            fifi::multiply_constant(m_impl, coefficient, &m_dest[0], m_length);

            // Now we verify that we have computed:
            // dest[i] = dest[i] + src[i]
            for(uint32_t i = 0; i < m_length; ++i)
            {
                value_type result =
                    m_impl.multiply(coefficient, m_dest_check[i]);

                ASSERT_EQ(result, m_dest[i]);
            }
        }


    void test_multiply_add()
        {
            setup();

            value_type coefficient = rand() % field_type::order;

            fifi::multiply_add(m_impl, coefficient,
                               &m_dest[0], &m_src[0],
                               &m_temp[0], m_length);

            // Now we verify that we have computed:
            // dest[i] = dest[i] + (src[i]*c)
            for(uint32_t i = 0; i < m_length; ++i)
            {
                value_type multiplied =
                    m_impl.multiply(m_src_check[i], coefficient);

                value_type result =
                    m_impl.add(m_dest_check[i], multiplied);

                ASSERT_EQ(result, m_dest[i]);
            }
        }


    void test_multiply_subtract()
        {
            setup();

            value_type coefficient = rand() % field_type::order;

            fifi::multiply_subtract(m_impl, coefficient,
                                    &m_dest[0], &m_src[0],
                                    &m_temp[0], m_length);

            // Now we verify that we have computed:
            // dest[i] = dest[i] + (src[i]*c)
            for(uint32_t i = 0; i < m_length; ++i)
            {
                value_type multiplied =
                    m_impl.multiply(m_src_check[i], coefficient);

                value_type result =
                    m_impl.subtract(m_dest_check[i], multiplied);

                ASSERT_EQ(result, m_dest[i]);
            }
        }



private:

    uint32_t m_length;

    std::vector<value_type> m_dest;
    std::vector<value_type> m_src;
    std::vector<value_type> m_temp;

    std::vector<value_type> m_dest_check;
    std::vector<value_type> m_src_check;

    FieldImpl m_impl;

};

template<class FieldImpl>
void test_functions()
{
    test_arithmetics<FieldImpl> s;
    s.test_add();
    s.test_subtract();
    s.test_multiply_add();
    s.test_multiply_subtract();
    s.test_multiply();
    s.test_multiply_constant();
}


TEST(test_arithmetics, RunFunctions)
{
    test_functions<fifi::simple_online<fifi::binary> >();
    test_functions< fifi::simple_online<fifi::binary8> >();
    test_functions< fifi::simple_online<fifi::binary16> >();

    test_functions< fifi::full_table<fifi::binary8> >();

    test_functions< fifi::log_table<fifi::binary8> >();
    test_functions< fifi::log_table<fifi::binary16> >();

    test_functions< fifi::extended_log_table<fifi::binary8> >();
    test_functions< fifi::extended_log_table<fifi::binary16> >();

    test_functions< fifi::optimal_prime<fifi::prime2325> >();


    // Just also run the default fields
    test_functions< fifi::default_field_impl<fifi::binary>::type >();
    test_functions< fifi::default_field_impl<fifi::binary8>::type >();
    test_functions< fifi::default_field_impl<fifi::binary16>::type >();
}


