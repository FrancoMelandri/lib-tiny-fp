namespace TinyFp
{
  template <class S>
  bool Try<S>::isSuccess()
  {
    return _isSuccess;
  }

  template <class S>
  S Try<S>::match(std::function<S(const S&)> success, std::function<S(const exception&)> fail)
  {
    auto failure = fail(_fail);
    if (!isSuccess())
      return failure;
    auto succ = success(_success);
    return succ;
  }

  template <class S>
  S* Try<S>::match(std::function<S*(const S&)> success, std::function<S*(const exception&)> fail)
  {
    auto failure = fail(_fail);
    if (!isSuccess())
      return failure;
    auto succ = success(_success);
    return succ;
  }

  template <class S>
  S* Try<S>::match(std::function<S*(const S&)> success)
  {
    auto fail = [](const exception& ex)
    {
        return (S*)NO_VALUE;
    };
    return match(success, fail);
  }
}
