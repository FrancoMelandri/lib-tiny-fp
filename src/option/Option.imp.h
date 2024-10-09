namespace TinyFp
{
  template <class T>
  bool Option<T>::isSome()
  {
    return _isSome;
  }

  template <class T>
  template <class R>
  R Option<T>::orElse(function<R()> none)
  {
    return isSome()
      ? _value
      : none();
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::map(function<R(const T&)> map)
  {
    if (!isSome())
      return Option<R>::none();
    auto retVal = map(_value);
    return Option<R>::some(retVal);
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::guardMap(
    function<R(const T&)> defaultMap,
    const vector<tuple<function<bool(const T&)>, function<R(const T&)>>>& guards)
  {
    if (!isSome())
      return Option<R>::none();

    auto mapToInvoke = defaultMap;
    for (auto & guard : guards) {
        auto selector = get<0>(guard);
        if (selector(_value)) {
            mapToInvoke = get<1>(guard);
            break;
        }
    }
    auto retVal = mapToInvoke(_value);
    return Option<R>::some(retVal);
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::bind(function<Option<R>(const T&)> bind)
  {
    if (!isSome())
      return Option<R>::none();
    auto retVal = bind(_value);
    return retVal;
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::guardBind(
    function<Option<R>(const T&)> defaultBind,
    const vector<tuple<function<bool(const T&)>, function<Option<R>(const T&)>>>& guards)
  {
    if (!isSome())
      return Option<R>::none();

    auto mapToInvoke = defaultBind;
    for (auto & guard : guards) {
        auto selector = get<0>(guard);
        if (selector(_value)) {
            mapToInvoke = get<1>(guard);
            break;
        }
    }
    auto retVal = mapToInvoke(_value);
    return retVal;
  }

  template <class T>
  template <class R>
  R Option<T>::match(function<R(const T&)> some, function<R()> none)
  {
    return isSome()
      ? some(_value)
      : none();
  }

  template <class T>
  template <class L>
  Either<L, T> Option<T>::toEither(function<L()> leftValue)
  {
    if (isSome())
      return Either<L, T>::right(_value);
    auto left = leftValue();
    return Either<L, T>::left(left);
  }
}
