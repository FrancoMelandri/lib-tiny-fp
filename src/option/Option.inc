namespace TinyFp
{
  template <class T>
  bool Option<T>::IsSome()
  {
    return _isSome;
  }

  template <class T>
  template <class R>
  R Option<T>::OrElse(std::function<R()> none)
  {
    return IsSome()
      ? _value
      : none();
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::Map(std::function<R(T&)> map)
  {
    auto val = map(_value);
    return IsSome()
      ? Option<R>::Some(val)
      : Option<R>::None();
  }

  template <class T>
  template <class R>
  R Option<T>::Match(std::function<R(T&)> some, std::function<R()> none)
  {
    return IsSome()
      ? some(_value)
      : none();
  }
}
