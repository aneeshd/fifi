// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>
#include <type_traits>

#include "prime2325.hpp"

namespace fifi
{
    /// This implementation allows finite field arithmetics in the
    /// prime fields in this case where the characteristic of the
    /// field is different than two.
    template<class Super>
    class optimal_prime_arithmetic : public Super
    {
    public:

        /// @copydoc layer::value_type
        typedef typename Super::value_type value_type;

        /// @copydoc layer::field_type
        typedef typename Super::field_type field_type;

        /// Static field check
        static_assert(std::is_same<prime2325, field_type>::value,
                      "This layer only support the 2^32 - 5 prime field");

    public:

        /// Specialization for the (2^32 - 5) prime field. Multiplication is
        /// based on a clever way of doing modulo. See:
        ///
        ///   S. B. Mohan  and  B. S. Adiga, Electronics  “Fast algorithms for
        ///   implementing rsa public key cryptosystem" Electronics  Letters,
        ///   vol.  21, 1985.
        /// @copydoc layer::multiply(value_type, value_type) const
        value_type multiply(value_type element_one,
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

            c = c >= field_type::prime ? c - field_type::prime : c;

            return static_cast<value_type>(c);

        }

        /// Specialization for the (2^32 - 5) prime field. In this
        /// case division is simply implemented using multiplication
        /// with the inverse.
        /// @copydoc layer::divide(value_type, value_type) const
        value_type divide(value_type a, value_type b) const
        {
            value_type inverse = invert(b);
            return multiply(a, inverse);
        }

        /// Specialization for the (2^32 - 5) prime field. This
        /// algorithm used a modified version of the Extended
        /// Euclidean algorithm, which essentially solves the a*x +
        /// b*y = gcd(a,b) in this case b = 2^32 - 5 which is a prime
        /// therefore we know that gcd(a,b) = 1 also since we do all
        /// calculations mod 2^32 - 5 we see that b*y must become
        /// 0. We are left with calculating a*x = 1 in which case x
        /// must be the inverse of a.
        /// @copydoc layer::invert(value_type, value_type) const
        value_type invert(value_type element) const
        {
            assert(element > 0);
            assert(element < field_type::prime);

            int64_t q  = 0;

            int64_t x  = 0;
            int64_t x0 = 0;
            int64_t x1 = 1;

            int64_t r  = 0;
            int64_t r0 = field_type::prime;
            int64_t r1 = element;

            while (r1 != 1)
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

            x1 = x1 < 0 ? (x1 + field_type::prime) : x1;

            return static_cast<value_type>(x1);
        }

        /// Specialization for the (2^32 - 5) prime field
        /// @copydoc layer::add(value_type, value_type) const
        value_type add(value_type element_one, value_type element_two) const
        {
            element_one += element_two;

            // If element_one >= element_two the we did not have a 32 bit
            // overflow
            //
            //     1 if no overflow
            //     0 if overflow
            //
            // This means that (element_one >= element_two) - 1 becomes:
            //
            //     0 or 0x00000000 if no overflow
            //     -1 or 0xffffffff if overflow
            //
            // An overflow is equivalent to a mod 2^32 since
            // we are working 2^32 - 5 we simply add 5 to
            // compensate
            element_one += (5 & ((element_one >= element_two) - 1));

            // Conditional move version
            // element_one = element_one >= field_type::prime ?
            //    element_one - field_type::prime : element_one;

            // The line below does the following:
            // field_type::prime > element_one becomes:
            //
            //     1 if prime is larger
            //     0 if prime is smaller or equal
            //
            // If that means the (field_type::prime > element_one) - 1 becomes:
            //
            //     0 or 0x00000000 if prime is larger
            //     -1 or 0xffffffff if the prime is smaller or equal
            //
            // This mask is then used to determine whether the subtraction
            // with the prime statement is in effect of not
            //
            // Our measurements show that this branch-less version
            // yields a significant performance gain over both the
            // branched and conditional move versions
            element_one -=
                (field_type::prime & ((field_type::prime > element_one) - 1));

            return element_one;
        }

        /// Specialization for the (2^32 - 5) prime field
        /// @copydoc layer::subtract(value_type, value_type) const
        value_type subtract(value_type element_one,
                            value_type element_two) const
        {
            // If element_one >= element_two then we will not have an
            // underflow
            //
            //     1 if no underflow
            //     0 if underflow
            //
            // This means that (element_one >= element_two) - 1 becomes:
            //
            //     0 or 0x00000000 if no underflow
            //     -1 or 0xffffffff if underflow
            //
            // An underflow is equivalent to a mod 2^32 since
            // we are working 2^32 - 5 we simply subtract 5 to
            // compensate

            // Different from addition there is no way we can end up
            // above the prime so we don't have to do anything else

            return (element_one - element_two) +
                (-5 & ((element_one >= element_two) - 1));
        }
    };
}
