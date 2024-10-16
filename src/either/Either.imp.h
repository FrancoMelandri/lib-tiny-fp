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
  Either<L, Q> Either<L, R>::map(Unary<R, Q> map)
  {
    if(!isRight())
      return Either<L, Q>::left(_left);
    auto retVal = map(_right);
    return Either<L, Q>::right(retVal);
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::guardMap(Unary<R, Q> defaultMap, const Guards<R, Q>& guards)
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
  Either<L, Q> Either<L, R>::bind(Unary<R, Either<L, Q>> bind)
  {
    if (!isRight())
      return Either<L, Q>::left(_left);
    auto retVal = bind(_right);
    return retVal;
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::guardBind(Unary<R, Either<L, Q>> defaultBind, const Guards<R, Either<L, Q>>& guards)
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
  Q Either<L, R>::match(Unary<R, Q> right, Unary<L, Q> left)
  {
    return isRight()
      ? right(_right)
      : left(_left);
  }
}
