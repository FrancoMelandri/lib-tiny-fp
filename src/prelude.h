#ifndef LIB_TINY_FP_PRELUDE
#define LIB_TINY_FP_PRELUDE

#include "Defines.h"
#include "option/Option.h"

namespace TinyFp 
{ 
    template <class A>
    Option<A> createOption(A* value)
    {
        return value == NO_VALUE ?
            Option<A>::None() :
            Option<A>::Some(*value);
    }
}
#endif
