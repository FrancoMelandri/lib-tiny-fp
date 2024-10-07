namespace TinyFp
{
  template <class T>
  bool Option<T>::IsSome()
  {
    return _isSome;
  }

  template <class T>
  template <class R>
  R Option<T>::OrElse(function<R()> none)
  {
    return IsSome()
      ? _value
      : none();
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::Map(function<R(T&)> map)
  {
    if (!IsSome())
      return Option<R>::None();
    auto retVal = map(_value);
    return Option<R>::Some(retVal);
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::GuardMap(
    function<R(T&)> defaultMap,
    vector<tuple<function<bool(T&)>, function<R(T&)>>> guards)
  {
    if (!IsSome())
      return Option<R>::None();
    auto retVal = firstOrDefaultMap(guards, defaultMap, _value);
    return Option<R>::Some(retVal);
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::Bind(function<Option<R>(T&)> bind)
  {
    if (!IsSome())
      return Option<R>::None();
    auto retVal = bind(_value);
    return retVal;
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::GuardBind(
    function<Option<R>(T&)> defaultBind,
    vector<tuple<function<bool(T&)>, function<Option<R>(T&)>>> guards)
  {
    if (!IsSome())
      return Option<R>::None();
    auto retVal = firstOrDefaultMap(guards, defaultBind, _value);
    return retVal;
  }

  template <class T>
  template <class R>
  R Option<T>::Match(function<R(T&)> some, function<R()> none)
  {
    return IsSome()
      ? some(_value)
      : none();
  }
}
