// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cmath>
#include <limits>

#include <sak/aligned_allocator.hpp>

#include <gauge/gauge.hpp>
#include <gauge/console_printer.hpp>
#include <gauge/csv_printer.hpp>
#include <gauge/python_printer.hpp>

#include <fifi/fifi_utils.hpp>
#include <fifi/simple_online.hpp>
#include <fifi/full_table.hpp>
#include <fifi/log_table.hpp>
#include <fifi/extended_log_table.hpp>
#include <fifi/optimal_prime.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>
#include <fifi/prime2325.hpp>

#include "stacks.hpp"

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

    double measurement()
    {
        // Get the time spent per iteration
        double time = gauge::time_benchmark::measurement();

        gauge::config_set cs = get_current_configuration();

        uint32_t size = cs.get_value<uint32_t>("vector_size");
        uint32_t vectors = cs.get_value<uint32_t>("vectors");

        // The number of bytes processed per iteration
        uint64_t bytes = size * vectors;

        return bytes / time; // MB/s for each iteration
    }

    void store_run(tables::table& results)
    {
        if(!results.has_column("throughput"))
            results.add_column("throughput");

        results.set_value("throughput", measurement());
    }

    std::string unit_text() const
    {
        return "MB/s";
    }

    void get_options(gauge::po::variables_map& options)
    {
        auto sizes = options["size"].as<std::vector<uint32_t>>();
        auto vectors = options["vectors"].as<std::vector<uint32_t>>();
        auto operations = options["operations"].as<std::vector<std::string>>();
        auto access = options["access"].as<std::vector<std::string>>();

        assert(sizes.size() > 0);
        assert(vectors.size() > 0);
        assert(operations.size() > 0);
        assert(access.size() > 0);

        for (const auto& s : sizes)
        {
            for (const auto& v : vectors)
            {
                for (const auto& o : operations)
                {
                    for (const auto& a : access)
                    {
                        // The encoding benchmark pattern is not applicable
                        // to multiply_constant
                        if (o == "multiply_constant" && a == "encoding")
                            continue;

                        gauge::config_set cs;
                        cs.set_value<uint32_t>("vector_size", s);

                        // Based on the desired vector size (in bytes)
                        // we calculate the length of the vector in
                        // field elements
                        assert((s % sizeof(value_type)) == 0);
                        uint32_t length = s / sizeof(value_type);
                        assert(length > 0);

                        cs.set_value<uint32_t>("vector_length", length);
                        cs.set_value<uint32_t>("vectors", v);
                        cs.set_value<std::string>("operation", o);
                        cs.set_value<std::string>("data_access", a);

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

        // Prepare the continuous data blocks
        m_data_one.resize(vectors * length);
        m_data_two.resize(vectors * length);

        for (uint32_t i = 0; i < length; ++i)
        {
            m_data_one[i] = rand() % field_type::max_value;
            m_data_two[i] = rand() % field_type::max_value;
        }

        // Prepare the symbol pointers
        m_symbols_one.resize(vectors);
        m_symbols_two.resize(vectors);

        for (uint32_t i = 0; i < vectors; ++i)
        {
            m_symbols_one[i] = &m_data_one[i * length];
            m_symbols_two[i] = &m_data_two[i * length];
        }
    }

    /// Tests the dest[i] = dest[i] OP src[i] functions
    template<class Function>
    void run_binary(Function function)
    {
        gauge::config_set cs = get_current_configuration();
        uint32_t length = cs.get_value<uint32_t>("vector_length");
        uint32_t vectors = cs.get_value<uint32_t>("vectors");
        std::string data_access = cs.get_value<std::string>("data_access");

        if(data_access == "linear")
        {
            RUN
            {
                for (uint32_t i = 0; i < vectors; ++i)
                {
                    (m_field.*function)(m_symbols_one[i], m_symbols_two[i],
                        length);
                }
            }
        }
        else if (data_access == "random")
        {
            RUN
            {
                for (uint32_t i = 0; i < vectors; ++i)
                {
                    uint32_t index_one = rand() % vectors;
                    uint32_t index_two = rand() % vectors;

                    (m_field.*function)(m_symbols_one[index_one],
                        m_symbols_two[index_two], length);
                }
            }
        }
        else if (data_access == "encoding")
        {
            RUN
            {
                for (uint32_t i = 0; i < vectors; ++i)
                {
                    for (uint32_t j = 0; j < vectors; ++j)
                    {
                        (m_field.*function)(m_symbols_one[i],
                            m_symbols_two[j], length);
                    }
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
    void run_binary_constant(Function function)
    {
        gauge::config_set cs = get_current_configuration();
        uint32_t length = cs.get_value<uint32_t>("vector_length");
        uint32_t vectors = cs.get_value<uint32_t>("vectors");
        std::string data_access = cs.get_value<std::string>("data_access");

        if(data_access == "linear")
        {
            // Clock is ticking
            RUN
            {
                value_type constant = rand() % field_type::max_value;
                constant = fifi::pack_constant<field_type>(constant);

                for (uint32_t i = 0; i < vectors; ++i)
                {
                    (m_field.*function)(m_symbols_one[i],
                        m_symbols_two[i], constant, length);
                }
            }
        }
        else if (data_access == "random")
        {
            // Clock is ticking
            RUN
            {
                value_type constant = rand() % field_type::max_value;
                constant = fifi::pack_constant<field_type>(constant);

                for (uint32_t i = 0; i < vectors; ++i)
                {
                    uint32_t index_one = rand() % vectors;
                    uint32_t index_two = rand() % vectors;

                    (m_field.*function)(m_symbols_one[index_one],
                        m_symbols_two[index_two], constant, length);
                }
            }
        }
        else if (data_access == "encoding")
        {
            RUN
            {
                for (uint32_t i = 0; i < vectors; ++i)
                {
                    for (uint32_t j = 0; j < vectors; ++j)
                    {
                        value_type constant = rand() % field_type::max_value;
                        constant = fifi::pack_constant<field_type>(constant);

                        (m_field.*function)(m_symbols_one[i],
                            m_symbols_two[j], constant, length);
                    }
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
    void run_unary_constant(Function function)
    {
        gauge::config_set cs = get_current_configuration();
        uint32_t length = cs.get_value<uint32_t>("vector_length");
        uint32_t vectors = cs.get_value<uint32_t>("vectors");
        std::string data_access = cs.get_value<std::string>("data_access");

        if(data_access == "linear")
        {
            RUN
            {
                value_type constant = rand() % field_type::max_value;
                constant = fifi::pack_constant<field_type>(constant);

                for (uint32_t i = 0; i < vectors; ++i)
                {
                    (m_field.*function)(m_symbols_one[i], constant,
                        length);
                }
            }
        }
        else if (data_access == "random")
        {
            RUN
            {
                value_type constant = rand() % field_type::max_value;
                constant = fifi::pack_constant<field_type>(constant);

                for (uint32_t i = 0; i < vectors; ++i)
                {
                    uint32_t index = rand() % vectors;

                    (m_field.*function)(m_symbols_one[index], constant,
                        length);
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

        if (operation == "add")
        {
            // dest[i] = dest[i] + src[i]
            run_binary(&field_impl::region_add);
        }
        else if (operation == "subtract")
        {
            // dest[i] = dest[i] - src[i]
            run_binary(&field_impl::region_subtract);
        }
        else if (operation == "multiply")
        {
            // dest[i] = dest[i] * src[i]
            run_binary(&field_impl::region_multiply);
        }
        else if (operation == "multiply_add")
        {
            // dest[i] = dest[i] + (constant * src[i])
            run_binary_constant(&field_impl::region_multiply_add);
        }
        else if (operation == "multiply_subtract")
        {
            // dest[i] = dest[i] - (constant * src[i])
            run_binary_constant(&field_impl::region_multiply_subtract);
        }
        else if (operation == "multiply_constant")
        {
            // dest[i] = dest[i] * constant
            run_unary_constant(&field_impl::region_multiply_constant);
        }
        else
        {
            throw std::runtime_error("Unknown operation type");
        }
    }

protected:

    /// The field implementation
    field_impl m_field;

    /// Type of the aligned vector
    typedef std::vector<value_type, sak::aligned_allocator<value_type>>
        aligned_vector;

    /// The first buffer of vectors
    std::vector<value_type*> m_symbols_one;

    /// The second buffer of vectors
    std::vector<value_type*> m_symbols_two;

    /// Random data for the first continuous buffer
    aligned_vector m_data_one;

    /// Random data for the second continuous buffer
    aligned_vector m_data_two;
};


/// Using this macro we may specify options. For specifying options
/// we use the boost program options library. So you may additional
/// details on how to do it in the manual for that library.
BENCHMARK_OPTION(arithmetic_options)
{
    gauge::po::options_description options;

    std::vector<uint32_t> size;
    size.push_back(64);
    size.push_back(1600);

    auto default_size =
        gauge::po::value<std::vector<uint32_t>>()->default_value(
            size, "")->multitoken();

    std::vector<uint32_t> vectors;
    vectors.push_back(16);
    vectors.push_back(64);
    vectors.push_back(256);

    auto default_vectors =
        gauge::po::value<std::vector<uint32_t>>()->default_value(
            vectors, "")->multitoken();

    std::vector<std::string> operations;
    operations.push_back("add");
    operations.push_back("subtract");
    operations.push_back("multiply");
    operations.push_back("multiply_add");
    operations.push_back("multiply_subtract");
    operations.push_back("multiply_constant");

    auto default_operations =
        gauge::po::value<std::vector<std::string> >()->default_value(
            operations, "")->multitoken();

    std::vector<std::string> access;
    access.push_back("random");
    access.push_back("linear");
    access.push_back("encoding");

    auto default_access =
        gauge::po::value<std::vector<std::string> >()->default_value(
            access, "")->multitoken();

    options.add_options()
        ("size", default_size, "Set the size of a vector in bytes");

    options.add_options()
        ("vectors", default_vectors,
         "Set the number of vectors to perform the operations on");

    options.add_options()
        ("operations", default_operations, "Set operations type");

    options.add_options()
        ("access", default_access, "Set the data access pattern");

    gauge::runner::instance().register_options(options);
}

//------------------------------------------------------------------
// SimpleOnline
//------------------------------------------------------------------

// typedef arithmetic_setup< fifi::simple_online<fifi::binary> >
//     setup_simple_online_binary;

// BENCHMARK_F(setup_simple_online_binary, Arithmetic, SimpleOnline, 5)
// {
//     benchmark();
// }

typedef arithmetic_setup<fifi::simple_online<fifi::binary8>>
    setup_simple_online_binary8;

BENCHMARK_F(setup_simple_online_binary8, Arithmetic, simple_online_binary8, 5)
{
    benchmark();
}

typedef arithmetic_setup<fifi::simple_online<fifi::binary16>>
    setup_simple_online_binary16;

BENCHMARK_F(setup_simple_online_binary16, arithmetic, simple_online_binary16, 5)
{
    benchmark();
}

//------------------------------------------------------------------
// FullTable
//------------------------------------------------------------------

typedef arithmetic_setup<fifi::full_table<fifi::binary4>>
    setup_full_table_binary4;

BENCHMARK_F(setup_full_table_binary4, arithmetic, full_table_binary4, 5)
{
    benchmark();
}

typedef arithmetic_setup<fifi::full_table<fifi::binary8>>
    setup_full_table_binary8;

BENCHMARK_F(setup_full_table_binary8, arithmetic, full_table_binary8, 5)
{
    benchmark();
}

//------------------------------------------------------------------
// LogTable
//------------------------------------------------------------------

typedef arithmetic_setup< fifi::log_table<fifi::binary8>>
    setup_log_table_binary8;

BENCHMARK_F(setup_log_table_binary8, arithmetic, log_table_binary8, 5)
{
    benchmark();
}

typedef arithmetic_setup< fifi::log_table<fifi::binary16>>
    setup_log_table_binary16;

BENCHMARK_F(setup_log_table_binary16, arithmetic, log_table_binary16, 5)
{
    benchmark();
}

//------------------------------------------------------------------
// ExtendedLogTable
//------------------------------------------------------------------

typedef arithmetic_setup< fifi::extended_log_table<fifi::binary8>>
    setup_extended_log_table_binary8;

BENCHMARK_F(setup_extended_log_table_binary8, arithmetic,
            extended_log_table_binary8, 5)
{
    benchmark();
}

typedef arithmetic_setup< fifi::extended_log_table<fifi::binary16>>
    setup_extended_log_table_binary16;

BENCHMARK_F(setup_extended_log_table_binary16, arithmetic,
            extended_log_table_binary16, 5)
{
    benchmark();
}

//------------------------------------------------------------------
// OptimalPrime
//------------------------------------------------------------------

typedef arithmetic_setup< fifi::optimal_prime<fifi::prime2325>>
    setup_optimal_prime2325;

BENCHMARK_F(setup_optimal_prime2325, arithmetic, optimal_prime2325, 5)
{
    benchmark();
}

//------------------------------------------------------------------
// Unoptimized
//------------------------------------------------------------------

typedef arithmetic_setup<fifi::unoptimized_binary8<fifi::binary8>>
    setup_unoptimized_binary8;

BENCHMARK_F(setup_unoptimized_binary8, arithmetic, unoptimized_binary8, 5)
{
    benchmark();
}

int main(int argc, const char* argv[])
{
    srand(static_cast<uint32_t>(time(0)));

    gauge::runner::add_default_printers();

    gauge::runner::run_benchmarks(argc, argv);

    return 0;
}
