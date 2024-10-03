#ifndef __LIB_TINY_FP_OPTION__
#define __LIB_TINY_FP_OPTION__

#include <cstddef>

using namespace std;

#define NO_VALUE NULL

namespace TinyFp
{
  template <typename T>
  class Option
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
      static Option<T>* None() { return new Option<T>(); };
      static Option<T>* Some(T* value) { return new Option<T>(value); };
      bool IsSome();
      template <typename R> Option<R>* Map(R* (*map)(T*));
  };
}

#include "Option.inc"

#endif