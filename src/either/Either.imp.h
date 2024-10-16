namespace TinyFp
{
  template <class L, class R>
  bool Either<L,R>::isRight()
  {
    return _isRight;
  }

  template <class L, class R>
  bool Either<L,R>::isLeft()
  {
    return !_isRight;
  }

  template <class L, class R>
  R Either<L, R>::right(Unary<L, R> onLeft)
  {
    return _isRight ?
      _right :
      onLeft(_left);
  }

  template <class L, class R>
  R Either<L, R>::unwrap()
  {
    if (_isRight)
      return _right;
    throw exception();
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::map(function<Q(const R&)> map)
  {
    if(!isRight())
      return Either<L, Q>::left(_left);
    auto retVal = map(_right);
    return Either<L, Q>::right(retVal);
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::guardMap(
    function<Q(const R&)> defaultMap,
    const Sequence<tuple<function<bool(const R&)>, function<Q(const R&)>>>& guards)
  {
    if(!isRight())
      return Either<L, Q>::left(_left);

    auto mapToInvoke = defaultMap;
    for (auto & guard : guards) {
        auto selector = get<0>(guard);
        if (selector(_right)) {
            mapToInvoke = get<1>(guard);
            break;
        }
    }
    auto retVal = mapToInvoke(_right);
    return Either<L, Q>::right(retVal);
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::bind(function<Either<L, Q>(const R&)> bind)
  {
    if (!isRight())
      return Either<L, Q>::left(_left);
    auto retVal = bind(_right);
    return retVal;
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::guardBind(
    function<Either<L, Q>(const R&)> defaultBind,
    const Sequence<tuple<function<bool(const R&)>, function<Either<L, Q>(const R&)>>>& guards)
  {
    if (!isRight())
      return Either<L, Q>::left(_left);

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
  Q Either<L, R>::match(function<Q(const R&)> right, function<Q(const L&)> left)
  {
    return isRight()
      ? right(_right)
      : left(_left);
  }
}
