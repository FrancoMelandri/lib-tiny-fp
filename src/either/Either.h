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
      static Either<L, R> Right(const R& value) { return Either<L, R>(value); };
      static Either<L, R> Left(const L& value) { return Either<L, R>(value); };
      bool IsRight();
      bool IsLeft();
      R Right(function<R(L&)> onLeft);
      template <class Q> Either<L, Q> Map(function<Q(const R&)> map);
      template <class Q> Either<L, Q> GuardMap(
        function<Q(R&)> defaultMap,
        vector<tuple<function<bool(R&)>, function<Q(R&)>>> guards);
      template <class Q> Either<L, Q> Bind(function<Either<L, Q>(R&)> bind);
      template <class Q> Either<L, Q> GuardBind(
        function<Either<L, Q>(R&)> defaultBind,
        vector<tuple<function<bool(R&)>, function<Either<L, Q>(R&)>>> guards);
      template <class Q> Q Match(function<Q(R&)> right, function<Q(L&)> left);
  };
}

#include "Either.imp.h"

#endif