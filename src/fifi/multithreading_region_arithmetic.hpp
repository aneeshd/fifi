// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <atomic>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
#include <utility>
#include <functional>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <queue>
#include <boost/thread.hpp>

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
            m_started(false)
        { }

        void set_length(uint32_t length)
        {
            stop();
            Super::set_length(length);
        }

        void set_threads(uint32_t threads)
        {
            stop();
            Super::set_threads(threads);
        }

        void region_add(value_type* dest, const value_type* src) const
        {
            std::cout << "region_add" << std::endl;
            if (!m_started)
                start();

            m_dest = dest;
            m_src = const_cast<value_type*>(src);

            m_work_left = Super::threads();

            boost::unique_lock<boost::mutex> lock( m_coordination );

            std::cout << "Before notifying workers" << std::endl;
            m_work_start.notify_all();
            m_work_done.wait(lock);
            std::cout << "All done!" << std::endl;
        }

        ~multithreading_region_arithmetic()
        {
            stop();
        }

    private:

        void start() const
        {
            std::cout << "start" << std::endl;
            m_started = true;
            m_workers_ready = 0;

            for(uint32_t i = 0; i < Super::threads(); ++i)
            {
                m_threads.push_back(boost::thread(
                    boost::bind(
                        &multithreading_region_arithmetic::worker_thread,
                        this, i)
                ));
            }

            while(m_workers_ready < Super::threads())
                continue;
        }

        void stop() const
        {
            std::cout << "stop" << std::endl;
            m_started = false;
            m_work_start.notify_all();
            for (auto& thread : m_threads)
            {
                thread.join();
            }
            m_threads.clear();
        }

        void worker_thread(uint32_t index) const
        {

            bool initial = true;
            std::cout << "worker_thread" << std::endl;
            while (1)
            {
                {
                    boost::unique_lock<boost::mutex> lock( m_coordination );
                    std::cout << "Waiting for work " << boost::this_thread::get_id()
                              << std::endl;

                    if (initial)
                    {
                        ++m_workers_ready;
                        initial = false;
                    }

                    m_work_start.wait(lock);
                }

                if(!m_started)
                    return;

                std::cout << "Work starting " << boost::this_thread::get_id()
                              << std::endl;

                Super::region_add(m_dest + (index * Super::length()),
                                  m_src  + (index * Super::length()));

                std::cout << "after region add" << std::endl;

                m_work_done_lock.lock();
                m_work_left--;
                if (m_work_left == 0)
                    m_work_done.notify_one();
                m_work_done_lock.unlock();
            }
        }

    private:

        mutable std::atomic<bool> m_started;
        mutable std::atomic<uint32_t> m_workers_ready;

        mutable value_type* m_dest;
        mutable value_type* m_src;
        mutable std::atomic<uint32_t> m_work_left;
        mutable boost::mutex m_work_done_lock;

        mutable boost::condition_variable m_work_start;
        mutable boost::condition_variable m_work_done;
        mutable boost::mutex m_coordination;

        mutable std::vector<boost::thread> m_threads;
    };
}
