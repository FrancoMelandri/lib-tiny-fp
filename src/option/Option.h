#ifndef LIB_TINY_FP_OPTION
#define LIB_TINY_FP_OPTION

#include "../Defines.h"

using namespace std;

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

      Option(T& value)
      {
          _isSome = true;
          _value = value;
      }

    public:
      static Option<T> None() { return Option<T>(); };
      static Option<T> Some(T& value) { return Option<T>(value); };
      bool IsSome();
      template <class R> R OrElse(function<R()> none);
      template <class R> Option<R> Map(function<R(T&)> map);
      template <class R> Option<R> GuardMap(
        function<R(T&)> defaultMap,
        vector<tuple<function<bool(T&)>, function<R(T&)>>> guards);
      template <class R> Option<R> Bind(function<Option<R>(T&)> bind);
      template <class R> R Match(function<R(T&)> some, function<R()> none);
  };
}

#include "Option.inc"

#endif