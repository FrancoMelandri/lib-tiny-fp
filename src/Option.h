#ifndef LIB_TINY_FP_OPTION
#define LIB_TINY_FP_OPTION

#include "Defines.h"

namespace TinyFp
{
  template <class T>
  struct Option
  {
    private:
      T* _value;

      Option()
      {
          _value = NO_VALUE;
      }

      Option(T* value)
      {
          _value = value;
      }

    public:
      static Option<T> None() { return Option<T>(); };
      static Option<T> Some(T* value) { return Option<T>(value); };
      bool IsSome();
      template <class R> R OrElse(std::function<R()> none);
      template <class R> Option<R> Map(std::function<R*(T*)> map);
      // template <typename R> R Match(R (*some)(T*), R (*none)());
  };
}

#include "Option.inc"

#endif