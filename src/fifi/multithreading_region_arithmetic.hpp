// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>
#include <vector>

#include <boost/thread.hpp>
#include "is_packed_constant.hpp"

namespace fifi
{
    /// Performs region arithmetic in parallel.
    template<class Super>
    class multithreading_region_arithmetic : public Super
    {
    public:

        /// The field type
        typedef typename Super::field_type field_type;

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

    public:

        multithreading_region_arithmetic() :
            m_threads(1),
            m_length(1)
        { }

        uint32_t threads() const
        {
            return m_threads;
        }

        void set_threads(uint32_t threads)
        {
            assert(threads > 0);
            assert((length() % threads) == 0);

            m_threads = threads;

            Super::set_length(length() / threads);
        }

        void set_length(uint32_t length)
        {
            assert(length > 0);
            assert((length % m_threads) == 0);

            m_length = length;

            Super::set_length(length / m_threads);
        }

        uint32_t length() const
        {
            return m_length;
        }

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
            for (uint32_t i = 0; i < m_threads; ++i)
            {
                threads.push_back(boost::thread(
                    boost::bind(function, *this, dest+(i*Super::length()),
                                src+(i*Super::length()))
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
            for (uint32_t i = 0; i < m_threads; ++i)
            {
                threads.push_back(boost::thread(
                    boost::bind(function, *this, dest+(i*Super::length()), constant)
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
            for (uint32_t i = 0; i < m_threads; ++i)
            {
                threads.push_back(boost::thread(
                    boost::bind(function, *this, dest+(i*Super::length()),
                                src+(i*Super::length()), constant)
                ));
            }

            for(auto& thread : threads){
                thread.join();
            }
        }

    protected:

        uint32_t m_threads;
        uint32_t m_length;
    };
}
