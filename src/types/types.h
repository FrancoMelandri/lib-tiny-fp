#ifndef LIB_TINY_FP_TYPES
#define LIB_TINY_FP_TYPES

#include "../common.h"

namespace TinyFp::Types
{
    template<class A>
    using Predicate = std::function<bool(const A&)>;

    template<class A>
    using Nullary = std::function<A()>;

    template<class A, class B>
    using Unary = std::function<B(const A&)>;

    template<class A, class B, class C>
    using Binary = std::function<C(const A&, const B&)>;

    template<class A, class B>
    using Guard = std::tuple<Predicate<A>, Unary<A, B>>;

    template<class A, class B>
    using GuardVector = std::vector<Guard<A, B>>;
}

#endif