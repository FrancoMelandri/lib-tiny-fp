namespace TinyFp
{
  template <typename T>
  bool Option<T>::IsSome()
  {
    return _value != NO_VALUE;
  }

  template <typename T>
  template <typename R>
  Option<R>* Option<T>::Map(R* (*map)(T*))
  {
    return IsSome()
      ? Option<R>::Some(map(_value))
      : Option<R>::None();
  }
}
