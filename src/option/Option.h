#ifndef LIB_TINY_FP_OPTION
#define LIB_TINY_FP_OPTION

#include "../common.h"
#include "../types/types.h"
#include "../types/types.complex.h"
#include "../either/Either.h"
#include "../extensions/vector.h"

using namespace std;
using namespace TinyFp::Extensions;
using namespace TinyFp::Types;

namespace TinyFp
{
  template <class T>
  struct Option
  {
    private:
      bool _isSome;
      T _value;

      Option() { _isSome = false; }
      Option(const T& value)
      {
          _isSome = true;
          _value = value;
      }

    public:
      static Option<T> none() { return Option<T>(); };
      static Option<T> some(const T& value) { return Option<T>(value); };
      bool isSome();
      T unwrap();
      template <class R> R orElse(Nullary<R> none);
      template <class R> Option<R> map(Unary<T, R> map);
      template <class R> Option<R> guardMap(Unary<T, R> defaultMap, const Guards<T, R>& guards);
      template <class R> Option<R> bind(Unary<T, Option<R>> bind);
      template <class R> Option<R> guardBind(Unary<T, Option<R>> defaultBind, const Guards<T, Option<R>>& guards);
      template <class R> R match(Unary<T, R> some, Nullary<R> none);
      template <class L> Either<L, T> toEither(Nullary<L> leftValue);
  };
}

#include "Option.imp.h"

#endif