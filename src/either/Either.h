#ifndef LIB_TINY_FP_EITHER
#define LIB_TINY_FP_EITHER

#include "../common.h"
#include "../types/types.h"
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
      template <class Q> Either<L, Q> map(FuncValue<Q, R> map);
      template <class Q> Either<L, Q> guardMap(
        FuncValue<Q, R> defaultMap,
        const Guards<Q, R>& guards);
      template <class Q> Either<L, Q> bind(FuncValue<Either<L, Q>, R> bind);
      template <class Q> Either<L, Q> guardBind(
        function<Either<L, Q>(const R&)> defaultBind,
        const Guards<Either<L, Q>, R>& guards);
      template <class Q> Q match(FuncValue<Q, R> right, FuncValue<Q, L> left);
  };
}

#include "Either.imp.h"

#endif