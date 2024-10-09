#ifndef LIB_TINY_FP_EXTENSIONS_VECTOR
#define LIB_TINY_FP_EXTENSIONS_VECTOR

using namespace std;

namespace TinyFp::Extensions
{ 
    template <class A>
    A firstOf(
        vector<A>& items,
        function<bool(A&)> of)
    {
        A retVal;
        for (auto & item : items) {
            if (of(item)) {
                retVal = item;
                break;
            }
        }
        return retVal;
    }

    template <class A>
    A firstOfOrDefault(
        vector<A>& items,
        function<bool(A&)> of,
        A& def)
    {
        A retVal = def;
        for (auto & item : items) {
            if (of(item)) {
                retVal = item;
                break;
            }
        }
        return retVal;
    }

    template <class A, class B>
    function<A(B&)> firstOrDefault(
        vector<tuple<function<bool(B&)>, function<A(B&)>>>& guards,
        function<A(B&)> defaultMap,
        B& value)
    {
        auto mapToInvoke = defaultMap;
        for (auto & guard : guards) {
            auto selector = get<0>(guard);
            if (selector(value)) {
                mapToInvoke = get<1>(guard);
                break;
            }
        }
        return mapToInvoke;
    }

    template <class A, class B>
    A firstOrDefaultMap(
        vector<tuple<function<bool(B&)>, function<A(B&)>>> guards,
        function<A(B&)> defaultMap,
        B& value)
    {
        auto mapToInvoke = firstOrDefault(guards, defaultMap, value);
        auto retVal = mapToInvoke(value);
        return retVal;
    }
}
#endif
