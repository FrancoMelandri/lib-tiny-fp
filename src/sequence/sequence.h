#ifndef LIB_TINY_FP_SEQUENCE
#define LIB_TINY_FP_SEQUENCE

#include "../common.h"
#include "../types/types.h"
#include "../extensions/vector.h"

using namespace TinyFp::Extensions;
using namespace TinyFp::Types;
using namespace std;

namespace TinyFp
{
    template<class T>
    class Sequence
    {
        typedef typename std::vector<T> SequenceType;
        SequenceType _vector;

        Sequence(const std::vector<T>& vector)
        {
            _vector = vector;
        };

        Sequence(const std::list<T>& list)
        {
            _vector = std::vector<T>();
            for (auto & it : list) {
                _vector.push_back(it);
            }
        };

    public:
        typedef typename SequenceType::iterator iterator;
        typedef typename SequenceType::const_iterator const_iterator;

        static Sequence from(const std::vector<T>& vector) { return Sequence(vector); };
        static Sequence from(const std::list<T>& list) { return Sequence(list); };

        T firstOf(Predicate<T> of);
        T firstOfOrDefault(Predicate<T> of, const T& def);
        template<class R> R fold(const R& state, Binary<R, T, R> step);
        template<class R> Sequence<R> map(Unary<T, R> item);
        Sequence<T> filter(Predicate<T> item);

        T at(int n);
        int size() { return _vector.size(); }
        iterator begin() { return _vector.begin(); }
        const_iterator begin() const { return _vector.begin(); }
        const_iterator cbegin() const { return _vector.cbegin(); }
        iterator end() { return _vector.end(); }
        const_iterator end() const { return _vector.end(); }
        const_iterator cend() const { return _vector.cend(); }
    };
}

#include "sequence.imp.h"

#endif