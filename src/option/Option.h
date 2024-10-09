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
      static Option<T> None() { return Option<T>(); };
      static Option<T> Some(const T& value) { return Option<T>(value); };
      bool IsSome();
      template <class R> R OrElse(function<R()> none);
      template <class R> Option<R> Map(function<R(const T&)> map);
      template <class R> Option<R> GuardMap(
        function<R(const T&)> defaultMap,
        const vector<tuple<function<bool(const T&)>, function<R(const T&)>>>& guards);
      template <class R> Option<R> Bind(function<Option<R>(T&)> bind);
      template <class R> Option<R> GuardBind(
        function<Option<R>(const T&)> defaultBind,
        const vector<tuple<function<bool(const T&)>, function<Option<R>(const T&)>>>& guards);
      template <class R> R Match(function<R(T&)> some, function<R()> none);
      template <class L> Either<L, T> ToEither(function<L()> leftValue);
  };
}

#include "Option.imp.h"

#endif