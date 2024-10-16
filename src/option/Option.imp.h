namespace TinyFp
{
  template <class T>
  bool Option<T>::isSome()
  {
    return _isSome;
  }

  template <class T>
  template <class R>
  R Option<T>::orElse(Nullary<R> none)
  {
    return isSome()
      ? _value
      : none();
  }

  template <class T>
  T Option<T>::unwrap()
  {
    if (isSome())
      return _value;
    throw exception();
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::map(Unary<T, R> map)
  {
    if (!isSome())
      return Option<R>::none();
    auto retVal = map(_value);
    return Option<R>::some(retVal);
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::guardMap(Unary<T, R> defaultMap, const Guards<T, R>& guards)
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
  Option<R> Option<T>::bind(Unary<T, Option<R>> bind)
  {
    if (!isSome())
      return Option<R>::none();
    auto retVal = bind(_value);
    return retVal;
  }

  template <class T>
  template <class R>
  Option<R> Option<T>::guardBind(Unary<T, Option<R>> defaultBind, const Guards<T, Option<R>>& guards)
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
  R Option<T>::match(Unary<T, R> some, Nullary<R> none)
  {
    return isSome()
      ? some(_value)
      : none();
  }

  template <class T>
  template <class L>
  Either<L, T> Option<T>::toEither(Nullary<L> leftValue)
  {
    if (isSome())
      return Either<L, T>::right(_value);
    auto left = leftValue();
    return Either<L, T>::left(left);
  }
}
