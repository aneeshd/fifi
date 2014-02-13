// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing


#include <cassert>
#include <condition_variable>
#include <cstdint>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include <iostream>

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
            std::cout << "enqueue" << std::endl;
            assert(!m_stop);

            auto task = std::make_shared<std::packaged_task<void()>>(std::move(function));

            std::future<void> result = task->get_future();
            {
                std::unique_lock<std::mutex> lock(m_queue_mutex);
                m_tasks.push([task](){ (*task)(); });
            }
            m_condition.notify_one();
            return result;
        }

        ~thread_pool()
        {
            std::cout << "~thread_pool" << std::endl;
            stop();
        }

        void start(uint32_t threads)
        {
            std::cout << "start " << threads << std::endl;
            m_stop = false;
            for(uint32_t i = 0; i < threads; ++i)
            {
                std::cout << "add thread" << std::endl;
                m_threads.emplace_back(std::bind(&thread_pool::worker, std::move(this)));
            }
        }

        void stop()
        {
            std::cout << "stop" << std::endl;
            {
                std::unique_lock<std::mutex> lock(m_queue_mutex);
                m_stop = true;
            }
            std::cout << "notify_all" << std::endl;
            m_condition.notify_all();

            for(auto& thread : m_threads)
            {
                std::cout << "join" << std::endl;
                thread.join();
                std::cout << "joined" << std::endl;
            }
            m_threads.clear();
        }
    private:

        void worker()
        {
            while(true)
            {
                std::unique_lock<std::mutex> lock(m_queue_mutex);
                while(!m_stop && m_tasks.empty())
                {
                    std::cout << "while(!m_stop && m_tasks.empty())" << std::endl;
                    m_condition.wait(lock);
                }
                if(m_stop && m_tasks.empty())
                {
                    std::cout << "if(m_stop && m_tasks.empty())" << std::endl;
                    return;
                }
                std::function<void()> task(m_tasks.front());
                m_tasks.pop();
                lock.unlock();
                std::cout << "task" << std::endl;
                task();
            }
        }

        ERROR!

    private:
        std::vector<std::thread> m_threads;
        mutable std::queue<std::function<void()>> m_tasks;
        mutable std::mutex m_queue_mutex;
        mutable std::condition_variable m_condition;
        bool m_stop;
    };
}
