#ifndef LIB_TINY_FP_SEQUENCE
#define LIB_TINY_FP_SEQUENCE

#include "../common.h"
#include "../extensions/vector.h"

using namespace TinyFp::Extensions;
using namespace std;

namespace TinyFp
{
    template<class T>
    class Sequence
    {
        std::vector<T> _vector;

        Sequence(const std::vector<T>& vector)
        {
            _vector = vector;
        };

    public:
        static Sequence from(const std::vector<T>& vector) { return Sequence(vector); };
        T firstOf(function<bool(const T&)> of);
        T firstOfOrDefault(function<bool(const T&)> of, const T& def);
        template<class R> R fold(const R& state, function<R(const R&, const T&)> step);
        template<class R> Sequence<R> map(function<R(const T&)> item);
        Sequence<T> filter(function<bool(const T&)> item);
        T at(int n);
        int size();
    };
}

#include "sequence.imp.h"

#endif