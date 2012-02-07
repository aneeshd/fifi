// Copyright Steinwurf APS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE_1_0.txt or
// http://www.steinwurf.dk/licensing

#include "expected_results.h"

// Small helper function to get the size of the arrays
template<class T, uint32_t N>
inline uint32_t dimension_of(T (&)[N])
{
    return N;
}


//
// Multiply binary8
//
const expected_result_2<fifi::binary8> expected_multiply_binary8[] =
{
    // arg1, arg2, result
    { 0,   0,   0   },
    { 0,   2,   0   },
    { 1,   2,   2   },
    { 2,   1,   2   },
    { 1,   1,   1   },
    { 1,   46,  46  },
    { 67,  1,   67  },
    { 5,   5,   17  },
    { 10,  10,  68  },
    { 10,  20,  136 },
    { 25,  10,  250 },
    { 25,  15,  135 },
    { 25,  66,  60  },
    { 12,  87,  195 },
    { 144, 66,  206 },
    { 4,   200, 7   },
    { 110, 7,   23  },
    { 30,  242, 78  },
    { 176, 132, 204 },
    { 200, 200, 158 },
    { 251, 133, 104 },
    { 254, 254, 227 },
    { 255, 255, 226 },
    { 110, 253, 232 }
};

const uint32_t expected_multiply_binary8_size = dimension_of(expected_multiply_binary8);



//
// Divide binary8
//
const expected_result_2<fifi::binary8> expected_divide_binary8[] =
{
    // arg1, arg2, result
    { 0,   2,   0   },
    { 1,   2,   142 },
    { 2,   1,   2   },
    { 1,   1,   1   },
    { 1,   46,  51  },
    { 67,  1,   67  },
    { 5,   5,   1   },
    { 10,  10,  1   },
    { 10,  20,  142 },
    { 25,  10,  42  },
    { 25,  15,  199 },
    { 25,  66,  80  },
    { 12,  87,  182 },
    { 144, 66,  254 },
    { 4,   200, 111 },
    { 110, 7,   125 },
    { 30,  242, 199 },
    { 176, 132, 68  },
    { 200, 200, 1   },
    { 251, 133, 52  },
    { 254, 254, 1   },
    { 255, 255, 1   },
    { 110, 253, 52  }
};

const uint32_t expected_divide_binary8_size = dimension_of(expected_divide_binary8);


//
// Invert binary8
//
const expected_result_1<fifi::binary8> expected_invert_binary8[] =
{
    // arg1, result
    { 1,   1   },
    { 2,   142 },
    { 5,   167 },
    { 10,  221 },
    { 15,  150 },
    { 20,  224 },
    { 25,  222 },
    { 46,  51  },
    { 66,  248 },
    { 67,  213 },
    { 87,  97  },
    { 110, 47  },
    { 132, 124 },
    { 133, 204 },
    { 144, 24  },
    { 200, 210 },
    { 242, 181 },
    { 253, 255 },
    { 254, 126 },
    { 255, 253 }
};

const uint32_t expected_invert_binary8_size = dimension_of(expected_invert_binary8);








//
// Multiply binary16
//
const expected_result_2<fifi::binary16> expected_multiply_binary16[] =
{
    // arg1, arg2, result
    { 0,   0,   0     },
    { 0,   2,   0     },
    { 1,   2,   2     },
    { 2,   1,   2     },
    { 1,   1,   1     },
    { 1,   46,  46    },
    { 67,  1,   67    },
    { 5,   5,   17    },
    { 10,  10,  68    },
    { 10,  20,  136   },
    { 25,  10,  250   },
    { 25,  15,  135   },
    { 25,  66,  1650  },
    { 12,  87,  996   },
    { 144, 66,  9504  },
    { 4,   200, 800   },
    { 110, 7,   266   },
    { 30,  242, 2716  },
    { 176, 132, 23232 },
    { 200, 200, 20544 },
    { 251, 133, 32407 },
    { 254, 254, 21844 },
    { 255, 255, 21845 },
    { 110, 253, 9478  }
};

const uint32_t expected_multiply_binary16_size = dimension_of(expected_multiply_binary16);


//
// Divide binary16
//
const expected_result_2<fifi::binary16> expected_divide_binary16[] =
{
    // arg1, arg2, result
    { 0,   2,   0     },
    { 1,   2,   34821 },
    { 2,   1,   2     },
    { 1,   1,   1     },
    { 1,   46,  2983  },
    { 67,  1,   67    },
    { 5,   5,   1     },
    { 10,  10,  1     },
    { 10,  20,  34821 },
    { 25,  10,  55300 },
    { 25,  15,  24577 },
    { 25,  66,  55164 },
    { 12,  87,  46287 },
    { 144, 66,  54045 },
    { 4,   200, 28050 },
    { 110, 7,   54984 },
    { 30,  242, 34597 },
    { 176, 132, 2247  },
    { 200, 200, 1     },
    { 251, 133, 46436 },
    { 254, 254, 1     },
    { 255, 255, 1     },
    { 110, 253, 825   }
};

const uint32_t expected_divide_binary16_size = dimension_of(expected_divide_binary16);



//
// Invert binary16
//
const expected_result_1<fifi::binary16> expected_invert_binary16[] =
{
    // arg1, result
    { 1,   1     },
    { 2,   34821 },
    { 5,   20482 },
    { 10,  10241 },
    { 15,  49159 },
    { 20,  39941 },
    { 25,  56100 },
    { 46,  2983  },
    { 66,  19094 },
    { 67,  56530 },
    { 87,  55062 },
    { 110, 61399 },
    { 132, 9547  },
    { 133, 63805 },
    { 144, 25710 },
    { 200, 37729 },
    { 242, 46215 },
    { 253, 38174 },
    { 254, 12174 },
    { 255, 7372  }
};

const uint32_t expected_invert_binary16_size = dimension_of(expected_invert_binary16);





