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
  Option<R> Option<T>::Map(function<R(const T&)> map)
  {
    if (!IsSome())
      return Option<R>::None();
    auto retVal = map(_value);
    return Option<R>::Some(retVal);
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::GuardMap(
    function<R(const T&)> defaultMap,
    const vector<tuple<function<bool(const T&)>, function<R(const T&)>>>& guards)
  {
    if (!IsSome())
      return Option<R>::None();

    auto mapToInvoke = defaultMap;
    for (auto & guard : guards) {
        auto selector = get<0>(guard);
        if (selector(_value)) {
            mapToInvoke = get<1>(guard);
            break;
        }
    }
    auto retVal = mapToInvoke(_value);
    return Option<R>::Some(retVal);
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::Bind(function<Option<R>(const T&)> bind)
  {
    if (!IsSome())
      return Option<R>::None();
    auto retVal = bind(_value);
    return retVal;
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::GuardBind(
    function<Option<R>(const T&)> defaultBind,
    const vector<tuple<function<bool(const T&)>, function<Option<R>(const T&)>>>& guards)
  {
    if (!IsSome())
      return Option<R>::None();

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
  R Option<T>::Match(function<R(const T&)> some, function<R()> none)
  {
    return IsSome()
      ? some(_value)
      : none();
  }

  template <class T>
  template <class L>
  Either<L, T> Option<T>::ToEither(function<L()> leftValue)
  {
    if (IsSome())
      return Either<L, T>::Right(_value);
    auto left = leftValue();
    return Either<L, T>::Left(left);
  }
}
