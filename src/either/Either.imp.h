namespace TinyFp
{
  template <class L, class R>
  bool Either<L,R>::IsRight()
  {
    return _isRight;
  }

  template <class L, class R>
  bool Either<L,R>::IsLeft()
  {
    return !_isRight;
  }

  template <class L, class R>
  R Either<L, R>::Right(function<R(const L&)> onLeft)
  {
    return _isRight ?
      _right :
      onLeft(_left);
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::Map(function<Q(const R&)> map)
  {
    if(!IsRight())
      return Either<L, Q>::Left(_left);
    auto retVal = map(_right);
    return Either<L, Q>::Right(retVal);
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::GuardMap(
    function<Q(const R&)> defaultMap,
    const vector<tuple<function<bool(const R&)>, function<Q(const R&)>>>& guards)
  {
    if(!IsRight())
      return Either<L, Q>::Left(_left);

    auto mapToInvoke = defaultMap;
    for (auto & guard : guards) {
        auto selector = get<0>(guard);
        if (selector(_right)) {
            mapToInvoke = get<1>(guard);
            break;
        }
    }
    auto retVal = mapToInvoke(_right);
    return Either<L, Q>::Right(retVal);
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::Bind(function<Either<L, Q>(const R&)> bind)
  {
    if (!IsRight())
      return Either<L, Q>::Left(_left);
    auto retVal = bind(_right);
    return retVal;
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::GuardBind(
    function<Either<L, Q>(const R&)> defaultBind,
    const vector<tuple<function<bool(const R&)>, function<Either<L, Q>(const R&)>>>& guards)
  {
    if (!IsRight())
      return Either<L, Q>::Left(_left);

    auto mapToInvoke = defaultBind;
    for (auto & guard : guards) {
        auto selector = get<0>(guard);
        if (selector(_right)) {
            mapToInvoke = get<1>(guard);
            break;
        }
    }
    auto retVal = mapToInvoke(_right);
    return retVal;
  }

  template <class L, class R>
  template <class Q>
  Q Either<L, R>::Match(function<Q(const R&)> right, function<Q(const L&)> left)
  {
    return IsRight()
      ? right(_right)
      : left(_left);
  }
}
