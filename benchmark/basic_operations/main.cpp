// Copyright Steinwurf APS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE_1_0.txt or
// http://www.steinwurf.dk/licensing

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <speedy/time_benchmark.h>
#include <speedy/result_writer.h>
#include "../../fifi/simple_online.h"
#include "../../fifi/full_table.h"
#include "../../fifi/log_table.h"
#include "../../fifi/extended_log_table.h"
#include "../../fifi/optimal_prime.h"
#include "../../fifi/field_types.h"

using namespace std;

const static int EXETIME = 2;
const static int ELEMENTS = 1000000; 

class ArithmeticTest
{

public:
    ArithmeticTest();

    void run();
    
private:
    speedy::result_writer m_divide_results;
    speedy::result_writer m_multiply_results;
    speedy::result_writer m_add_results;
    speedy::result_writer m_subtract_results;
    template<class Field> void multiplyData(const std::string &name);
    template<class Field> void divideData(const std::string &name);
    template<class Field> void addData(const std::string &name);
    template<class Field> void subtractData(const std::string &name);
    /**
      * ADD ALL THE INVERT ADD, SUBTRACT functions here
      * we need it just to make sure we never by accident
      * create a regression.
      */


};

ArithmeticTest::ArithmeticTest()
    : m_divide_results("divide_results.xml"),
      m_multiply_results("multiply_results.xml"),
      m_add_results("add_results.xml"),
      m_subtract_results("subtract_results.xml")
{
    srand(time(0));
}

template<class Field>
void ArithmeticTest::multiplyData(const std::string &name)
{
    cout << "running " << name << endl;
    typedef typename Field::value_type value_type;

    int elements = ELEMENTS;

    value_type *a = new value_type[elements];
    value_type *b = new value_type[elements];
    value_type *r = new value_type[elements];

    for(int i = 0; i < elements; ++i)
    {
        a[i] = rand();
        b[i] = rand();
    }


    Field field;

    // Warm up
    for(int i = 0; i < elements; ++i)
    {
        r[i] = field.multiply(a[i], b[i]);
    }

    speedy::time_benchmark benchmark(EXETIME);

    while(!benchmark.done())
    {
        benchmark.start();
        for(;benchmark.running();benchmark.next())
        {
            for(int i = 0; i < elements; ++i)
            {
                r[i] = field.multiply(a[i], b[i]);
            }
        }
        benchmark.stop();
    }


    //amount of data processed
    double megs = (elements*sizeof(value_type))/1000000.0;
    double megs_per_second = megs / benchmark.time_per_iteration();

    m_multiply_results.write(name, megs_per_second);

    delete [] a;
    delete [] b;
    delete [] r;

}

template<class Field>
void ArithmeticTest::divideData(const std::string &name)
{
    cout << "running " << name << endl;
    typedef typename Field::value_type value_type;

    int elements = ELEMENTS;

    value_type *a = new value_type[elements];
    value_type *b = new value_type[elements];
    value_type *r = new value_type[elements];

    for(int i = 0; i < elements; ++i)
    {
        a[i] = rand();
        b[i] = rand();

        // Make sure there are only non-zero values in
        // b[] (the denominator)
        if(b[i] == 0)
            b[i] = 1;
    }


    Field field;

    // Warm up
    for(int i = 0; i < elements; ++i)
    {
        r[i] = field.divide(a[i], b[i]);
    }

    speedy::time_benchmark benchmark(EXETIME);

    while(!benchmark.done())
    {
        benchmark.start();
        for(;benchmark.running();benchmark.next())
        {
            for(int i = 0; i < elements; ++i)
            {
                r[i] = field.divide(a[i], b[i]);
            }
        }
        benchmark.stop();
    }

    //amount of data processed
    double megs = (elements*sizeof(value_type))/1000000.0;
    double megs_per_second = megs / benchmark.time_per_iteration();

    m_divide_results.write(name, megs_per_second);

    delete a;
    delete b;
    delete r;
    

}

template<class Field>
void ArithmeticTest::addData(const std::string &name)
{
    cout << "running " << name << endl;
    typedef typename Field::value_type value_type;

    int elements = ELEMENTS;

    value_type *a = new value_type[elements];
    value_type *b = new value_type[elements];
    value_type *r = new value_type[elements];

    for(int i = 0; i < elements; ++i)
    {
        a[i] = rand();
        b[i] = rand();

        // Make sure there are only non-zero values in
        // b[] (the denominator)
        if(b[i] == 0)
            b[i] = 1;
    }


    Field field;

    // Warm up
    for(int i = 0; i < elements; ++i)
    {
        r[i] = field.add(a[i], b[i]);
    }

    speedy::time_benchmark benchmark(EXETIME);

    while(!benchmark.done())
    {
        benchmark.start();
        for(;benchmark.running();benchmark.next())
        {
            for(int i = 0; i < elements; ++i)
            {
                r[i] = field.add(a[i], b[i]);
            }
        }
        benchmark.stop();
    }

    //amount of data processed
    double megs = (elements*sizeof(value_type))/1000000.0;
    double megs_per_second = megs / benchmark.time_per_iteration();

    m_add_results.write(name, megs_per_second);

    delete a;
    delete b;
    delete r;
    

}

template<class Field>
void ArithmeticTest::subtractData(const std::string &name)
{
    cout << "running " << name << endl;
    typedef typename Field::value_type value_type;

    int elements = ELEMENTS;

    value_type *a = new value_type[elements];
    value_type *b = new value_type[elements];
    value_type *r = new value_type[elements];

    for(int i = 0; i < elements; ++i)
    {
        a[i] = rand();
        b[i] = rand();

        // Make sure there are only non-zero values in
        // b[] (the denominator)
        if(b[i] == 0)
            b[i] = 1;
    }


    Field field;

    // Warm up
    for(int i = 0; i < elements; ++i)
    {
        r[i] = field.subtract(a[i], b[i]);
    }

    speedy::time_benchmark benchmark(EXETIME);

    while(!benchmark.done())
    {
        benchmark.start();
        for(;benchmark.running();benchmark.next())
        {
            for(int i = 0; i < elements; ++i)
            {
                r[i] = field.subtract(a[i], b[i]);
            }
        }
        benchmark.stop();
    }

    //amount of data processed
    double megs = (elements*sizeof(value_type))/1000000.0;
    double megs_per_second = megs / benchmark.time_per_iteration();

    m_subtract_results.write(name, megs_per_second);

    delete a;
    delete b;
    delete r;
    

}




void ArithmeticTest::run()
{
    multiplyData<fifi::simple_online<fifi::binary8> >("Sim. Online Multi. Binary8");

    divideData<fifi::simple_online<fifi::binary8> >("Sim. Online Divide Binary8");

    addData<fifi::simple_online<fifi::binary8> >("Sim. Online Add Binary8");

    subtractData<fifi::simple_online<fifi::binary8> >("Sim. Online Subtract Binary8");

//    multiplyData<fifi::simple_online<fifi::binary16> >("Sim. Online Multi. Binary16");

//    divideData<fifi::simple_online<fifi::binary16> >("Sim. Online Divide Binary16");

    multiplyData<fifi::full_table<fifi::binary8> >("Full Table Multi. Binary8");

    divideData<fifi::full_table<fifi::binary8> >("Full Table Divide Binary8");

    addData<fifi::full_table<fifi::binary8> >("Full Table Add Binary8");

    subtractData<fifi::full_table<fifi::binary8> >("Full Table Subtract Binary8");

    multiplyData<fifi::log_table<fifi::binary8> >("Log Table Multi. Binary8");

    divideData<fifi::log_table<fifi::binary8> >("Log Table Divide Binary8");

    addData<fifi::log_table<fifi::binary8> >("Log Table Add Binary8");

    subtractData<fifi::log_table<fifi::binary8> >("Log Table Subtract Binary8");

//    multiplyData<fifi::log_table<fifi::binary16> >("Log Table Multi. Binary16");

//    divideData<fifi::log_table<fifi::binary16> >("Log Table Divide Binary16");

//    multiplyData<fifi::extended_log_table<fifi::binary8> >("Ext. Log Table Multi. Binary8");

//    divideData<fifi::extended_log_table<fifi::binary8> >("Ext. Log Table Divide Binary8");

//    multiplyData<fifi::extended_log_table<fifi::binary16> >("Ext. Log Table Multi. Binary16");

//    divideData<fifi::extended_log_table<fifi::binary16> >("Ext. Log Table Divide Binary16");

    multiplyData<fifi::optimal_prime<fifi::prime2325> >("Opt. Prime Multi. Prime2325");

    divideData<fifi::optimal_prime<fifi::prime2325> >("Opt. Prime Divide Prime2325");

    addData<fifi::optimal_prime<fifi::prime2325> >("Opt. Prime Add Prime2325");

    subtractData<fifi::optimal_prime<fifi::prime2325> >("Opt. Prime Subtract Prime2325");
}

int main()
{
    ArithmeticTest test;
    
    for(int i = 0; i < 2; ++i)
    {
	test.run();
	std::cout << "Interation " << i << std::endl;
    
    }

}
