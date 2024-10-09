#ifndef LIB_TINY_FP_PRELUDE
#define LIB_TINY_FP_PRELUDE

#include "common.h"
#include "option/Option.h"

using namespace std;

namespace TinyFp 
{ 
    template <class A>
    Option<A> makeOption(A* value)
    {
        if (value == NO_VALUE)
            return Option<A>::None();
        return Option<A>::Some(*value);
    }

    template <class A>
    Option<A> makeOption(A* value, function<bool(const A&)> whenNone)
    {
        if (value == NO_VALUE)
            return Option<A>::None();
        auto retVal = *value;
        if (whenNone(retVal))
            return Option<A>::None();
        return Option<A>::Some(retVal);
    }
}
#endif
