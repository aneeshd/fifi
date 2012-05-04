// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <fifi/optimal_prime.h>
#include <fifi/field_types.h>


TEST(test_optimal_prime, multiply)
{
    fifi::optimal_prime<fifi::prime2325> optimal;

    EXPECT_EQ( optimal.multiply(4294967290U, 0U), 0U );
    EXPECT_EQ( optimal.multiply(4294967290U, 1U), 4294967290U );
    EXPECT_EQ( optimal.multiply(4294967290U, 2U), 4294967289U );
    EXPECT_EQ( optimal.multiply(4294967290U, 4294967290U)   , 1U );


    /// Tested using Python:
    /// import random
    ///
    /// r1 = random.randint(0,2**32-5)
    /// r2 = random.randint(0,2**32-5)
    ///
    /// res = (r1*r2) % (2**32-5)
    ///
    EXPECT_EQ( optimal.multiply(3301510135U, 2380300242U) , 3460816498U );
    EXPECT_EQ( optimal.multiply(2747836187U, 606517521U)  , 4005335094U );
    EXPECT_EQ( optimal.multiply(4071004727U, 3893610017U) , 3098938562U );
    EXPECT_EQ( optimal.multiply(3216464703U, 2321361148U) , 2159784831U );
    EXPECT_EQ( optimal.multiply(3948329266U, 1846670630U) , 2958898160U );
    EXPECT_EQ( optimal.multiply(549534826U, 3692094631U)  , 3813011302U );
    EXPECT_EQ( optimal.multiply(890246292U, 3115294715U)  , 3374921530U );
    EXPECT_EQ( optimal.multiply(4065585297U, 1282846608U) , 1407859229U );
    EXPECT_EQ( optimal.multiply(465046300U, 2490793713U)  , 1292002396U );
    EXPECT_EQ( optimal.multiply(329125604U, 1125285055U)  , 64911094U );
    EXPECT_EQ( optimal.multiply(292183365U, 98702877U)    , 3472541934U );
    EXPECT_EQ( optimal.multiply(3509643596U, 1005952927U) , 217974344U );
    EXPECT_EQ( optimal.multiply(1088564772U, 2666620140U) , 2614656028U );
    EXPECT_EQ( optimal.multiply(1708839543U, 6080196U)    , 3721248180U );
    EXPECT_EQ( optimal.multiply(2452969238U, 4067666644U) , 524100996U );
    EXPECT_EQ( optimal.multiply(2653007858U, 2001584548U) , 2373753781U );
    EXPECT_EQ( optimal.multiply(3764782301U, 2438172530U) , 666616654U );
    EXPECT_EQ( optimal.multiply(2328663233U, 3756359853U) , 2772253748U );
    EXPECT_EQ( optimal.multiply(1399444321U, 898799570U)  , 3524721531U );
    EXPECT_EQ( optimal.multiply(3821191152U, 2689111356U) , 2145330644U );
}


TEST(test_optimal_prime, prime2325randCheck)
{
    fifi::optimal_prime<fifi::prime2325> optimal;

    int elements = 1000;

    for(int i = 0; i < elements; ++i)
    {
        fifi::prime2325::value_type v = rand() % fifi::prime2325::order;

        if(v == 0)
            ++v;

        EXPECT_EQ( optimal.multiply(v, optimal.invert(v)), 1U);
        EXPECT_EQ( optimal.multiply(v, optimal.divide(1, v)), 1U);
    }
}





