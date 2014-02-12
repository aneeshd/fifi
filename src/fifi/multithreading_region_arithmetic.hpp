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
#include <string>

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
        {
             print(std::string("constructor"));
        }

        void set_length(uint32_t length)
        {
            stop();
            Super::set_length(length);
            start();
        }

        void set_threads(uint32_t threads)
        {
            stop();
            Super::set_threads(threads);
            start();
        }

        void region_add(value_type* dest, const value_type* src) const
        {
            assert(m_started);
            print(std::string("region_add"));


            m_dest = dest;
            m_src = const_cast<value_type*>(src);

            m_work_left = Super::threads();

            boost::unique_lock<boost::mutex> lock( m_coordination );

            print(std::string("Before notifying workers"));
            m_work_start.notify_all();
            m_work_done.wait(lock);
            print(std::string("All done!"));
        }

        virtual ~multithreading_region_arithmetic()
        {
            print(std::string("destructor"));
            stop();
        }

    private:

        void start() const
        {
            print(std::string("start"));
            m_started = true;
            m_workers_ready = 0;

            for(uint32_t i = 0; i < Super::threads(); ++i)
            {
                print(std::string("adding thread ") + std::to_string(i));
                m_threads.push_back(boost::thread(
                    boost::bind(
                        &multithreading_region_arithmetic::worker_thread,
                        this, i)
                ));
            }

            boost::unique_lock<boost::mutex> lock( m_coordination );

            m_workers_started.wait(lock);
            print(std::string("started"));
        }

        void stop() const
        {
            print(std::string("stop"));
            m_started = false;
            m_work_start.notify_all();
            for (auto& thread : m_threads)
            {
                thread.join();
            }
            m_threads.clear();
            print(std::string("stopped"));
        }

        void worker_thread(uint32_t index) const
        {

            bool initial = true;
            print(std::string("worker_thread"));
            while (1)
            {
                {
                    boost::unique_lock<boost::mutex> lock( m_coordination );
                    print(std::string("Waiting for work ") + std::to_string(index));

                    if (initial)
                    {
                        m_workers_started_lock.lock();
                        ++m_workers_ready;
                        if (m_workers_ready == Super::threads())
                            m_workers_started.notify_one();
                        m_workers_started_lock.unlock();
                        initial = false;
                    }

                    m_work_start.wait(lock);
                }

                if(!m_started)
                    return;

                print(std::string("Work starting ") + std::to_string(index));

                Super::region_add(m_dest + (index * Super::length()),
                                  m_src  + (index * Super::length()));

                print(std::string("after region add ") + std::to_string(index));

                m_work_done_lock.lock();
                m_work_left--;
                if (m_work_left == 0)
                    m_work_done.notify_one();
                m_work_done_lock.unlock();
            }
        }

        void print(const std::string& text) const
        {
            m_print_lock.lock();
            std::cout << text << std::endl;
            m_print_lock.unlock();
        }

    private:

        mutable std::atomic<bool> m_started;
        mutable std::atomic<uint32_t> m_workers_ready;

        mutable value_type* m_dest;
        mutable value_type* m_src;
        mutable std::atomic<uint32_t> m_work_left;
        mutable boost::mutex m_work_done_lock;
        mutable boost::mutex m_workers_started_lock;

        mutable boost::condition_variable m_work_start;
        mutable boost::condition_variable m_workers_started;
        mutable boost::condition_variable m_work_done;
        mutable boost::mutex m_coordination;

        mutable std::vector<boost::thread> m_threads;

        mutable boost::mutex m_print_lock;
    };
}
