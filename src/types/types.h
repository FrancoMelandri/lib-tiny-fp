#ifndef LIB_TINY_FP_TYPES
#define LIB_TINY_FP_TYPES

#include "../common.h"

namespace TinyFp::Types
{
    template<class A>
    using FuncSelector = std::function<bool(const A&)>;

    template<class B, class A>
    using FuncValue = std::function<B(const A&)>;

    template<class B, class A>
    using Guard = std::tuple<FuncSelector<A>, FuncValue<B, A>>;

    template<class B, class A>
    using GuardVector = std::vector<Guard<B, A>>;
}

#endif