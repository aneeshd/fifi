// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

namespace fifi
{

    template<class Super>
    class region_arithmetic : public Super
    {
    public:

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

        void add(value_type* dest, const value_type* src,
                 uint32_t length) const
        {
            for(uint32_t i = 0; i < length; ++i)
            {
                Super::packed_add(a[i], b[i]);
            }
        }

        void subtract(value_type* dest, const value_type* src,
                      uint32_t length) const
        {
            for(uint32_t i = 0; i < length; ++i)
            {
                Super::packed_subtract(a[i], b[i]);
            }
        }

        void divide(value_type* dest, const value_type* src,
                    uint32_t length) const
        {
            for(uint32_t i = 0; i < length; ++i)
            {
                Super::packed_divide(a[i], b[i]);
            }
        }

        void multiply(value_type* dest, const value_type* src,
                      uint32_t length) const
        {
            for(uint32_t i = 0; i < length; ++i)
            {
                Super::packed_multiply(a[i], b[i]);
            }
        }

        void multiply(value_type* dest, value_type constant,
                      uint32_t length) const
        {
            for(uint32_t i = 0; i < length; ++i)
            {
                Super::packed_multiply(a, b[i]);
            }
        }

        void multiply_add(value_type* dest, const value_type* src,
                          value_type constant, uint32_t length) const
        {
            for(uint32_t i = 0; i < length; ++i)
            {
                Super::packed_multiply(a[i], b[i]);
            }
        }

        void multiply_substract(value_type* dest, const value_type* src,
                          value_type constant, uint32_t length) const
        {
            for(uint32_t i = 0; i < length; ++i)
            {
                Super::packed_multiply(a[i], b[i]);
            }
        }

    };

}


