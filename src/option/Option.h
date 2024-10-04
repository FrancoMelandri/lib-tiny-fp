#ifndef LIB_TINY_FP_OPTION
#define LIB_TINY_FP_OPTION

#include "../Defines.h"

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
  };

  template <class T>
  struct OptionRef
  {
    private:
      bool _isSome;
      T _value;

      OptionRef()
      {
          _isSome = false;
      }

      OptionRef(T& value)
      {
          _isSome = true;
          _value = value;
      }

    public:
      static OptionRef<T> None() { return OptionRef<T>(); };
      static OptionRef<T> Some(T& value) { return OptionRef<T>(value); };
      bool IsSome();
      template <class R> R OrElse(std::function<R()> none);
      template <class R> OptionRef<R> Map(std::function<R(T&)> map);
      template <class R> R Match(std::function<R(T&)> some, std::function<R()> none);
  };
}

#include "Option.inc"
#include "OptionRef.inc"

#endif