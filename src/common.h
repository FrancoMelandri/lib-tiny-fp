#ifndef LIB_TINY_FP_COMMON
#define LIB_TINY_FP_COMMON
#include <iostream>
#include <vector>
#include <list>
#include <vector>
#include <cstddef>
#include <functional>
#include <stdexcept>

#define NO_VALUE NULL

namespace TinyFp 
{ 
    struct Unit
    {
    public:
        static Unit Default() { return Unit();}
    };
}

#endif
