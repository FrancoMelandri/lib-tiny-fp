namespace TinyFp
{
  template <typename T>
  bool Option<T>::IsSome()
  {
    return _value != NO_VALUE;
  }

  template <typename T>
  template <typename R>
  R Option<T>::OrElse(std::function<R()> none)
  {
    return IsSome()
      ? *_value
      : none();
  }

/*
  template <typename T>
  template <typename R>
  Option<R> Option<T>::Map(std::function<R(T*)> map)
  {
    return IsSome()
      ? Option<R>::Some(&(map(_value)))
      : Option<R>::None();
  }

  template <typename T>
  template <typename R>
  R Option<T>::Match(R (*some)(T*), R (*none)())
  {
    return IsSome()
      ? some(_value)
      : none();
  }
*/
}
