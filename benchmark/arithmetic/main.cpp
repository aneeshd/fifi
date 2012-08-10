// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cmath>
#include <stdexcept>

#include <fifi/arithmetics.h>
#include <fifi/fifi_utils.h>

#include <fifi/simple_online.h>
#include <fifi/full_table.h>
#include <fifi/log_table.h>
#include <fifi/extended_log_table.h>
#include <fifi/optimal_prime.h>
#include <fifi/field_types.h>

#include <gauge/gauge.h>
#include <gauge/console_printer.h>
#include <gauge/python_printer.h>

/// @return the size of a vector in bytes
std::vector<uint32_t> setup_sizes()
{
    std::vector<uint32_t> sizes;
    sizes.push_back(100);
    sizes.push_back(1400);
    sizes.push_back(2000);
    return sizes;
}

/// The working set - i.e. how many vectors are in the source
/// and destination buffers respectively.
///
/// @return the number of vectors in each buffer
std::vector<uint32_t> setup_vectors()
{
    std::vector<uint32_t> vectors;
    vectors.push_back(16);
    vectors.push_back(32);
    vectors.push_back(64);
    vectors.push_back(128);
    vectors.push_back(256);
    vectors.push_back(512);
    vectors.push_back(1024);

    return vectors;
}

/// The different operations to perform on the two buffers
/// @return the operations to perform
std::vector<std::string> setup_operations()
{
    std::vector<std::string> operations;
    operations.push_back("dest[i] = dest[i] + src[i]");
    operations.push_back("dest[i] = dest[i] - src[i]");
    operations.push_back("dest[i] = dest[i] * src[i]");
    operations.push_back("dest[i] = dest[i] + (constant * src[i])");
    operations.push_back("dest[i] = dest[i] - (constant * src[i])");
    operations.push_back("dest[i] = dest[i] * constant");

    return operations;
}

/// Whether vectors are take from each buffer in a linear or
/// random pattern
/// @return the access pattern
std::vector<std::string> setup_data_access()
{
    std::vector<std::string> data_access;
    data_access.push_back("random");
    data_access.push_back("linear");

    return data_access;
}

/// Benchmark fixture for the arithmetic benchmark
template<class FieldImpl>
class arithmetic_setup : public gauge::time_benchmark
{
public:

    /// The field implementation used
    typedef FieldImpl field_impl;

    /// The field type e.g. binary, binary8 etc
    typedef typename field_impl::field_type field_type;

    /// The value type of a field element
    typedef typename field_type::value_type value_type;

public:

    /// Constructor - creates all the benchmark configurations
    arithmetic_setup()
        {
            std::vector<uint32_t> sizes = setup_sizes();
            std::vector<uint32_t> vectors = setup_vectors();

            // We make one pool with random data as source for the
            // computations
            uint32_t max_size =
                *std::max_element(sizes.begin(), sizes.end());

            assert((max_size % sizeof(value_type)) == 0);
            uint32_t max_length = max_size / sizeof(value_type);

            uint32_t max_vectors =
                *std::max_element(vectors.begin(), vectors.end());

            m_random_symbols_one.resize(max_vectors);
            m_random_symbols_two.resize(max_vectors);

            m_temp.resize(max_length);

            for(uint32_t j = 0; j < max_vectors; ++j)
            {
                m_random_symbols_one[j].resize(max_length);
                m_random_symbols_two[j].resize(max_length);

                for(uint32_t i = 0; i < max_length; ++i)
                {
                    m_random_symbols_one[j][i] = rand();
                    m_random_symbols_two[j][i] = rand();
                }
            }

            // Now add all the configurations
            std::vector<std::string> operations = setup_operations();
            std::vector<std::string> data_access = setup_data_access();

            for(uint32_t i = 0; i < sizes.size(); ++i)
            {
                for(uint32_t j = 0; j < vectors.size(); ++j)
                {
                    for(uint32_t k = 0; k < operations.size(); ++k)
                    {
                        for(uint32_t m = 0; m < data_access.size(); ++m)
                        {
                            gauge::config_set cs;
                            cs.set_value<uint32_t>("vector_size", sizes[i]);

                            // Based on the desired vector size (in bytes)
                            // we calculate the length of the vector in
                            // field elements
                            assert((sizes[i] % sizeof(value_type)) == 0);
                            uint32_t length = sizes[i] / sizeof(value_type);

                            cs.set_value<uint32_t>("vector_length", length);
                            cs.set_value<uint32_t>("vectors", vectors[j]);
                            cs.set_value<std::string>("operation", operations[k]);
                            cs.set_value<std::string>("data_access", data_access[m]);
                            add_configuration(cs);
                        }
                    }
                }
            }
        }

    /// Prepares the data structures between each run
    void setup()
        {
            gauge::config_set cs = get_current_configuration();

            uint32_t length = cs.get_value<uint32_t>("vector_length");
            uint32_t vectors = cs.get_value<uint32_t>("vectors");

            if(vectors != m_symbols_one.size())
            {
                m_symbols_one.resize(vectors);
                m_symbols_two.resize(vectors);
            }

            for(uint32_t j = 0; j < vectors; ++j)
            {
                if(length != m_symbols_one[j].size())
                {
                    m_symbols_one[j].resize(length);
                    m_symbols_two[j].resize(length);
                }

                std::copy_n(&m_random_symbols_one[j][0],
                            length,
                            &m_symbols_one[j][0]);

                std::copy_n(&m_random_symbols_two[j][0],
                            length,
                            &m_symbols_two[j][0]);
            }

        }

    /// Tests the dest[i] = dest[i] OP src[i] functions
    template<class Function>
    void run_binary(Function f)
        {
            gauge::config_set cs = get_current_configuration();
            uint32_t length = cs.get_value<uint32_t>("vector_length");
            uint32_t vectors = cs.get_value<uint32_t>("vectors");
            std::string data_access = cs.get_value<std::string>("data_access");

            if(data_access == "linear")
            {
                RUN{

                    for(uint32_t i = 0; i < vectors; ++i)
                    {
                        f(m_field, &(m_symbols_one[i][0]),
                          &(m_symbols_two[i][0]), length);
                    }

                }
            }
            else if(data_access == "random")
            {
                RUN{

                    for(uint32_t i = 0; i < vectors; ++i)
                    {
                        uint32_t index_one = rand() % vectors;
                        uint32_t index_two = rand() % vectors;

                        f(m_field, &(m_symbols_one[index_one][0]),
                          &(m_symbols_two[index_two][0]), length);
                    }

                }
            }
            else
            {
                assert(0);
            }
        }

    /// Tests the dest[i] = dest[i] OP (src[i] * constant) functions
    template<class Function>
    void run_binary_constant(Function f)
        {
            gauge::config_set cs = get_current_configuration();
            uint32_t length = cs.get_value<uint32_t>("vector_length");
            uint32_t vectors = cs.get_value<uint32_t>("vectors");
            std::string data_access = cs.get_value<std::string>("data_access");

            if(data_access == "linear")
            {
                // Clock is ticking
                RUN{

                    value_type constant = rand() % field_type::max_value;

                    for(uint32_t i = 0; i < vectors; ++i)
                    {
                        f(m_field, constant, &(m_symbols_one[i][0]),
                          &(m_symbols_two[i][0]), &m_temp[0], length);
                    }
                }

            }
            else if(data_access == "random")
            {
                // Clock is ticking
                RUN{

                    value_type constant = rand() % field_type::max_value;

                    for(uint32_t i = 0; i < vectors; ++i)
                    {
                        uint32_t index_one = rand() % vectors;
                        uint32_t index_two = rand() % vectors;

                        f(m_field, constant, &(m_symbols_one[index_one][0]),
                          &(m_symbols_two[index_two][0]), &m_temp[0], length);
                    }
                }

            }
            else
            {
                assert(0);
            }
        }

    /// Tests the dest[i] = dest[i] * constant functions
    template<class Function>
    void run_unary_constant(Function f)
        {
            gauge::config_set cs = get_current_configuration();
            uint32_t length = cs.get_value<uint32_t>("vector_length");
            uint32_t vectors = cs.get_value<uint32_t>("vectors");
            std::string data_access = cs.get_value<std::string>("data_access");

            if(data_access == "linear")
            {

                RUN{

                    value_type constant = rand() % field_type::max_value;

                    for(uint32_t i = 0; i < vectors; ++i)
                    {
                        f(m_field, constant, &(m_symbols_one[i][0]), length);
                    }
                }
            }
            else if(data_access == "random")
            {
                RUN{

                    value_type constant = rand() % field_type::max_value;

                    for(uint32_t i = 0; i < vectors; ++i)
                    {
                        uint32_t index = rand() % vectors;

                        f(m_field, constant, &(m_symbols_one[index][0]), length);
                    }
                }

            }
            else
            {
                assert(0);
            }
        }

    /// Starts a new benchmark according to the current configuration
    void benchmark()
        {
            gauge::config_set cs = get_current_configuration();
            std::string operation = cs.get_value<std::string>("operation");

            if(operation == "dest[i] = dest[i] + src[i]")
            {
                run_binary(&fifi::add<field_impl>);
            }
            else if(operation == "dest[i] = dest[i] - src[i]")
            {
                run_binary(&fifi::subtract<field_impl>);
            }
            else if(operation == "dest[i] = dest[i] * src[i]")
            {
                run_binary(&fifi::multiply<field_impl>);
            }
            else if(operation == "dest[i] = dest[i] + (constant * src[i])")
            {
                run_binary_constant(&fifi::multiply_add<field_impl>);
            }
            else if(operation == "dest[i] = dest[i] - (constant * src[i])")
            {
                run_binary_constant(&fifi::multiply_subtract<field_impl>);
            }
            else if(operation == "dest[i] = dest[i] * constant")
            {
                run_unary_constant(&fifi::multiply_constant<field_impl>);
            }
            else
            {
                throw std::runtime_error("Unknown operation type");
            }
        }

protected:

    /// The field implementation
    field_impl m_field;

    /// The first buffer of vectors
    std::vector< std::vector<value_type> > m_symbols_one;

    /// The second buffer of vectors
    std::vector< std::vector<value_type> > m_symbols_two;

    /// Random data for the first buffer of symbols
    std::vector< std::vector<value_type> > m_random_symbols_one;

    /// Random data for the second buffer of symbols
    std::vector< std::vector<value_type> > m_random_symbols_two;

    /// Temp buffer required for composite algorithms
    std::vector<value_type> m_temp;

};

// typedef arithmetic_setup< fifi::simple_online<fifi::binary> >
//     setup_simple_online_binary;

// BENCHMARK_F(setup_simple_online_binary, Arithmetic, SimpleOnline, 5)
// {
//     benchmark();
// }

typedef arithmetic_setup< fifi::simple_online<fifi::binary8> >
    setup_simple_online_binary8;

BENCHMARK_F(setup_simple_online_binary8, Arithmetic, SimpleOnline8, 5)
{
    benchmark();
}

typedef arithmetic_setup< fifi::simple_online<fifi::binary16> >
    setup_simple_online_binary16;

BENCHMARK_F(setup_simple_online_binary16, Arithmetic, SimpleOnline16, 5)
{
    benchmark();
}

typedef arithmetic_setup< fifi::full_table<fifi::binary8> >
    setup_full_table_binary8;

BENCHMARK_F(setup_full_table_binary8, Arithmetic, FullTable8, 5)
{
    benchmark();
}

typedef arithmetic_setup< fifi::log_table<fifi::binary8> >
    setup_log_table_binary8;

BENCHMARK_F(setup_log_table_binary8, Arithmetic, LogTable8, 5)
{
    benchmark();
}

typedef arithmetic_setup< fifi::log_table<fifi::binary16> >
    setup_log_table_binary16;

BENCHMARK_F(setup_log_table_binary16, Arithmetic, LogTable16, 5)
{
    benchmark();
}

typedef arithmetic_setup< fifi::extended_log_table<fifi::binary8> >
    setup_extended_log_table_binary8;

BENCHMARK_F(setup_extended_log_table_binary8, Arithmetic, ExtendedLogTable8, 5)
{
    benchmark();
}


typedef arithmetic_setup< fifi::extended_log_table<fifi::binary16> >
    setup_extended_log_table_binary16;

BENCHMARK_F(setup_extended_log_table_binary16, Arithmetic, ExtendedLogTable16, 5)
{
    benchmark();
}


typedef arithmetic_setup< fifi::optimal_prime<fifi::prime2325> >
    setup_optimal_prime2325;

BENCHMARK_F(setup_optimal_prime2325, Arithmetic, OptimalPrime2325, 5)
{
    benchmark();
}


int main(int argc, const char* argv[])
{

    srand(static_cast<uint32_t>(time(0)));
    gauge::runner::instance().printers().push_back(
        std::make_shared<gauge::console_printer>());

    gauge::runner::instance().printers().push_back(
        std::make_shared<gauge::python_printer>("out.py"));

    gauge::runner::run_benchmarks(argc, argv);

    return 0;
}

