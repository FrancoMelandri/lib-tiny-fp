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
        T firstOf(function<bool(T&)> of);
        T firstOfOrDefault(function<bool(T&)> of, T& def);
        template<class R> R fold(const R& state, function<R(R&, T&)> step);
    };
}

#include "sequence.imp.h"

#endif