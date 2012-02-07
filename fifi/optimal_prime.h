// Copyright Steinwurf APS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE_1_0.txt or
// http://www.steinwurf.dk/licensing
#ifndef FIFI_OPTIMAL_PRIME_H
#define FIFI_OPTIMAL_PRIME_H

#include <stdint.h>
#include "field_types.h"

namespace fifi
{

    template<class Field>
    class optimal_prime
    {
    public:
        // Typedef of the data type used for each field element
        typedef typename Field::value_type value_type;

        // Typedef of the field type used
        typedef Field field_type;

    public:
        // Operator performing the field multiplication
        // @param element_two, the first field element
        // @param element_two, the second field element
        // @return the result after multiplication
        value_type multiply(value_type element_one, value_type element_two) const;

        // Operator finding the inverse of a field element
        // @param element, the field element whos inverse we wish to find
        // @return the inverse element
        value_type divide(value_type numerator, value_type denominator) const;

        // Operator performing the field division
        // @param numerator, the numerator field element
        // @param denominator, the denominator field element
        // @return the result after division
        value_type invert(value_type element) const;
        
        // Performs the field addition
        // @param element_two, the first field element
        // @param element_two, the second field element
        // @return the result after addition
        value_type add(value_type element_one, value_type element_two) const;

        // Performs the field subtraction
        // @param element_two, the first field element
        // @param element_two, the second field element
        // @return the result after subtraction
        value_type subtract(value_type element_one, value_type element_two) const;
    };

    //  Specilization for the (2^32 - 5) prime field
    template<>
    inline optimal_prime<prime2325>::value_type optimal_prime<prime2325>::multiply(value_type element_one, value_type element_two) const
    {
        uint64_t c = (uint64_t)element_one * (uint64_t)element_two;
        uint64_t h1 = c >> 32;
        uint64_t l1 = c & 0xffffffff;

        c = h1 * 5;
        uint64_t h2 = c >> 32;
        uint64_t l2 = c & 0xffffffff;

        c = h2 * 5;
        c = c + l1 + l2;

        c = c >= prime2325::prime ? c - prime2325::prime : c;

        return c;
    }

    template<>
    inline optimal_prime<prime2325>::value_type optimal_prime<prime2325>::invert(value_type a) const
    {
        assert(a > 0);
        assert(a < prime2325::prime);

        int64_t x0 = 1;
        int64_t x1 = 0;

        value_type b = prime2325::prime;
        int64_t x = 0;
        value_type q = 0;
        value_type r = 0;

        while(a != 1)
        {
            q = b / a;
            r = b - (q * a);

            b = a;
            a = r;
            x = x1 - x0*q;

            x1 = x0;
            x0 = x;
        }

        x = x < 0 ? (x + prime2325::prime) : x;

        return x;
    }

    template<>
    inline optimal_prime<prime2325>::value_type
    optimal_prime<prime2325>::divide(value_type numerator, value_type denominator) const
    {
        value_type inverse = invert(denominator);
        return multiply(numerator, inverse);
    }

    template<>
    inline optimal_prime<prime2325>::value_type
    optimal_prime<prime2325>::add(value_type element_one, value_type element_two) const
    {
        int64_t sum = element_one + element_two;
        sum = sum < prime2325::prime ? sum : sum - prime2325::prime;

        return sum;
    }

    template<>
    inline optimal_prime<prime2325>::value_type
    optimal_prime<prime2325>::subtract(value_type element_one, value_type element_two) const
    {
        int64_t sum = element_one - element_two;
        sum = sum < 0 ? sum + prime2325::prime : sum;

        return sum;
    }

//    template<>
//    optimal_prime<prime2325>::value_type optimal_prime<prime2325>::multiplyASM(optimal_prime<prime2325>::value_type a, optimal_prime<prime2325>::value_type b)
//    {

//        /**
//          * Not working
//          */

//        __asm__("mul %[b];"           // Multiply a and b
//                "movl %%eax, %%ebx;"  // Move low bits to %ebx
//                "movl $5, %[b];"      // Save 5 in b's register
//                "movl %%edx, %%eax;"  // Move high bits to %eax
//                "mul %[b];"           // Multiply high bits with 5
//                "addl %%eax, %%ebx;"  // Sum the low order bits
//                "movl %%edx, %%eax;"  // Move high bits to %eax
//                "mul %[b];"           // Multiply high bits with 5
//                "addl %%eax, %%ebx;"
//                "movl %%ebx, %%eax;"
//                : [a] "+a" (a)
//                : [b] "r" (b)
//                : "cc", "ebx", "%edx");

//        return a;
//    }

}

#endif

