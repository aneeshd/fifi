// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing


#include <boost/thread.hpp>
#include <cassert>
#include <cstdint>
#include <functional>
#include <future>
#include <queue>
#include <vector>

#include <chrono>
#include <iostream>
#include <string>

namespace fifi
{
    class thread_pool
    {
    public:
        thread_pool() :
            m_stop(true)
        { }

        template<class Function>
        std::future<void> enqueue(Function function) const
        {
            print("enqueue");
            assert(!m_stop);
            print("not stopped");
            auto task = std::make_shared<std::packaged_task<void()>>(function);
            print("task created");

            // AARGH THIS TRHOWS!
            std::future<void> result = task->get_future();
            print("I GOT HEREEEE!!!!");
            {
                print("got future");
                boost::unique_lock<boost::mutex> lock(m_queue_mutex);
                print("locked queue");
                m_tasks.push([task](){ (*task)(); });
                print("task pushed");
            }
            print("task added");
            m_condition.notify_one();
            print("worker notified");
            return result;
        }

        virtual ~thread_pool()
        {
            print("~thread_pool");
            stop();
            print("~ended");
        }

        void start(uint32_t threads)
        {
            print("start ");
            print(std::to_string(threads));
            m_stop = false;
            for(uint32_t i = 0; i < threads; ++i)
            {
                print("add thread");
                m_threads.emplace_back(boost::thread(
                    boost::bind(&thread_pool::worker, this)));
                print("thread added");
            }
            print("started");
        }

        void stop()
        {
            print("stop");
            {
                boost::unique_lock<boost::mutex> lock(m_queue_mutex);
                m_stop = true;
            }
            print("notify_all");
            m_condition.notify_all();

            for(auto& thread : m_threads)
            {
                print("join");
                thread.join();
                print("joined");
            }
            print("all joined");
            print(std::to_string(m_threads.size()));
            m_threads.clear();
            print("all cleared");
        }

    private:

        void worker()
        {
            print("worker");
            while(true)
            {
                print("working");
                boost::unique_lock<boost::mutex> lock(m_queue_mutex);
                while(!m_stop && m_tasks.empty())
                {
                    print("while(!m_stop && m_tasks.empty())");
                    m_condition.wait(lock);
                    print("after lock");
                }
                print("after while");
                if(m_stop && m_tasks.empty())
                {
                    print("if(m_stop && m_tasks.empty())");
                    return;
                }
                print("getting task");
                std::function<void()> task(m_tasks.front());
                m_tasks.pop();
                lock.unlock();
                print("got task");
                task();
                print("task ran");
            }
        }

        void print(const std::string& text) const
        {
            std::cout << text << std::endl;
            boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
        }

    private:
        std::vector<boost::thread> m_threads;
        mutable std::queue<std::function<void()>> m_tasks;
        mutable boost::mutex m_queue_mutex;
        mutable boost::condition_variable m_condition;
        bool m_stop;
    };
}
