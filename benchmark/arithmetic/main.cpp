// Copyright Steinwurf APS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE_1_0.txt or
// http://www.steinwurf.dk/licensing

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cmath>

//#include <speedy/time_benchmark.h>
//#include <speedy/result_writer.h>
//#include "../../fifi/default_field_impl.h"


#include <fifi/arithmetics.h>
#include <fifi/fifi_utils.h>

class throughput
{
public:

    throughput(const char* filename)
	: //m_results(filename),
	  m_run_time(2)
	{
	    srand(time(0));
	} 

    template<class FieldImpl, class TestFunction>
    void do_run(const std::string &name, const FieldImpl &/*impl_dummy*/, TestFunction function)
        {
            std::cout << "running " << name << std::endl;

            typedef typename FieldImpl::value_type value_type;
            typedef typename FieldImpl::field_type field_type;
    
            FieldImpl impl;

    //         double function_time_elapsed = 0.0;
    //         bool function_done = false;
            
    //         uint32_t vectors = 1000;
    //         uint32_t iterations = 10000;
    //         uint32_t length = fifi::bytes_to_elements<field_type>(1400);

    //         std::vector<std::vector<value_type> > symbols;
    //         symbols.resize(vectors);

    //         for(uint32_t i = 0; i < symbols.size(); ++i)
    //         {
    //             symbols[i].resize(length);
    //             for(uint32_t j = 0; j < length; ++j)
    //             {
    //                 symbols[i][j] = rand() %
    //                     std::numeric_limits<value_type>::max();
    //             }
    //         }
                    
    //         while(!function_done)
    //         {
    //             // Clock running
    //             PXTimer function_timer;
    //     	function_timer.reset();

    //             for(uint32_t i = 0; i < iterations; ++i)
    //             {
    //                 uint32_t index_one = rand() % vectors;
    //                 uint32_t index_two = rand() % vectors;
    //                 while (index_one == index_two)
    //                 {
    //                     index_two = rand() % vectors;                    
    //                 }
    //                 value_type coefficient = rand() % field_type::order;

    //                 function(impl, coefficient,
    //                          &(symbols[index_one][0]),
    //                          &(symbols[index_two][0]),
    //                          length);
    //             }

    //             // Clock stopped
    //             function_time_elapsed = function_timer.get();
                
    //             if(function_time_elapsed > m_run_time)
    //             {
    //                 function_done = true;
    //             }
    //             else
    //             {
    //                 double factor = m_run_time/function_time_elapsed * 1.1;
    //                 iterations = std::ceil(iterations * factor);
    //             }             
    //         }
    //         double function_troughput =
    //             fifi::bytes_needed<field_type>(length) * iterations
    //             / function_time_elapsed / 1000000;
            
    //         std::cout << "name: " << name << " troughput: " <<
    //             function_troughput << " MB/s" << std::endl;
    //         m_results.write(name, function_troughput);
        }

private:
//    speedy::result_writer m_results;
    
    // The minimum time to benchmark
    uint32_t m_run_time;
};

int main()
{
    {
        typedef fifi::simple_online<fifi::binary> field_type;
        typedef fifi::simple_online<fifi::binary8> field_type_simple8;
        typedef fifi::log_table<fifi::binary8> field_type_log8;
        typedef fifi::extended_log_table<fifi::binary8> field_type_ext_log8;
        typedef fifi::full_table<fifi::binary8> field_type_full8;
        typedef fifi::simple_online<fifi::binary16> field_type_simple16;
        typedef fifi::log_table<fifi::binary16> field_type_log16;
        typedef fifi::extended_log_table<fifi::binary16> field_type_ext_log16;
        
        throughput test_mult_add("multiply_add.xml");

        test_mult_add.do_run("simple_online_binary",
                    field_type(),
                    &fifi::multiply_add<fifi::simple_online>);

        test_mult_add.do_run("simple_online_binary8",
                    field_type_simple8(),
                    &fifi::multiply_subtract<field_type_simple8>);

        test_mult_add.do_run("log_table_binary8",
                    field_type_log8(),
                    &fifi::multiply_subtract<field_type_log8>);

        test_mult_add.do_run("extended_log_table_binary8",
                    field_type_ext_log8(),
                    &fifi::multiply_subtract<field_type_ext_log8>);

        test_mult_add.do_run("full_table_binary8",
                    field_type_full8(),
                    &fifi::multiply_subtract<field_type_full8>);
        
        test_mult_add.do_run("simple_online_binary16",
                    field_type_simple16(),
                    &fifi::multiply_subtract<field_type_simple16>);

        test_mult_add.do_run("log_table_binary16",
                    field_type_log16(),
                    &fifi::multiply_subtract<field_type_log16>);

        test_mult_add.do_run("extended_log_table_binary16",
                    field_type_ext_log16(),
                    &fifi::multiply_subtract<field_type_ext_log16>);

        throughput test_mult_subtract("multiply_subtract.xml");
        
        test_mult_subtract.do_run("simple_online_binary",
                    field_type(),
                    &fifi::multiply_add<fifi::simple_online>);

        test_mult_subtract.do_run("simple_online_binary8",
                    field_type_simple8(),
                    &fifi::multiply_subtract<field_type_simple8>);

        test_mult_subtract.do_run("log_table_binary8",
                    field_type_log8(),
                    &fifi::multiply_subtract<field_type_log8>);

        test_mult_subtract.do_run("extended_log_table_binary8",
                    field_type_ext_log8(),
                    &fifi::multiply_subtract<field_type_ext_log8>);

        test_mult_subtract.do_run("full_table_binary8",
                    field_type_full8(),
                    &fifi::multiply_subtract<field_type_full8>);
        
        test_mult_subtract.do_run("simple_online_binary16",
                    field_type_simple16(),
                    &fifi::multiply_subtract<field_type_simple16>);

        test_mult_subtract.do_run("log_table_binary16",
                    field_type_log16(),
                    &fifi::multiply_subtract<field_type_log16>);

        test_mult_subtract.do_run("extended_log_table_binary16",
                    field_type_ext_log16(),
                    &fifi::multiply_subtract<field_type_ext_log16>);
    }
    
    return 0;
}

