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
      template <class R> R orElse(function<R()> none);
      template <class R> Option<R> map(Func<T, R> map);
      template <class R> Option<R> guardMap(Func<T, R> defaultMap, const Guards<T, R>& guards);
      template <class R> Option<R> bind(Func<T, Option<R>> bind);
      template <class R> Option<R> guardBind(Func<T, Option<R>> defaultBind, const Guards<T, Option<R>>& guards);
      template <class R> R match(Func<T, R> some, function<R()> none);
      template <class L> Either<L, T> toEither(function<L()> leftValue);
  };
}

#include "Option.imp.h"

#endif