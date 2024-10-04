#ifndef LIB_TINY_FP_EITHER
#define LIB_TINY_FP_EITHER

#include "../Defines.h"

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
      R Right(std::function<R(L&)> onLeft);
      template <class Q> Either<L, Q> Map(std::function<Q(R&)> map);
      // template <class R> Either<R> Bind(std::function<Option<R>(T&)> bind);
      // template <class R> R Match(std::function<R(T&)> some, std::function<R()> none);
  };
}

#include "Either.inc"

#endif