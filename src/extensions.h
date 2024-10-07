#ifndef LIB_TINY_FP_EXTENSION
#define LIB_TINY_FP_EXTENSION

#include "Defines.h"
using namespace std;

namespace TinyFp 
{ 
    template <class Q, class R>
    Q firstOrDefaultMap(
        vector<tuple<function<bool(R&)>, function<Q(R&)>>> guards,
        function<Q(R&)> defaultMap,
        R& value)
    {
        auto mapToInvoke = defaultMap;
        for (auto & guard : guards) {
            auto selector = get<0>(guard);
            if (selector(value)) {
                mapToInvoke = get<1>(guard);
                break;
            }
        }
        auto retVal = mapToInvoke(value);
        return retVal;
    }
}
#endif
