#ifndef LIB_TINY_FP_OPTION
#define LIB_TINY_FP_OPTION

#include "../common.h"
#include "../types/types.h"
#include "../either/Either.h"
#include "../extensions/vector.h"

using namespace std;
using namespace TinyFp::Extensions;

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
      template <class R> Option<R> map(FuncValue<R, T> map);
      template <class R> Option<R> guardMap(FuncValue<R, T> defaultMap, const Guards<R, T>& guards);
      template <class R> Option<R> bind(FuncValue<Option<R>, T> bind);
      template <class R> Option<R> guardBind(FuncValue<Option<R>, T> defaultBind, const Guards<Option<R>, T>& guards);
      template <class R> R match(FuncValue<R, T> some, function<R()> none);
      template <class L> Either<L, T> toEither(function<L()> leftValue);
  };
}

#include "Option.imp.h"

#endif