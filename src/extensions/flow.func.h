namespace TinyFp::Extensions
{
    template <class S>
    S loop(Nullary<S> init, function<bool(const S&)> enabled, function<S(const S&)> body)
    {
        auto current = init();
        while(enabled(current))
        {
            auto nextstate = body(current);
            current = nextstate;
        }
        return current;
    }

    template <class S>
    S which(Nullary<bool> condition, Nullary<S> onTrue, Nullary<S> onFalse)
    {
        auto current = condition() ? 
            onTrue() :
            onFalse(); 
        return current;
    }

    template <class S, class T>
    S which(const T& input,
            function<bool(const T&)> condition,
            function<S(const T&)> onTrue,
            function<S(const T&)> onFalse)
    {
        auto current = condition(input) ? 
            onTrue(input) :
            onFalse(input); 
        return current;
    }

    template <class S>
    S guard(
        Nullary<S> onDefault,
        const vector<tuple<function<bool()>, function<S()>>>& guards)
    {
        auto toInvoke = onDefault;
        for (auto & guard : guards) {
            auto selector = get<0>(guard);
            if (selector()) {
                toInvoke = get<1>(guard);
                break;
            }
        }
        auto retVal = toInvoke();
        return retVal;
    }

    template <class S, class T>
    S guard(
        const T& value,
        function<S(const T&)> onDefault,
        const vector<tuple<function<bool(const T&)>, function<S(const T&)>>>& guards)
    {
        auto toInvoke = onDefault;
        for (auto & guard : guards) {
            auto selector = get<0>(guard);
            if (selector(value)) {
                toInvoke = get<1>(guard);
                break;
            }
        }
        auto retVal = toInvoke(value);
        return retVal;
    }
}