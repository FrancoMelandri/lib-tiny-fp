#ifndef __LIB_TINY_FP_OPTION__
#define __LIB_TINY_FP_OPTION__

using namespace std;

namespace TinyFp
{
  template <typename T> class Option
  {
    private:
      bool _isSome;
      T _value;

      Option(bool isSome, T value)
      {
          _isSome = isSome;
          _value = value;
      }

    public:
      static Option<T>* None();
      static Option<T>* Some(T value);

      bool IsSome();
  };
}

#endif