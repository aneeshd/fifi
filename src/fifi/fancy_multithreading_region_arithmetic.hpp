// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>
#include <functional>
#include <boost/thread/future.hpp>
#include <thread>
#include <vector>
#include <vector>

#include "thread_pool.hpp"

#include <iostream>
#include <string>

namespace fifi
{
    /// Performs region arithmetic in parallel.
    template<class Super>
    class fancy_multithreading_region_arithmetic : public Super
    {
    public:

        /// The field type
        typedef typename Super::field_type field_type;

        /// Typedef of the data type used for each field element
        typedef typename Super::value_type value_type;

    public:

        void set_length(uint32_t length)
        {
            std::cout << "set_length" << std::endl;
            m_pool.stop();
            Super::set_length(length);
            m_pool.start(Super::threads());
        }

        void set_threads(uint32_t threads)
        {
            std::cout << "set_threads" << std::endl;
            m_pool.stop();
            Super::set_threads(threads);
            m_pool.start(Super::threads());
        }

        void region_add(value_type* dest, const value_type* src) const
        {
            std::cout << "region_add" << std::endl;
            std::vector<std::future<void>> results;
            for (uint32_t i = 0; i < Super::threads(); ++i)
            {
                std::cout << i << std::endl;
                std::cout << "create functor" << std::endl;
                auto functor = std::bind(&fancy_multithreading_region_arithmetic::test, this, dest+(i*Super::slice()), src+(i*Super::slice()));
                std::cout << "add functor" << std::endl;
                auto task = std::packaged_task<int()>(functor);
                std::future<int> result = task.get_future();
                std::cout << "OMGOMGOMGOMGOMGOM" << std::endl;
                //results.push_back(m_pool.enqueue(functor));
                std::cout << "functor added" << std::endl;
            }

            std::cout << "waiting for threads to finish" << std::endl;

            for(auto& result : results){
                std::cout << "..." << std::endl;
                try {
                    std::cout << result.valid() << std::endl;
                    result.get();
                } catch (const std::future_error& e) {
                    std::cout << "Caught a future_error with code \"" << e.code()
                              << "\"\nMessage: \"" << e.what() << "\"\n";
                }
                std::cout << "one finished!" << std::endl;
            }
        }

        int test(value_type* dest, const value_type* src) const
        {
            return 1337;
        }

        ERROR!

    private:

        thread_pool m_pool;
    };
}
