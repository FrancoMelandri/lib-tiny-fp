namespace TinyFp::Extensions
{ 
    template <class A>
    A firstOf(
        const vector<A>& items,
        function<bool(const A&)> of)
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
        const vector<A>& items,
        function<bool(const A&)> of,
        const A& def)
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
    function<A(const B&)> firstOrDefault(
        const vector<tuple<function<bool(const B&)>, function<A(const B&)>>>& guards,
        function<A(const B&)> defaultMap,
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
        const vector<tuple<function<bool(const B&)>, function<A(const B&)>>>& guards,
        function<A(const B&)> defaultMap,
        const B& value)
    {
        auto mapToInvoke = firstOrDefault(guards, defaultMap, value);
        auto retVal = mapToInvoke(value);
        return retVal;
    }
}
