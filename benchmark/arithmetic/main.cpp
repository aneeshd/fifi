// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cmath>

#include <fifi/arithmetics.h>
#include <fifi/fifi_utils.h>

#include <fifi/simple_online.h>
#include <fifi/full_table.h>
#include <fifi/log_table.h>
#include <fifi/extended_log_table.h>
#include <fifi/optimal_prime.h>
#include <fifi/field_types.h>


#include <sak/code_warmup.h>


// Helper struct defning pointer to function
// types.
template<class Field>
struct run
{
    typedef typename Field::value_type value_type;
    typedef void (*dest_op_src)(const Field &,
                                value_type*,
                                const value_type*,
                                uint32_t length);


    typedef void (*dest_op_src_const)(const Field &,
                                      value_type,
                                      value_type*,
                                      const value_type*,
                                      uint32_t length);

    typedef void (*dest_const)(const Field &,
                               value_type,
                               value_type*,
                               uint32_t length);
};


// Tests the dest[i] = dest[i] OP src[i] funcions
// Where OP can be +,-,*
template<class Field>
void invoke_dest_op_src(const std::string &name,
                        long double target_time,
                        uint32_t vectors, uint32_t vector_length,
                        const typename run<Field>::dest_op_src &function)
{
    std::cout << "running " << name << std::endl;

    typedef typename Field::value_type value_type;

    std::vector< std::vector<value_type> > symbols_one;
    symbols_one.resize(vectors);

    std::vector< std::vector<value_type> > symbols_two;
    symbols_two.resize(vectors);


    for(uint32_t i = 0; i < symbols_one.size(); ++i)
    {
        symbols_one[i].resize(vector_length);
        symbols_two[i].resize(vector_length);

        for(uint32_t j = 0; j < vector_length; ++j)
        {
            symbols_one[i][j] = rand() %
                std::numeric_limits<value_type>::max();
            symbols_two[i][j] = rand() %
                std::numeric_limits<value_type>::max();

        }
    }

    Field field;

    // Warm up
    sak::code_warmup warmup;

    while(!warmup.done())
    {
        for(uint32_t i = 0; i < vectors; ++i)
        {

            uint32_t index_one = rand() % vectors;
            uint32_t index_two = rand() % vectors;

            function(field, &(symbols_one[index_one][0]),
                     &(symbols_two[index_two][0]), vector_length);
        }

        warmup.next_iteration();
    }

    uint64_t needed_iterations = warmup.iterations(target_time);

    std::cout << "Needed iteration: " << needed_iterations << std::endl;

    boost::timer::cpu_timer timer;
    timer.start();

    for(uint64_t j = 0; j < needed_iterations; ++j)
    {

        for(uint32_t i = 0; i < vectors; ++i)
        {

            uint32_t index_one = rand() % vectors;
            uint32_t index_two = rand() % vectors;

            function(field, &(symbols_one[index_one][0]),
                      &(symbols_two[index_two][0]), vector_length);

        }

    }

    timer.stop();

    long double total_sec = sak::seconds_elapsed(timer);


    // Amount of data processed
    long double bytes = static_cast<long double>(
        needed_iterations * vectors * vector_length * sizeof(value_type));

    long double megs = bytes / 1000000.0;
    long double megs_per_second = megs / total_sec;

    std::cout << "Test time " << total_sec << " [s]" << std::endl;
    std::cout << "MB/s = " << megs_per_second << std::endl;

}


// Tests the dest[i] = dest[i] OP (src[i] * constant) funcions
// Where OP can be +,-,*
template<class Field>
void invoke_dest_op_src_const(const std::string &name,
                              long double target_time,
                              uint32_t vectors, uint32_t vector_length,
                              const typename run<Field>::dest_op_src_const &function)
{
    std::cout << "running " << name << std::endl;

    typedef typename Field::value_type value_type;

    std::vector< std::vector<value_type> > symbols;
    symbols.resize(vectors);

    for(uint32_t i = 0; i < symbols.size(); ++i)
    {
        symbols[i].resize(vector_length);
        for(uint32_t j = 0; j < vector_length; ++j)
        {
            symbols[i][j] = rand() %
                std::numeric_limits<value_type>::max();
        }
    }

    Field field;

    // Warm up
    sak::code_warmup warmup;

    while(!warmup.done())
    {
        for(uint32_t i = 0; i < vectors; ++i)
        {

            uint32_t index_one = rand() % vectors;
            uint32_t index_two = rand() % vectors;

            value_type constant = rand() %
                std::numeric_limits<value_type>::max();

            function(field, constant, &(symbols[index_one][0]),
                     &(symbols[index_two][0]), vector_length);
        }

        warmup.next_iteration();
    }

    uint64_t needed_iterations = warmup.iterations(target_time);

    boost::timer::cpu_timer timer;
    timer.start();

    for(uint64_t j = 0; j < needed_iterations; ++j)
    {

        for(uint32_t i = 0; i < vectors; ++i)
        {

            uint32_t index_one = rand() % vectors;
            uint32_t index_two = rand() % vectors;

            value_type constant = rand() %
                std::numeric_limits<value_type>::max();


            function(field, constant, &(symbols[index_one][0]),
                      &(symbols[index_two][0]), vector_length);

        }

    }

    timer.stop();

    long double total_sec = sak::seconds_elapsed(timer);

    // Amount of data processed
    long double bytes = static_cast<long double>(
        needed_iterations * vectors * vector_length * sizeof(value_type));

    long double megs = bytes / 1000000.0;
    long double megs_per_second = megs / total_sec;

    std::cout << "Test time " << total_sec << " [s]" << std::endl;
    std::cout << "MB/s = " << megs_per_second << std::endl;

}


// Tests the dest[i] = dest[i] * constant functions
// Where OP can be +,-,*
template<class Field>
void invoke_dest_const(const std::string &name,
                       long double target_time,
                       uint32_t vectors, uint32_t vector_length,
                       const typename run<Field>::dest_const &function)
{
    std::cout << "running " << name << std::endl;

    typedef typename Field::value_type value_type;

    std::vector< std::vector<value_type> > symbols;
    symbols.resize(vectors);

    for(uint32_t i = 0; i < symbols.size(); ++i)
    {
        symbols[i].resize(vector_length);
        for(uint32_t j = 0; j < vector_length; ++j)
        {
            symbols[i][j] = rand() %
                std::numeric_limits<value_type>::max();
        }
    }

    Field field;

    // Warm up
    sak::code_warmup warmup;

    while(!warmup.done())
    {
        for(uint32_t i = 0; i < vectors; ++i)
        {

            uint32_t index = rand() % vectors;

            value_type constant = rand() %
                std::numeric_limits<value_type>::max();

            function(field, constant, &(symbols[index][0]),
                     vector_length);
        }

        warmup.next_iteration();
    }

    uint64_t needed_iterations = warmup.iterations(target_time);

    boost::timer::cpu_timer timer;
    timer.start();

    for(uint64_t j = 0; j < needed_iterations; ++j)
    {

        for(uint32_t i = 0; i < vectors; ++i)
        {

            uint32_t index = rand() % vectors;

            value_type constant = rand() %
                std::numeric_limits<value_type>::max();

            function(field, constant, &(symbols[index][0]),
                     vector_length);

        }

    }

    timer.stop();

    long double total_sec = sak::seconds_elapsed(timer);


    // Amount of data processed
    long double bytes = static_cast<long double>(
        needed_iterations * vectors * vector_length * sizeof(value_type));

    long double megs = bytes / 1000000.0;
    long double megs_per_second = megs / total_sec;

    std::cout << "Test time " << total_sec << " [s]" << std::endl;
    std::cout << "MB/s = " << megs_per_second << std::endl;

}


// Helper function used to invoke the different arithmetic
// operations for each field implementation.
template<class Field>
void benchmark(const std::string &name)
{
    uint32_t vectors = 100;
    uint32_t vector_length = 1400;

    long double time = 5.0;

    typedef Field field_type;

    {
        typename run<field_type>::dest_op_src function;

        function = &fifi::add<field_type>;

        invoke_dest_op_src<field_type>(
            name + " add", time, vectors, vector_length, function);

        function = &fifi::subtract<field_type>;

        invoke_dest_op_src<field_type>(
            name + " subtract", time, vectors, vector_length, function);

        function = &fifi::multiply<field_type>;

        invoke_dest_op_src<field_type>(
            name + " multiply", time, vectors, vector_length, function);
    }

    {

        typename run<field_type>::dest_op_src_const function;

        function = &fifi::multiply_add<field_type>;

        invoke_dest_op_src_const<field_type>(
            name + " multiply_add", time, vectors, vector_length, function);

        function = &fifi::multiply_subtract<field_type>;

        invoke_dest_op_src_const<field_type>(
            name + " multiply_subtract", time, vectors, vector_length, function);
    }

    {

        typename run<field_type>::dest_const function;

        function = &fifi::multiply_constant<field_type>;

        invoke_dest_const<field_type>(
            name + " multiply_constant", time, vectors, vector_length, function);

    }

}

int main()
{

    srand(static_cast<uint32_t>(time(0)));

    benchmark< fifi::simple_online<fifi::binary8> >(
        "Simple Online Binary8");

    benchmark< fifi::simple_online<fifi::binary16> >(
        "Simple Online Binary16");

    benchmark< fifi::full_table<fifi::binary8> >(
        "Full Table Binary8");

    benchmark<fifi::log_table<fifi::binary8> >(
        "Log Table Binary8");

    benchmark<fifi::log_table<fifi::binary16> >(
        "Log Table Binary16");

    benchmark<fifi::extended_log_table<fifi::binary8> >(
        "Extended Log Table Binary8");

    benchmark<fifi::extended_log_table<fifi::binary16> >(
        "Extended Log Table Binary16");

    benchmark<fifi::optimal_prime<fifi::prime2325> >(
        "Optimal Prime Prime2325");

    return 0;
}

