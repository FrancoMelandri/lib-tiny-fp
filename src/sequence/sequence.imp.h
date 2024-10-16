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
        R accumulator = state;
        for (auto & item : _vector) {
            accumulator = step(accumulator, item);
        }
        return accumulator;
    }

    template <class T>
    template<class R>
    Sequence<R> Sequence<T>::map(Func<T, R> item)
    {
        auto items = vector<R>();
        for (auto & it : _vector) {
            auto mapped = item(it);
            items.push_back(mapped);
        }
        return Sequence<R>::from(items);
    }

    template <class T>
    Sequence<T> Sequence<T>::filter(function<bool(const T&)> item)
    {
        auto items = vector<T>();
        for (auto & it : _vector) {
            if(item(it))
                items.push_back(it);
        }
        return Sequence<T>::from(items);
    }

    template <class T>
    T Sequence<T>::at(int index)
    {
        auto item = _vector.at(index);
        return item;
    }
}