namespace TinyFp
{
  template <class S>
  bool Try<S>::IsSuccess()
  {
    return _isSuccess;
  }

  template <class S>
  S Try<S>::Match(std::function<S(S&)> success, std::function<S(exception&)> fail)
  {
    return IsSuccess()
      ? success(_success)
      : fail(_fail);
  }
}
