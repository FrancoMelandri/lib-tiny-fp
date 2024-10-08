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
    auto failure = fail(_fail);
    if (!IsSuccess())
      return failure;
    auto succ = success(_success);
    return succ;
  }

  template <class S>
  S* Try<S>::Match(std::function<S*(S&)> success, std::function<S*(exception&)> fail)
  {
    auto failure = fail(_fail);
    if (!IsSuccess())
      return failure;
    auto succ = success(_success);
    return succ;
  }

  template <class S>
  S* Try<S>::Match(std::function<S*(S&)> success)
  {
    auto fail = [](exception& ex)
    {
        return (S*)NO_VALUE;
    };
    return Match(success, fail);
  }
}
