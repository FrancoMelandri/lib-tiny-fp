namespace TinyFp
{
  template <class T>
  bool OptionRef<T>::IsSome()
  {
    return _isSome;
  }

  template <class T>
  template <class R>
  R OptionRef<T>::OrElse(std::function<R()> none)
  {
    return IsSome()
      ? _value
      : none();
  }

  template <class T>
  template <class R>
  OptionRef<R> OptionRef<T>::Map(std::function<R(T&)> map)
  {
    auto val = map(_value);
    return IsSome()
      ? OptionRef<R>::Some(val)
      : OptionRef<R>::None();
  }
}
