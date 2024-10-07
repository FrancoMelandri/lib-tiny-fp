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
  R Either<L, R>::Right(function<R(L&)> onLeft)
  {
    return _isRight ?
      _right :
      onLeft(_left);
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::Map(function<Q(R&)> map)
  {
    if(!IsRight())
      return Either<L, Q>::Left(_left);
    auto retVal = map(_right);
    return Either<L, Q>::Right(retVal);
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::GuardMap(
    function<Q(R&)> defaultMap,
    vector<tuple<function<bool(R&)>, function<Q(R&)>>> guards)
  {
    if(!IsRight())
      return Either<L, Q>::Left(_left);
    auto retVal = firstOrDefaultMap(guards, defaultMap, _right);
    return Either<L, Q>::Right(retVal);
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::Bind(function<Either<L, Q>(R&)> bind)
  {
    if (!IsRight())
      return Either<L, Q>::Left(_left);
    auto retVal = bind(_right);
    return retVal;
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::GuardBind(
    function<Either<L, Q>(R&)> defaultBind,
    vector<tuple<function<bool(R&)>, function<Either<L, Q>(R&)>>> guards)
  {
    if (!IsRight())
      return Either<L, Q>::Left(_left);
    auto retVal = firstOrDefaultMap(guards, defaultBind, _right);
    return retVal;
  }

  template <class L, class R>
  template <class Q>
  Q Either<L, R>::Match(function<Q(R&)> right, function<Q(L&)> left)
  {
    return IsRight()
      ? right(_right)
      : left(_left);
  }
}
