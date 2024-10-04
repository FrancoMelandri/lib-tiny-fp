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

  /*
  template <class T>
  template <class R>
  R Either<T>::OrElse(std::function<R()> none)
  {
    return IsSome()
      ? _value
      : none();
  }

  template <class T>
  template <class R>
  Either<R> Either<T>::Map(std::function<R(T&)> map)
  {
    auto retVal = map(_value);
    return IsSome()
      ? Either<R>::Some(retVal)
      : Either<R>::None();
  }

  template <class T>
  template <class R>
  Either<R> Either<T>::Bind(std::function<Either<R>(T&)> bind)
  {
    auto retVal = bind(_value);
    return IsSome()
      ? retVal
      : Either<R>::None();
  }

  template <class T>
  template <class R>
  R Either<T>::Match(std::function<R(T&)> some, std::function<R()> none)
  {
    return IsSome()
      ? some(_value)
      : none();
  }
  */
}
