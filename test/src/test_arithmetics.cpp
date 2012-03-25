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
void test_multiply_add()
{
    // Test whether the multipy_add function computes the
    // correct results
    
    typedef typename FieldImpl::value_type value_type;
    typedef typename FieldImpl::field_type field_type;
    
    FieldImpl impl;

    uint32_t length = 100;
    
    value_type *dest = new value_type[length];
    value_type *src  = new value_type[length];

    value_type *dest_copy = new value_type[length];
    value_type *src_copy  = new value_type[length];
    
    for(uint32_t i = 0; i < length; ++i)
    {
	dest[i] = rand() % field_type::order;
	src[i] = rand() % field_type::order;
    }

    memcpy(dest_copy, dest, sizeof(value_type)*length);
    memcpy(src_copy, src, sizeof(value_type)*length);
    
    value_type coefficient = rand() % field_type::order;

    fifi::multiply_add(impl, coefficient, dest, src, length);

    // Now we verify that we have computed: dest[i] = dest[i] + (src[i]*c)
    for(uint32_t i = 0; i < length; ++i)
    {
	value_type multiplied = impl.multiply(src_copy[i], coefficient);
	value_type result = impl.add(dest_copy[i], multiplied);

	ASSERT_EQ(result, dest[i]);
    }
    
    delete [] dest;
    delete [] src;
    delete [] dest_copy;
    delete [] src_copy;
}

template<class FieldImpl>
void test_multiply_subtract()
{
    // Test whether the multipy_add function computes the
    // correct results
    
    typedef typename FieldImpl::value_type value_type;
    typedef typename FieldImpl::field_type field_type;
    
    FieldImpl impl;

    uint32_t length = 100;
    
    value_type *dest = new value_type[length];
    value_type *src  = new value_type[length];

    value_type *dest_copy = new value_type[length];
    value_type *src_copy  = new value_type[length];
    
    for(uint32_t i = 0; i < length; ++i)
    {
	dest[i] = rand() % field_type::order;
	src[i] = rand() % field_type::order;
    }

    memcpy(dest_copy, dest, sizeof(value_type)*length);
    memcpy(src_copy, src, sizeof(value_type)*length);
    
    value_type coefficient = rand() % field_type::order;

    fifi::multiply_subtract(impl, coefficient, dest, src, length);

    // Now we verify that we have computed: dest[i] = dest[i] - (src[i]*c)
    for(uint32_t i = 0; i < length; ++i)
    {
	value_type multiplied = impl.multiply(src_copy[i], coefficient);
	value_type result = impl.subtract(dest_copy[i], multiplied);

	ASSERT_EQ(result, dest[i]);
    }
    
    delete [] dest;
    delete [] src;
    delete [] dest_copy;
    delete [] src_copy;
}

TEST(test_arithmetics, MultiplyAdd)
{

    test_multiply_add< fifi::simple_online<fifi::binary> >();
    test_multiply_add< fifi::simple_online<fifi::binary8> >();
    test_multiply_add< fifi::simple_online<fifi::binary16> >();
    
    test_multiply_add< fifi::full_table<fifi::binary8> >();

    test_multiply_add< fifi::log_table<fifi::binary8> >();
    test_multiply_add< fifi::log_table<fifi::binary16> >();

    test_multiply_add< fifi::extended_log_table<fifi::binary8> >();
    test_multiply_add< fifi::extended_log_table<fifi::binary16> >();

    // Just also run the default fields 
    test_multiply_add< fifi::default_field_impl<fifi::binary>::type >();
    test_multiply_add< fifi::default_field_impl<fifi::binary8>::type >();
    test_multiply_add< fifi::default_field_impl<fifi::binary16>::type >();

}

TEST(test_arithmetics, MultiplySubtract)
{

    test_multiply_subtract< fifi::simple_online<fifi::binary> >();
    test_multiply_subtract< fifi::simple_online<fifi::binary8> >();
    test_multiply_subtract< fifi::simple_online<fifi::binary16> >();
    
    test_multiply_subtract< fifi::full_table<fifi::binary8> >();

    test_multiply_subtract< fifi::log_table<fifi::binary8> >();
    test_multiply_subtract< fifi::log_table<fifi::binary16> >();

    test_multiply_subtract< fifi::extended_log_table<fifi::binary8> >();
    test_multiply_subtract< fifi::extended_log_table<fifi::binary16> >();

    // Just also run the default fields 
    test_multiply_subtract< fifi::default_field_impl<fifi::binary>::type >();
    test_multiply_subtract< fifi::default_field_impl<fifi::binary8>::type >();
    test_multiply_subtract< fifi::default_field_impl<fifi::binary16>::type >();

}

