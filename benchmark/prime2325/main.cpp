// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cmath>

#include <fifi/prime2325_binary_search.h>
#include <fifi/prime2325_bitmap.h>

#include <boost/chrono.hpp>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/count.hpp>

namespace bc = boost::chrono;
namespace ba = boost::accumulators;

// RUN("%s, k=%d, block_size=%d", "hej", 10, 333)

// test_parameter 0 1 2 3 4 5
// unit [block_size]

// bench_id
//    |
//    --- setup
//    --- results (time)

// SETUP() << "k" << k;
// SETUP() << "

// RUN(){
// }

// class control
// {
// public:
//     control() : m_iterations(0)
//         {

//         }

//     bool iterations_complete()
//         {
//             return m_iterations > 10;
//         }

//     void next()
//     {
//         ++m_iterations;
//     }

//     uint32_t m_iterations;

// };

// #define RUN \
//     for (control ctrl; \
//          ctrl.iterations_complete() == false; ctrl.next())


// void hej()
// {
//     std::vector<int> p;



//     RUN{
//         int a = 3;
//         int b = 432534;
//         int c = a*b;
//     }
// }

struct result_store
{
    std::vector<std::string> m_tests;
    std::vector<double> m_mean;
    std::vector<double> m_dev;
    std::vector<uint32_t> m_max;
    std::vector<uint32_t> m_min;
    std::vector<uint32_t> m_count;

    template<class Value>
    void dump_value(Value v, std::ostream &os)
        {
            os << v;
        }

    void dump_value(std::string s, std::ostream &os)
        {
            os << "\"" << s << "\"";
        }


    template<class FirstIt, class LastIt>
    void dump_values(FirstIt first, LastIt last, std::ostream &os)
        {
            assert(first != last);
            os << "["; dump_value(*first, os);
            ++first;

            while(first != last)
            {
                os << ", "; dump_value(*first, os);
                ++first;
            }
            os << "]";
        }

    void dump_to_file()
        {
            assert(m_tests.size() == m_mean.size());
            assert(m_tests.size() == m_dev.size());
            assert(m_tests.size() == m_max.size());
            assert(m_tests.size() == m_min.size());
            assert(m_tests.size() == m_count.size());

            std::ofstream out("results.py", std::ios::trunc);

            out << "results = {";

            out << "\"tests\": "; dump_values(m_tests.begin(), m_tests.end(), out);
            out << ",";
            out << "\"mean\": "; dump_values(m_mean.begin(), m_mean.end(), out);
            out << ",";
            out << "\"dev\": "; dump_values(m_dev.begin(), m_dev.end(), out);
            out << ",";
            out << "\"max\": "; dump_values(m_max.begin(), m_max.end(), out);
            out << ",";
            out << "\"min\": "; dump_values(m_min.begin(), m_min.end(), out);
            out << ",";
            out << "\"count\": "; dump_values(m_count.begin(), m_count.end(), out);

            out << "}\n";
        }

};



/// The time required to run a search for the missing prefix
/// over a random block of data
template<class Algorithm>
bc::microseconds::rep benchmark(Algorithm &algorithm,
                                const std::vector<uint32_t> &data)
{
    auto t1 = bc::high_resolution_clock::now();

    uint32_t prefix = algorithm.find_prefix(sak::storage_list(data));

    auto t2 = bc::high_resolution_clock::now();

    (void)prefix; // Avoid unused warning

    return bc::duration_cast<bc::microseconds>(t2-t1).count();
}

typedef ba::accumulator_set
    <bc::microseconds::rep,
     ba::features
        <ba::tag::mean,
         ba::tag::variance,
         ba::tag::min,
         ba::tag::max,
         ba::tag::count> >
 accu_type;

/// Runs the benchmark for a specified
template<class Algorithm>
void run_benckmark(Algorithm &algorithm,
                   const std::vector<uint32_t> &data,
                   result_store &results,
                   double target_time = 5.0)
{

    const double ms_to_sec = 1000000.0;

    bc::microseconds::rep total = 0;
    uint32_t iterations = 0;

    accu_type acc;

    while((total / ms_to_sec) < target_time || iterations < 100)
    {
        auto time = benchmark(algorithm, data);

        acc(time);
        total += time;
        ++iterations;
    }

    std::stringstream ss;
    algorithm.print_info(ss);

    double mean = ba::extract_result<ba::tag::mean>( acc );
    double dev  = std::sqrt(ba::extract_result<ba::tag::variance>( acc ));
    uint32_t min = ba::extract_result<ba::tag::min>( acc );
    uint32_t max = ba::extract_result<ba::tag::max>( acc );
    uint32_t count = ba::extract_result<ba::tag::count>( acc );

    std::cout << ss.str() << std::endl;
    std::cout << "Mean:   \t" << mean << std::endl;
    std::cout << "Std dev:\t" << dev << std::endl;
    std::cout << "Min:    \t" << min << std::endl;
    std::cout << "Max:    \t" << max << std::endl;
    std::cout << "Count:  \t" << count << std::endl;

    results.m_tests.push_back(ss.str());
    results.m_mean.push_back(mean);
    results.m_dev.push_back(dev);
    results.m_max.push_back(max);
    results.m_min.push_back(min);
    results.m_count.push_back(count);

}

int main()
{
    srand(static_cast<uint32_t>(time(0)));

    double runtime = 0.5;

    result_store results;

    for(uint32_t b = 1000; b < 3750000; b += 100000)
    {

        std::vector<uint32_t> data(b);
        for(uint32_t i = 0; i < b; ++i)
        {
            data[i] = rand();
        }

        for(uint32_t i = 1; i < 4; ++i)

        {
            fifi::prime2325_binary_search binary_search(b, i);
            run_benckmark(binary_search, data, results, runtime);

        }

        fifi::prime2325_bitmap bitmap_search(b);
        run_benckmark(bitmap_search, data, results, runtime);
    }

    results.dump_to_file();

    return 0;
}

