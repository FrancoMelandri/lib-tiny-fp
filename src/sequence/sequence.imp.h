namespace TinyFp 
{
    template <class T>
    T Sequence<T>::firstOf(function<bool(const T&)> of)
    {
        auto item = TinyFp::Extensions::firstOf(_vector, of);
        return item;
    }

    template <class T>
    T Sequence<T>::firstOfOrDefault(function<bool(const T&)> of, const T& def)
    {
        auto item = TinyFp::Extensions::firstOfOrDefault(_vector, of, def);
        return item;
    }

    template <class T>
    template<class R>
    R Sequence<T>::fold(const R& state, function<R(const R&, const T&)> step)
    {
        R initState = state;
        for (auto & item : _vector) {
            initState = step(initState, item);
        }
        return initState;
    }
}