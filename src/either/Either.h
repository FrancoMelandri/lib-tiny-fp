#ifndef LIB_TINY_FP_EITHER
#define LIB_TINY_FP_EITHER

#include "../common.h"
#include "../extensions/vector.h"

using namespace std;
using namespace TinyFp::Extensions;

namespace TinyFp
{
  template <class L, class R>
  struct Either
  {
    private:
      bool _isRight;
      L _left;
      R _right;

      Either(const R& value)
      {
          _isRight = true;
          _right = value;
      }

      Either(const L& value)
      {
          _isRight = false;
          _left = value;
      }

    public:
      static Either<L, R> right(const R& value) { return Either<L, R>(value); };
      static Either<L, R> left(const L& value) { return Either<L, R>(value); };
      bool isRight();
      bool isLeft();
      R right(function<R(const L&)> onLeft);
      template <class Q> Either<L, Q> map(function<Q(const R&)> map);
      template <class Q> Either<L, Q> guardMap(
        function<Q(const R&)> defaultMap,
        const vector<tuple<function<bool(const R&)>, function<Q(const R&)>>>& guards);
      template <class Q> Either<L, Q> bind(function<Either<L, Q>(const R&)> bind);
      template <class Q> Either<L, Q> guardBind(
        function<Either<L, Q>(const R&)> defaultBind,
        const vector<tuple<function<bool(const R&)>, function<Either<L, Q>(const R&)>>>& guards);
      template <class Q> Q match(function<Q(const R&)> right, function<Q(const L&)> left);
  };
}

#include "Either.imp.h"

#endif