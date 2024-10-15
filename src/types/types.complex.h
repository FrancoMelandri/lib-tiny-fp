#ifndef LIB_TINY_FP_TYPES_COMPLEX
#define LIB_TINY_FP_TYPES_COMPLEX

#include "../sequence/sequence.h"

namespace TinyFp::Types
{
    template<class B, class A>
    using Guards = TinyFp::Sequence<Guard<B, A>>;
}

#endif