#ifndef __LIB_TINY_FP_OPTION__
#define __LIB_TINY_FP_OPTION__

#include <cstddef>

using namespace std;

namespace TinyFp
{
  template <typename T>
  class Option
  {
    private:
      bool _isSome;
      T* _value;

      Option()
      {
          _isSome = false;
          _value = NULL;
      }

      Option(T* value)
      {
          _isSome = true;
          _value = value;
      }

    public:
      static Option<T>* None() { return new Option<T>(); };
      static Option<T>* Some(T* value) { return new Option<T>(value); };
      bool IsSome();
  };
}


namespace TinyFp
{
  template <typename T>
  bool Option<T>::IsSome()
  {
    return _isSome;
  }
}

#endif