#ifndef LIB_TINY_FP_TRY
#define LIB_TINY_FP_TRY

#include "../Defines.h"
#include "../extensions.h"

using namespace std;

namespace TinyFp
{
  template <class S>
  struct Try
  {
    private:
      bool _isSuccess;
      S _success;
      exception _fail;

      Try(S& value)
      {
        _isSuccess = true;
        _success = value;
      }

      Try(exception& value)
      {
        _isSuccess = false;
        _fail = value;
      }

    public:
      static Try<S> Handle(std::function<S()> func)
      {
        try
        {
          auto retVal = func();
          return Try<S>(retVal);
        }
        catch (...)
        {
          auto failure = std::exception();
          return Try<S>(failure);
        }
      };
      static Try<S> Handle(std::function<S*()> func)
      {
        try
        {
          auto retVal = *func();
          return Try<S>(retVal);
        }
        catch (...)
        {
          auto failure = std::exception();
          return Try<S>(failure);
        }
      };
      bool IsSuccess();
      S Match(std::function<S(S&)> success, std::function<S(exception&)> fail);
      S* Match(std::function<S*(S&)> success, std::function<S*(exception&)> fail);
      S* Match(std::function<S*(S&)> success);
  };
}

#include "Try.imp.h"

#endif