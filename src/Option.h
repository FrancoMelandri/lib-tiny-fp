#ifndef LIB_TINY_FP_OPTION
#define LIB_TINY_FP_OPTION

#include "Defines.h"

namespace TinyFp
{
  template <typename T>
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
      template <typename R> Option<R> Map(R* (*map)(T*));
  };
}

#include "Option.inc"

#endif