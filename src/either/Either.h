#ifndef LIB_TINY_FP_EITHER
#define LIB_TINY_FP_EITHER

#include "../Defines.h"

using namespace std;

namespace TinyFp
{
  template <class L, class R>
  struct Either
  {
    private:
      bool _isRight;
      L _left;
      R _right;

      Either()
      {
      }

      Either(R& value)
      {
          _isRight = true;
          _right = value;
      }

      Either(L& value)
      {
          _isRight = false;
          _left = value;
      }

    public:
      static Either<L, R> Right(R& value) { return Either<L, R>(value); };
      static Either<L, R> Left(L& value) { return Either<L, R>(value); };
      bool IsRight();
      bool IsLeft();
      R Right(function<R(L&)> onLeft);
      template <class Q> Either<L, Q> Map(function<Q(R&)> map);
      template <class Q> Either<L, Q> GuardMap(
        function<Q(R&)> defaultMap,
        vector<tuple<function<bool(R&)>, function<Q(R&)>>> guards);
      template <class Q> Either<L, Q> Bind(function<Either<L, Q>(R&)> bind);
      template <class Q> Q Match(function<Q(R&)> right, function<Q(L&)> left);
  };
}

#include "Either.inc"

#endif