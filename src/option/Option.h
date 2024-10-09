#ifndef LIB_TINY_FP_OPTION
#define LIB_TINY_FP_OPTION

#include "../common.h"
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

      Option()
      {
          _isSome = false;
      }

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
      template <class R> Option<R> map(function<R(const T&)> map);
      template <class R> Option<R> guardMap(
        function<R(const T&)> defaultMap,
        const vector<tuple<function<bool(const T&)>, function<R(const T&)>>>& guards);
      template <class R> Option<R> bind(function<Option<R>(const T&)> bind);
      template <class R> Option<R> guardBind(
        function<Option<R>(const T&)> defaultBind,
        const vector<tuple<function<bool(const T&)>, function<Option<R>(const T&)>>>& guards);
      template <class R> R match(function<R(const T&)> some, function<R()> none);
      template <class L> Either<L, T> toEither(function<L()> leftValue);
  };
}

#include "Option.imp.h"

#endif