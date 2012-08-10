// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#ifndef FIFI_OPTIMAL_PRIME_H
#define FIFI_OPTIMAL_PRIME_H

#include <stdint.h>
#include "field_types.h"

namespace fifi
{

    /// This implemtnation allows finite field arithmetics in the
    /// prime fields in this case where the characteristic of the
    /// field is different than two.
    template<class Field>
    class optimal_prime
    {
    public:
        /// Typedef of the data type used for each field element
        typedef typename Field::value_type value_type;

        /// Typedef of the field type used
        typedef Field field_type;

    public:
        /// Operator performing the field multiplication
        /// @param element_one the first field element
        /// @param element_two the second field element
        /// @return the result after multiplication
        value_type multiply(value_type element_one, value_type element_two) const;

        /// Operator performing the field division
        /// @param numerator the numerator field element
        /// @param denominator the denominator field element
        /// @return the result after division
        value_type divide(value_type numerator, value_type denominator) const;

        /// Operator finding the inverse of a field element
        /// @param element the field element whos inverse we wish to find
        /// @return the inverse element
        value_type invert(value_type element) const;

        /// Performs the field addition
        /// @param element_one the first field element
        /// @param element_two the second field element
        /// @return the result after addition
        value_type add(value_type element_one, value_type element_two) const;

        /// Performs the field subtraction
        /// @param element_one the first field element
        /// @param element_two the second field element
        /// @return the result after subtraction
        value_type subtract(value_type element_one, value_type element_two) const;

    };

    /// Specialization for the (2^32 - 5) prime field. Multiplication is
    /// based on a clever way of doing modulo. See:
    ///
    ///   S. B. Mohan  and  B. S. Adiga, Electronics  “Fast algorithms for
    ///   implementing rsa public key cryptosystem" Electronics  Letters,
    ///   vol.  21, 1985.
    template<>
    inline optimal_prime<prime2325>::value_type
    optimal_prime<prime2325>::multiply(value_type element_one,
                                       value_type element_two) const
    {
        uint64_t c = static_cast<uint64_t>(element_one) *
                     static_cast<uint64_t>(element_two);

        uint32_t l1 = c & 0xffffffff;
        c = c >> 32;
        c = c * 5;

        uint32_t l2 = c & 0xffffffff;
        c = c >> 32;
        c = c * 5;

        c = c + l1 + l2;

        c = c >= prime2325::prime ? c - prime2325::prime : c;

        return static_cast<value_type>(c);

    }

    /// Specialization for the (2^32 - 5) prime field. This algorithm
    /// used a modified version of the Extended Euclidean algorithm,
    /// which essentially solves the a*x + b*y = gcd(a,b) in this case
    /// b = 2^32 - 5 which is a prime therefore we know that gcd(a,b) = 1
    /// also since we do all calculations mod 2^32 - 5 we see that b*y
    /// must become 0. Therefore we are left with calculating a*x = 1
    /// in which case x must be the inverse of a.
    template<>
    inline optimal_prime<prime2325>::value_type
    optimal_prime<prime2325>::invert(value_type a) const
    {
        assert(a > 0);
        assert(a < prime2325::prime);

        int64_t q  = 0;

        int64_t x  = 0;
        int64_t x0 = 0;
        int64_t x1 = 1;

        int64_t r  = 0;
        int64_t r0 = prime2325::prime;
        int64_t r1 = a;

        while(r1 != 1)
        {
            // Compute the next remainder
            q = r0 / r1;
            r = r0 - (q * r1);
            x = x0 - (q * x1);

            // Store the results
            r0 = r1;
            r1 = r;
            x0 = x1;
            x1 = x;
        }

        x1 = x1 < 0 ? (x1 + prime2325::prime) : x1;

        return static_cast<value_type>(x1);
    }

    /// Specialization for the (2^32 - 5) prime field. In this
    /// case division is simply implemented using multiplication
    /// with the inverse.
    template<>
    inline optimal_prime<prime2325>::value_type
    optimal_prime<prime2325>::divide(value_type numerator,
                                     value_type denominator) const
    {
        value_type inverse = invert(denominator);
        return multiply(numerator, inverse);
    }

    /// Specialization for the (2^32 - 5) prime field
    template<>
    inline optimal_prime<prime2325>::value_type
    optimal_prime<prime2325>::add(value_type element_one,
                                  value_type element_two) const
    {
        element_one = element_one + element_two;
        element_one = element_one + (5 & ((element_one >= element_two) - 1));


        element_one = element_one + (
                (-prime2325::prime) & ((prime2325::prime > element_one) - 1));

        return element_one;
    }

    /// Specialization for the (2^32 - 5) prime field
    template<>
    inline optimal_prime<prime2325>::value_type
    optimal_prime<prime2325>::subtract(value_type element_one,
                                       value_type element_two) const
    {
        // Se explanation for the funny business below in arithmetics.h
        // specialization of subtract for optimal_prime<prime2325>
        return (element_one - element_two)
            + (-5 & ((element_one >= element_two) - 1));
    }

}

#endif

