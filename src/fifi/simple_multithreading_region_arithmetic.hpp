// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>
#include <vector>

#include <boost/thread.hpp>

namespace fifi
{
    /// Performs region arithmetic in parallel.
    template<class Super>
    class simple_multithreading_region_arithmetic : public Super
    {
    public:

        /// The field type
        typedef typename Super::field_type field_type;

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

    public:

        void region_add(value_type* dest, const value_type* src) const
        {
            binary_parallel(&Super::region_add, dest, src);
        }

        void region_subtract(value_type* dest, const value_type* src) const
        {
            binary_parallel(&Super::region_subtract, dest, src);
        }

        void region_divide(value_type* dest, const value_type* src) const
        {
            binary_parallel(&Super::region_divide, dest, src);
        }

        void region_multiply(value_type* dest, const value_type* src) const
        {
            binary_parallel(&Super::region_multiply, dest, src);
        }

        void region_multiply_constant(value_type* dest,
                                      value_type constant) const
        {
            binary_const_parallel(&Super::region_multiply_constant, dest,
                                  constant);
        }

        void region_multiply_add(value_type* dest, const value_type* src,
                                 value_type constant) const
        {
            binary_ptr_ptr_const_parallel(&Super::region_multiply_add, dest,
                                          src, constant);
        }

        void region_multiply_subtract(value_type* dest, const value_type* src,
                                      value_type constant) const
        {
            binary_ptr_ptr_const_parallel(&Super::region_multiply_subtract,
                                          dest, src, constant);
        }

    private:

        template<class Function>
        void binary_parallel(Function function, value_type* dest,
                             const value_type* src) const
        {
            std::vector<boost::thread> threads;
            for (uint32_t i = 0; i < Super::threads(); ++i)
            {
                threads.push_back(boost::thread(
                    boost::bind(function, *this, dest+(i*Super::slice()),
                                src+(i*Super::slice()))
                ));
            }

            for(auto& thread : threads){
                thread.join();
            }
        }

        template<class Function>
        void binary_const_parallel(Function function, value_type* dest,
                                   value_type constant) const
        {
            std::vector<boost::thread> threads;
            for (uint32_t i = 0; i < Super::threads(); ++i)
            {
                threads.push_back(boost::thread(
                    boost::bind(function, *this, dest+(i*Super::slice()), constant)
                ));
            }

            for(auto& thread : threads){
                thread.join();
            }
        }

        template<class Function>
        void binary_ptr_ptr_const_parallel(Function function, value_type* dest,
                                           const value_type* src,
                                           value_type constant) const
        {
            std::vector<boost::thread> threads;
            for (uint32_t i = 0; i < Super::threads(); ++i)
            {
                threads.push_back(boost::thread(
                    boost::bind(function, *this, dest+(i*Super::slice()),
                                src+(i*Super::slice()), constant)
                ));
            }

            for(auto& thread : threads){
                thread.join();
            }
        }
    };
}
