// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE_1_0.txt or
// http://www.steinwurf.dk/licensing

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include <fifi/simple_online.h>
#include <fifi/full_table.h>
#include <fifi/log_table.h>
#include <fifi/extended_log_table.h>
#include <fifi/optimal_prime.h>
#include <fifi/field_types.h>

#include <sak/code_warmup.h>

#include <boost/timer/timer.hpp>



template<class Field>
void multiply_loop(const Field &field,
                   typename Field::value_type *pr,
                   const typename Field::value_type *pa,
                   const typename Field::value_type *pb,
                   uint64_t elements)
{
    for(uint64_t i = 0; i < elements; ++i)
    {
        pr[i] = field.multiply(pa[i], pb[i]);
    }
}

template<class Field>
void divide_loop(const Field &field,
                 typename Field::value_type *pr,
                 const typename Field::value_type *pa,
                 const typename Field::value_type *pb,
                 uint64_t elements)
{
    for(uint64_t i = 0; i < elements; ++i)
    {
        pr[i] = field.divide(pa[i], pb[i]);
    }
}

template<class Field>
void add_loop(const Field &field,
              typename Field::value_type *pr,
              const typename Field::value_type *pa,
              const typename Field::value_type *pb,
              uint64_t elements)
{
    for(uint64_t i = 0; i < elements; ++i)
    {
        pr[i] = field.add(pa[i], pb[i]);
    }
}

template<class Field>
void subtract_loop(const Field &field,
                   typename Field::value_type *pr,
                   const typename Field::value_type *pa,
                   const typename Field::value_type *pb,
                   uint64_t elements)
{
    for(uint64_t i = 0; i < elements; ++i)
    {
        pr[i] = field.subtract(pa[i], pb[i]);
    }
}


template<class Field>
struct run
{
    typedef typename Field::value_type value_type;
    typedef void (*function)(const Field &,
                             value_type*,
                             const value_type*,
                             const value_type*,
                             uint64_t elements);
};

template<class Field>
void invoke_run(const std::string &name,
                uint32_t elements, long double target_time,
                const typename run<Field>::function &function)
{
    std::cout << "running " << name << std::endl;
    typedef typename Field::value_type value_type;

    std::vector<value_type> a(elements, 0);
    std::vector<value_type> b(elements, 0);
    std::vector<value_type> r(elements, 0);

    for(uint32_t i = 0; i < elements; ++i)
    {
        a[i] = rand();
        b[i] = rand();

        // Cannot divide by zero
        typename run<Field>::function f = &divide_loop<Field>;

        if( function == f && b[i] == 0 )
            b[i] = 1;
    }

    value_type *pa = &a[0];
    value_type *pb = &b[0];
    value_type *pr = &r[0];

    Field field;

    // Warm up
    sak::code_warmup warmup;

    while(!warmup.done())
    {
        function(field, pr, pa, pb, elements);

        warmup.next_iteration();
    }

    uint64_t needed_iterations = warmup.iterations(target_time);

    boost::timer::cpu_timer timer;
    timer.start();

    for(uint64_t j = 0; j < needed_iterations; ++j)
    {
        function(field, pr, pa, pb, elements);
    }

    timer.stop();

    long double total_sec = sak::seconds_elapsed(timer);

    // Amount of data processed
    long double bytes = needed_iterations * elements * sizeof(value_type);
    long double megs = bytes / 1000000.0;
    long double megs_per_second = megs / total_sec;

    std::cout << "Test time " << total_sec << " [s]" << std::endl;
    std::cout << "MB/s = " << megs_per_second << std::endl;

}



template<class Field>
void benchmark(const std::string &name)
{
    uint32_t elements = 1400;
    long double time = 5.0;

    typedef Field field_type;

    typename run<field_type>::function function;

    function = &multiply_loop<field_type>;

    invoke_run<field_type>(
        name + " multiply", elements, time, function);

    function = &divide_loop<field_type>;

    invoke_run<field_type>(
        name + " divide", elements, time, function);

    function = &add_loop<field_type>;

    invoke_run<field_type>(
        name + " add", elements, time, function);

    function = &subtract_loop<field_type>;

    invoke_run<field_type>(
        name + " subtract", elements, time, function);
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

