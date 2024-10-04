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
  R Either<L, R>::Right(std::function<R(L&)> onLeft)
  {
    return _isRight ?
      _right :
      onLeft(_left);
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::Map(std::function<Q(R&)> map)
  {
    auto retVal = map(_right);
    return IsRight()
      ? Either<L, Q>::Right(retVal)
      : Either<L, Q>::Left(_left);
  }

  template <class L, class R>
  template <class Q>
  Either<L, Q> Either<L, R>::Bind(std::function<Either<L, Q>(R&)> bind)
  {
    auto retVal = bind(_right);
    return IsRight()
      ? retVal
      : Either<L, Q>::Left(_left);
  }

  template <class L, class R>
  template <class Q>
  Q Either<L, R>::Match(std::function<Q(R&)> right, std::function<Q(L&)> left)
  {
    return IsRight()
      ? right(_right)
      : left(_left);
  }
}
