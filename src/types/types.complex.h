#ifndef LIB_TINY_FP_TYPES_COMPLEX
#define LIB_TINY_FP_TYPES_COMPLEX

#include "../sequence/sequence.h"

namespace TinyFp::Types
{
    template<class A, class B>
    using Guards = TinyFp::Sequence<Guard<A, B>>;
}

#endif