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

std::vector<uint32_t> setup_lengths()
{
    std::vector<uint32_t> lengths = {100, 1000, 2000 };
    return lengths;
}

std::vector<uint32_t> setup_vectors()
{
    std::vector<uint32_t> vectors = {100, 1000, 2000 };
    return vectors;
}

std::vector<std::string> setup_operations()
{
    std::vector<std::string> operations =
        {
            "linear dest[i] = dest[i] + src[i]",
            "linear dest[i] = dest[i] - src[i]",
            "linear dest[i] = dest[i] * src[i]",
            "linear dest[i] = dest[i] + (constant * src[i])",
            "linear dest[i] = dest[i] - (constant * src[i])",
            "linear dest[i] = dest[i] * constant",
            "random dest[i] = dest[i] + src[i]",
            "random dest[i] = dest[i] - src[i]",
            "random dest[i] = dest[i] * src[i]",
            "random dest[i] = dest[i] + (constant * src[i])",
            "random dest[i] = dest[i] - (constant * src[i])",
            "random dest[i] = dest[i] * constant"
        };

    return operations;
}


template<class FieldImpl>
class arithmetic_setup : public gauge::time_benchmark
{
public:

    typedef FieldImpl field_impl;
    typedef typename field_impl::field_type field_type;
    typedef typename field_type::value_type value_type;

public:

    arithmetic_setup()
        {
            std::vector<uint32_t> lengths = setup_lengths();
            std::vector<uint32_t> vectors = setup_vectors();
            std::vector<std::string> operations = setup_operations();

            for(uint32_t i = 0; i < lengths.size(); ++i)
            {
                for(uint32_t j = 0; j < vectors.size(); ++j)
                {
                    for(uint32_t k = 0; k < operations.size(); ++k)
                    {
                        gauge::config_set cs;
                        cs.set_value<uint32_t>("vector_length", lengths[i]);
                        cs.set_value<uint32_t>("vectors", vectors[j]);
                        cs.set_value<std::string>("operation", operations[k]);
                        cs.set_value<uint32_t>("element_size", sizeof(value_type));
                        add_configuration(cs);
                    }
                }
            }
        }

        void setup()
        {
            gauge::config_set cs = get_current_configuration();

            uint32_t length = cs.get_value<uint32_t>("vector_length");
            uint32_t vectors = cs.get_value<uint32_t>("vectors");

            m_symbols_one.resize(vectors);
            m_symbols_two.resize(vectors);

            for(uint32_t j = 0; j < vectors; ++j)
            {
                m_symbols_one[j].resize(length);
                m_symbols_two[j].resize(length);

                for(uint32_t i = 0; i < length; ++i)
                {
                    m_symbols_one[j][i] = rand();
                    m_symbols_two[j][i] = rand();
                }
            }
        }

    // Tests the dest[i] = dest[i] OP src[i] functions
    template<class Function>
    void run_linear_binary(Function f)
        {
            gauge::config_set cs = get_current_configuration();
            uint32_t length = cs.get_value<uint32_t>("vector_length");
            uint32_t vectors = cs.get_value<uint32_t>("vectors");

            RUN{
                for(uint32_t i = 0; i < vectors; ++i)
                {
                    f(m_field, &(m_symbols_one[i][0]),
                      &(m_symbols_two[i][0]), length);
                }
            }
        }

    // Tests the dest[i] = dest[i] OP (src[i] * constant) functions
    template<class Function>
    void run_linear_binary_constant(Function f)
        {
            gauge::config_set cs = get_current_configuration();
            uint32_t length = cs.get_value<uint32_t>("vector_length");
            uint32_t vectors = cs.get_value<uint32_t>("vectors");

            value_type constant = rand() % field_type::max_value;

            RUN{
                for(uint32_t i = 0; i < vectors; ++i)
                {
                    f(m_field, constant, &(m_symbols_one[i][0]),
                      &(m_symbols_two[i][0]), length);
                }
            }
        }

    // Tests the dest[i] = dest[i] * constant functions
    template<class Function>
    void run_linear_unary_constant(Function f)
        {
            gauge::config_set cs = get_current_configuration();
            uint32_t length = cs.get_value<uint32_t>("vector_length");
            uint32_t vectors = cs.get_value<uint32_t>("vectors");

            value_type constant = rand() % field_type::max_value;

            RUN{
                for(uint32_t i = 0; i < vectors; ++i)
                {
                    f(m_field, constant, &(m_symbols_one[i][0]), length);
                }
            }
        }

        // Tests the dest[i] = dest[i] OP src[i] functions
    template<class Function>
    void run_random_binary(Function f)
        {
            gauge::config_set cs = get_current_configuration();
            uint32_t length = cs.get_value<uint32_t>("vector_length");
            uint32_t vectors = cs.get_value<uint32_t>("vectors");

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

    // Tests the dest[i] = dest[i] OP (src[i] * constant) functions
    template<class Function>
    void run_random_binary_constant(Function f)
        {
            gauge::config_set cs = get_current_configuration();
            uint32_t length = cs.get_value<uint32_t>("vector_length");
            uint32_t vectors = cs.get_value<uint32_t>("vectors");

            value_type constant = rand() % field_type::max_value;

            RUN{
                for(uint32_t i = 0; i < vectors; ++i)
                {
                    uint32_t index_one = rand() % vectors;
                    uint32_t index_two = rand() % vectors;

                    f(m_field, constant, &(m_symbols_one[index_one][0]),
                      &(m_symbols_two[index_two][0]), length);
                }
            }
        }

    // Tests the dest[i] = dest[i] * constant functions
    template<class Function>
    void run_random_unary_constant(Function f)
        {
            gauge::config_set cs = get_current_configuration();
            uint32_t length = cs.get_value<uint32_t>("vector_length");
            uint32_t vectors = cs.get_value<uint32_t>("vectors");

            value_type constant = rand() % field_type::max_value;

            RUN{
                for(uint32_t i = 0; i < vectors; ++i)
                {
                    uint32_t index = rand() % vectors;

                    f(m_field, constant, &(m_symbols_one[index][0]), length);
                }
            }
        }


    void benchmark()
        {
            gauge::config_set cs = get_current_configuration();
            std::string operation = cs.get_value<std::string>("operation");

            if(operation == "linear dest[i] = dest[i] + src[i]")
            {
                run_linear_binary(&fifi::add<field_impl>);
            }
            else if(operation == "linear dest[i] = dest[i] - src[i]")
            {
                run_linear_binary(&fifi::subtract<field_impl>);
            }
            else if(operation == "linear dest[i] = dest[i] * src[i]")
            {
                run_linear_binary(&fifi::multiply<field_impl>);
            }
            else if(operation == "linear dest[i] = dest[i] + (constant * src[i])")
            {
                run_linear_binary_constant(&fifi::multiply_add<field_impl>);
            }
            else if(operation == "linear dest[i] = dest[i] - (constant * src[i])")
            {
                run_linear_binary_constant(&fifi::multiply_subtract<field_impl>);
            }
            else if(operation == "linear dest[i] = dest[i] * constant")
            {
                run_linear_unary_constant(&fifi::multiply_constant<field_impl>);
            }
            else if(operation == "random dest[i] = dest[i] + src[i]")
            {
                run_random_binary(&fifi::add<field_impl>);
            }
            else if(operation == "random dest[i] = dest[i] - src[i]")
            {
                run_random_binary(&fifi::subtract<field_impl>);
            }
            else if(operation == "random dest[i] = dest[i] * src[i]")
            {
                run_random_binary(&fifi::multiply<field_impl>);
            }
            else if(operation == "random dest[i] = dest[i] + (constant * src[i])")
            {
                run_random_binary_constant(&fifi::multiply_add<field_impl>);
            }
            else if(operation == "random dest[i] = dest[i] - (constant * src[i])")
            {
                run_random_binary_constant(&fifi::multiply_subtract<field_impl>);
            }
            else if(operation == "random dest[i] = dest[i] * constant")
            {
                run_random_unary_constant(&fifi::multiply_constant<field_impl>);
            }
            else
            {
                throw std::runtime_error("Unknown operation type");
            }
        }

protected:

    field_impl m_field;

    std::vector< std::vector<value_type> > m_symbols_one;
    std::vector< std::vector<value_type> > m_symbols_two;

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






// // Tests the dest[i] = dest[i] OP (src[i] * constant) funcions
// // Where OP can be +,-,*
// template<class Field>
// void invoke_dest_op_src_const(const std::string &name,
//                               long double target_time,
//                               uint32_t vectors, uint32_t vector_length,
//                               const typename run<Field>::dest_op_src_const &function)
// {
//     std::cout << "running " << name << std::endl;

//     typedef typename Field::value_type value_type;

//     std::vector< std::vector<value_type> > symbols;
//     symbols.resize(vectors);

//     for(uint32_t i = 0; i < symbols.size(); ++i)
//     {
//         symbols[i].resize(vector_length);
//         for(uint32_t j = 0; j < vector_length; ++j)
//         {
//             symbols[i][j] = rand() %
//                 std::numeric_limits<value_type>::max();
//         }
//     }

//     Field field;

//     // Warm up
//     sak::code_warmup warmup;

//     while(!warmup.done())
//     {
//         for(uint32_t i = 0; i < vectors; ++i)
//         {

//             uint32_t index_one = rand() % vectors;
//             uint32_t index_two = rand() % vectors;

//             value_type constant = rand() %
//                 std::numeric_limits<value_type>::max();

//             function(field, constant, &(symbols[index_one][0]),
//                      &(symbols[index_two][0]), vector_length);
//         }

//         warmup.next_iteration();
//     }

//     uint64_t needed_iterations = warmup.iterations(target_time);

//     boost::timer::cpu_timer timer;
//     timer.start();

//     for(uint64_t j = 0; j < needed_iterations; ++j)
//     {

//         for(uint32_t i = 0; i < vectors; ++i)
//         {

//             uint32_t index_one = rand() % vectors;
//             uint32_t index_two = rand() % vectors;

//             value_type constant = rand() %
//                 std::numeric_limits<value_type>::max();


//             function(field, constant, &(symbols[index_one][0]),
//                       &(symbols[index_two][0]), vector_length);

//         }

//     }

//     timer.stop();

//     long double total_sec = sak::seconds_elapsed(timer);

//     // Amount of data processed
//     long double bytes = static_cast<long double>(
//         needed_iterations * vectors * vector_length * sizeof(value_type));

//     long double megs = bytes / 1000000.0;
//     long double megs_per_second = megs / total_sec;

//     std::cout << "Test time " << total_sec << " [s]" << std::endl;
//     std::cout << "MB/s = " << megs_per_second << std::endl;

// }


// // Tests the dest[i] = dest[i] * constant functions
// // Where OP can be +,-,*
// template<class Field>
// void invoke_dest_const(const std::string &name,
//                        long double target_time,
//                        uint32_t vectors, uint32_t vector_length,
//                        const typename run<Field>::dest_const &function)
// {
//     std::cout << "running " << name << std::endl;

//     typedef typename Field::value_type value_type;

//     std::vector< std::vector<value_type> > symbols;
//     symbols.resize(vectors);

//     for(uint32_t i = 0; i < symbols.size(); ++i)
//     {
//         symbols[i].resize(vector_length);
//         for(uint32_t j = 0; j < vector_length; ++j)
//         {
//             symbols[i][j] = rand() %
//                 std::numeric_limits<value_type>::max();
//         }
//     }

//     Field field;

//     // Warm up
//     sak::code_warmup warmup;

//     while(!warmup.done())
//     {
//         for(uint32_t i = 0; i < vectors; ++i)
//         {

//             uint32_t index = rand() % vectors;

//             value_type constant = rand() %
//                 std::numeric_limits<value_type>::max();

//             function(field, constant, &(symbols[index][0]),
//                      vector_length);
//         }

//         warmup.next_iteration();
//     }

//     uint64_t needed_iterations = warmup.iterations(target_time);

//     boost::timer::cpu_timer timer;
//     timer.start();

//     for(uint64_t j = 0; j < needed_iterations; ++j)
//     {

//         for(uint32_t i = 0; i < vectors; ++i)
//         {

//             uint32_t index = rand() % vectors;

//             value_type constant = rand() %
//                 std::numeric_limits<value_type>::max();

//             function(field, constant, &(symbols[index][0]),
//                      vector_length);

//         }

//     }

//     timer.stop();

//     long double total_sec = sak::seconds_elapsed(timer);


//     // Amount of data processed
//     long double bytes = static_cast<long double>(
//         needed_iterations * vectors * vector_length * sizeof(value_type));

//     long double megs = bytes / 1000000.0;
//     long double megs_per_second = megs / total_sec;

//     std::cout << "Test time " << total_sec << " [s]" << std::endl;
//     std::cout << "MB/s = " << megs_per_second << std::endl;

// }


// // Helper function used to invoke the different arithmetic
// // operations for each field implementation.
// template<class Field>
// void benchmark(const std::string &name)
// {
//     uint32_t vectors = 100;
//     uint32_t vector_length = 1400;

//     long double time = 5.0;

//     typedef Field field_type;

//     {
//         typename run<field_type>::dest_op_src function;

//         function = &fifi::add<field_type>;

//         invoke_dest_op_src<field_type>(
//             name + " add", time, vectors, vector_length, function);

//         function = &fifi::subtract<field_type>;

//         invoke_dest_op_src<field_type>(
//             name + " subtract", time, vectors, vector_length, function);

//         function = &fifi::multiply<field_type>;

//         invoke_dest_op_src<field_type>(
//             name + " multiply", time, vectors, vector_length, function);
//     }

//     {

//         typename run<field_type>::dest_op_src_const function;

//         function = &fifi::multiply_add<field_type>;

//         invoke_dest_op_src_const<field_type>(
//             name + " multiply_add", time, vectors, vector_length, function);

//         function = &fifi::multiply_subtract<field_type>;

//         invoke_dest_op_src_const<field_type>(
//             name + " multiply_subtract", time, vectors, vector_length, function);
//     }

//     {

//         typename run<field_type>::dest_const function;

//         function = &fifi::multiply_constant<field_type>;

//         invoke_dest_const<field_type>(
//             name + " multiply_constant", time, vectors, vector_length, function);

//     }

// }

int main(int argc, const char* argv[])
{

    srand(static_cast<uint32_t>(time(0)));
    gauge::runner::instance().printers().push_back(
        std::make_shared<gauge::console_printer>());

    gauge::runner::instance().printers().push_back(
        std::make_shared<gauge::python_printer>("out.py"));

    gauge::runner::run_benchmarks(argc, argv);

    // benchmark< fifi::simple_online<fifi::binary8> >(
    //     "Simple Online Binary8");

    // benchmark< fifi::simple_online<fifi::binary16> >(
    //     "Simple Online Binary16");

    // benchmark< fifi::full_table<fifi::binary8> >(
    //     "Full Table Binary8");

    // benchmark<fifi::log_table<fifi::binary8> >(
    //     "Log Table Binary8");

    // benchmark<fifi::log_table<fifi::binary16> >(
    //     "Log Table Binary16");

    // benchmark<fifi::extended_log_table<fifi::binary8> >(
    //     "Extended Log Table Binary8");

    // benchmark<fifi::extended_log_table<fifi::binary16> >(
    //     "Extended Log Table Binary16");

    // benchmark<fifi::optimal_prime<fifi::prime2325> >(
    //     "Optimal Prime Prime2325");

    return 0;
}

