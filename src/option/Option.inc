namespace TinyFp
{
  template <class T>
  bool Option<T>::IsSome()
  {
    return _value != NO_VALUE;
  }

  template <class T>
  template <class R>
  R Option<T>::OrElse(std::function<R()> none)
  {
    return IsSome()
      ? *_value
      : none();
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::Map(std::function<R*(T*)> map)
  {
    return IsSome()
      ? Option<R>::Some(map(_value))
      : Option<R>::None();
  }
}
