// Copyright Steinwurf APS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE_1_0.txt or
// http://www.steinwurf.dk/licensing
#ifndef FIFI_ARITHMETICS_H
#define FIFI_ARITHMETICS_H

#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>

#include "field_types.h"
#include "log_table.h"
#include "extended_log_table.h"
#include "full_table.h"
#include "is_binary.h"
#include "disable_if_binary.h"

// Certain applications e.g. Error Correcting Codes (ECC)
// perform specific compound operations. These operations
// can for certain field implementations be implemented
// faster or smarter. This file provides commonly used
// operations.

namespace fifi
{
    
    // Generic version of adding two buffers
    //
    // Provides: dest[i] = dest[i] + src[i]
    // @param field, the field implementation
    // @param dest, the destination element buffer
    // @param src, the source element buffer
    // @param length, the size of destination and source buffers
    //        in value_type elements
    template<class FieldImpl>
    void add(const FieldImpl &field,
             typename FieldImpl::value_type *dest,
             const typename FieldImpl::value_type *src,
             uint32_t length)
    {
	assert(dest != 0);
	assert(src != 0);
	assert(length > 0);
        
	for(uint32_t i = 0; i < length; ++i)
	{
	    dest[i] = field.add(dest[i], src[i]);
	}
    }

    // Generic version of subtract two buffers
    //
    // Provides: dest[i] = dest[i] - src[i]
    // @param field, the field implementation
    // @param dest, the destination element buffer
    // @param src, the source element buffer
    // @param length, the size of destination and source buffers
    //        in value_type elements
    template<class FieldImpl>
    void subtract(const FieldImpl &field,
                  typename FieldImpl::value_type *dest,
                  const typename FieldImpl::value_type *src,
                  uint32_t length)
    {
	assert(dest != 0);
	assert(src != 0);
	assert(length > 0);
        
	for(uint32_t i = 0; i < length; ++i)
	{
	    dest[i] = field.subtract(dest[i], src[i]);
	}
    }

    // Generic version of multiplying two buffers
    //
    // Provides: dest[i] = dest[i] * src[i]
    // @param field, the field implementation
    // @param dest, the destination element buffer
    // @param src, the source element buffer
    // @param length, the size of destination and source buffers
    //        in value_type elements
    template<class FieldImpl>
    void multiply(const FieldImpl &field,
                  typename FieldImpl::value_type *dest,
                  const typename FieldImpl::value_type *src,
                  uint32_t length)
    {
	assert(dest != 0);
	assert(src != 0);
	assert(length > 0);
        
	for(uint32_t i = 0; i < length; ++i)
	{
	    dest[i] = field.multiply(dest[i], src[i]);
	}
    }

    // Generic version of multiplying a buffer with a constant
    //
    // Provides: dest[i] = dest[i] * constant
    // @param field, the field implementation
    // @param dest, the destination element buffer
    // @param constant, the constant multiplier
    // @param length, the size of destination and source buffers
    //        in value_type elements
    template<class FieldImpl>
    void multiply_constant(const FieldImpl &field,
                           typename FieldImpl::value_type constant,
                           typename FieldImpl::value_type *dest,
                           uint32_t length)
    {
	assert(dest != 0);
	assert(length > 0);

        typedef typename FieldImpl::field_type field_type;

        // This function does not work for the binary field
        // since multiplying with a constant does not behave as
        // expected (the binary field does a bit-wise AND operation).   
        BOOST_STATIC_ASSERT((is_binary<field_type>::value == false));
        
	for(uint32_t i = 0; i < length; ++i)
	{
	    dest[i] = field.multiply(dest[i], constant);
	}
    }

    // The overload is taken for binary fields for the multiply_constant(...)
    // functions. Since the binary field only consists of elements {0,1}
    // therefore we either zero the buffer or leave it untouched.
    //
    // @see generic version of multiply_constant(...) for parameters
    template<template <class> class FieldImpl>
    void multiply_constant(const FieldImpl<binary> &/*field*/,
                           typename binary::value_type constant,
                           typename binary::value_type *dest,
                           uint32_t length)
    {
	assert(dest != 0);
	assert(length > 0);

        // Only {0,1} allowed
	assert(constant == 0 || constant == 1); 
	
	if(constant == 0)
        {
            std::fill_n(dest, length, 0);
        }
    }
    
    // Generic version of adding two buffers after multiplying
    // with a constant.
    //
    // Provides: dest[i] = dest[i] + (src[i] * constant)
    // @param field, the field implementation
    // @param constant, the constant field value used for
    //        the multiplication
    // @param dest, the destination element buffer
    // @param src, the source element buffer
    // @param length, the size of destination and source buffers
    //        in value_type elements
    template<class FieldImpl>
    void multiply_add(const FieldImpl &field,
                      typename FieldImpl::value_type constant,
		      typename FieldImpl::value_type *dest,
		      const typename FieldImpl::value_type *src,
		      uint32_t length)
    {
	assert(dest != 0);
	assert(src != 0);
	assert(length > 0);

        typedef typename FieldImpl::field_type field_type;

        // This function does not work for the binary field
        // since the multiply function does not behave correctly
        // so make sure that we do not use it.
        BOOST_STATIC_ASSERT((is_binary<field_type>::value == false));
        
	if(constant == 0)
	    return;

        typedef typename FieldImpl::value_type value_type;
        
	for(uint32_t i = 0; i < length; ++i)
	{
	    value_type multiplied = field.multiply(src[i], constant);
	    dest[i] = field.add(dest[i], multiplied);
	}
    }
    
    // This overload is for the full table implementation where
    // a small optimization is possible when adding two buffers
    // after multiplying with a constant.
    //
    // @see generic version of multiply_add(...) for parameters
    // template<class Field>
    // typename disable_if_binary<Field>::type
    // multiply_add(const full_table<Field> &field,
    //     	 typename Field::value_type constant,
    //     	 typename Field::value_type *dest,
    //     	 const typename Field::value_type *src,
    //     	 uint32_t length)
    // {
    //     assert(dest != 0);
    //     assert(src  != 0);
    //     assert(length > 0);
        
    //     // This function does not work for the binary field
    //     // since the multiply function does not behave correctly
    //     // so make sure that we do not use it.
    //     BOOST_STATIC_ASSERT((is_binary<Field>::value == false));
        
    //     if(constant == 0)
    //         return;

    //     typedef typename Field::value_type value_type;

    //     // In the multiplication table the constant is used to indentify
    //     // the row number. Therefore the constant is used as an offset,
    //     // and all possible results can then be accessed on the following
    //     // number of indices indices.
    //     const value_type *offset =
    //         &field.m_multtable[(constant << Field::degree)];

    //     for(uint32_t i = 0; i < length; ++i)
    //     {
    //         dest[i] = field.add(dest[i], offset[src[i]]);
    //     }
    // }
    
    // The overload is taken for binary fields for the multiply_add(..)
    // functions. Since the binary field only consists of elements {0,1}
    // therefore it only makes sense to do the addition.
    //
    // @see generic version of multiply_add(...) for parameters
    template<template<class> class FieldImpl>
    void multiply_add(const FieldImpl<binary> &field,
                      typename binary::value_type constant,
                      typename binary::value_type *dest,
		      const typename binary::value_type *src,
		      uint32_t length)
    {
	assert(dest != 0);
	assert(src  != 0);
	assert(length > 0);

        // Only {0,1} allowed
	assert(constant == 0 || constant == 1); 
	
	if(constant == 0) // Do nothing
        {
            return;
        }
        else // Add the two buffers
        {
            add(field, dest, src, length);
        }
    }

    // Generic version of subtracting two buffers after multiplying
    // with a constant.
    //
    // Provides: dest[i] = dest[i] - (src[i] * constant)
    // @param field, the field implementation
    // @param constant, the constant field value used for
    //        the multiplication
    // @param dest, the destination element buffer
    // @param src, the source element buffer
    // @param length, the size of destination and source buffers
    //        in value_type elements
    template<class FieldImpl>
    void multiply_subtract(const FieldImpl &field,
                           typename FieldImpl::value_type constant,
                           typename FieldImpl::value_type *dest,
                           const typename FieldImpl::value_type *src,
                           uint32_t length)
    {
	assert(dest != 0);
	assert(src != 0);
	assert(length > 0);

        typedef typename FieldImpl::field_type field_type;

        // This function does not work for the binary field
        // since the multiply function does not behave correctly
        // so make sure that we do not use it.
        BOOST_STATIC_ASSERT((is_binary<field_type>::value == false));
        
	if(constant == 0)
	    return;

        typedef typename FieldImpl::value_type value_type;
        
	for(uint32_t i = 0; i < length; ++i)
	{
	    value_type multiplied = field.multiply(src[i], constant);
	    dest[i] = field.subtract(dest[i], multiplied);
	}
    }

    // This overload is for the full table implementation where
    // a small optimization is possible when subtracting two buffers
    // after multiplying with a constant.
    //
    // @see generic version of multiply_subtract(...) for parameters
    template<class Field>
    typename disable_if_binary<Field>::type
    multiply_subtract(const full_table<Field> &field,
                      typename Field::value_type constant,
                      typename Field::value_type *dest,
                      const typename Field::value_type *src,
                      uint32_t length)
    {
	assert(dest != 0);
	assert(src != 0);
	assert(length > 0);
        
        // This function does not work for the binary field
        // since the multiply function does not behave correctly
        // so make sure that we do not use it.
        BOOST_STATIC_ASSERT((is_binary<Field>::value == false));
        
	if(constant == 0)
	    return;

        typedef typename Field::value_type value_type;

        // In the multiplication table the constant is used to indentify
        // the row number. Therefore the constant is used as an offset,
        // and all possible results can then be accessed on the following
        // number of indices indices.
        const value_type *offset =
            &field.m_multtable[(constant << Field::degree)];

	for(uint32_t i = 0; i < length; ++i)
	{
	    dest[i] = field.subtract(dest[i], offset[src[i]]);
	}
    }

    // The overload is taken for binary fields for the multiply_subtract(..)
    // functions. Since the binary field only consists of elements {0,1}
    // therefore it only makes sense to do the subtraction.
    //
    // @see generic version of multiply_subtract(...) for parameters
    template<template<class> class FieldImpl>
    void multiply_subtract(const FieldImpl<binary> &field,
                           typename binary::value_type constant,
                           typename binary::value_type *dest,
                           const typename binary::value_type *src,
                           uint32_t length)
    {
	assert(dest != 0);
	assert(src != 0);
	assert(length > 0);

        // Only {0,1} allowed
	assert(constant == 0 || constant == 1); 
	
	if(constant == 0) // Do nothing
        {
            return;
        }
        else // Subtract the two buffers
        {
            subtract(field, dest, src, length);
        }
    }
}

#endif

