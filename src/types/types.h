#ifndef LIB_TINY_FP_TYPES
#define LIB_TINY_FP_TYPES

#include "../common.h"

namespace TinyFp::Types
{
    template<class A>
    using Predicate = std::function<bool(const A&)>;

    template<class A, class B>
    using Func = std::function<B(const A&)>;

    template<class A, class B>
    using Guard = std::tuple<Predicate<A>, Func<A, B>>;

    template<class A, class B>
    using GuardVector = std::vector<Guard<A, B>>;
}

#endif