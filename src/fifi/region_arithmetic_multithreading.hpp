// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cassert>
#include <cstdint>
#include <thread>

#include "is_packed_constant.hpp"

namespace fifi
{

    /// Performs region arithmetic in parallel.
    template<class Super>
    class region_arithmetic_multithreading : public Super
    {
    public:

        /// The field type
        typedef typename Super::field_type field_type;

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

    public:

        region_arithmetic_multithreading() :
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
            assert((m_length % threads) == 0);

            m_threads = threads;

            Super::set_length(m_length / m_threads);
        }

        void set_length(uint32_t length)
        {
            assert(length > 0);
            assert((length % m_threads) == 0);

            m_length = length;

            Super::set_length(m_length / m_threads);
        }

        uint32_t length() const
        {
            return m_length;
        }

        void region_add(value_type* dest, const value_type* src) const
        {
            std::vector<std::thread> threads;
            for (uint32_t i = 0; i < m_threads; ++i)
            {
                Super::region_add(dest+(i*Super::length()), src+(i*Super::length()));
            }
        }
        /*
        void region_subtract(value_type* dest, const value_type* src) const
        {

        }

        void region_divide(value_type* dest, const value_type* src) const
        {

        }

        void region_multiply(value_type* dest, const value_type* src) const
        {

        }

        void region_multiply_constant(
            value_type* dest, value_type constant) const
        {

        }

        void region_multiply_add(value_type* dest, const value_type* src,
                          value_type constant) const
        {

        }

        void region_multiply_subtract(value_type* dest, const value_type* src,
                                value_type constant) const
        {

        }
        */
    protected:

        uint32_t m_threads;
        uint32_t m_length;
    };
    /*
    template<class Function, FieldImpl>
    inline void check_results_binary(const Function &func, FieldImpl field)
    {
        uint32_t length = field::length();
        uint32_t slice =  length / m_threads;
        assert(length % threads == 0);

        field::set_length(slice);

        std::vector<std::thread> threads;

        for (uint32_t i = 0; i < m_threads; ++i)
        {
            threads.push_back(std::thread(func, field, dest, src));
        }

        for(auto& thread : threads){
            thread.join();
        }

        field.set_length(length);
    }
    */
}
