#include "Option.h"
#include <cstddef>

namespace TinyFp
{
    template <typename T>
    static TinyFp::Option<T>* None()
    {
        return new Option<T>(false, NULL);
    }

    template <typename T>
    static TinyFp::Option<T>* Some(T value)
    {
        return new Option<T>(true, value);
    }

    template<class T>
    bool Option<T>::IsSome()
    {
        return _isSome;
    }
}