#ifndef LIB_TINY_FP_EITHER
#define LIB_TINY_FP_EITHER

#include "../common.h"
#include "../types/types.h"
#include "../types/types.complex.h"
#include "../extensions/vector.h"

using namespace std;
using namespace TinyFp::Extensions;
using namespace TinyFp::Types;

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
      R right(Func<L, R> onLeft);
      template <class Q> Either<L, Q> map(Func<R, Q> map);
      template <class Q> Either<L, Q> guardMap(Func<R, Q> defaultMap, const Guards<R, Q>& guards);
      template <class Q> Either<L, Q> bind(Func<R, Either<L, Q>> bind);
      template <class Q> Either<L, Q> guardBind(Func<R, Either<L, Q>> defaultBind, const Guards<R, Either<L, Q>>& guards);
      template <class Q> Q match(Func<R, Q> right, Func<L, Q> left);
  };
}

#include "Either.imp.h"

#endif