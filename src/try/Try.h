#ifndef LIB_TINY_FP_TRY
#define LIB_TINY_FP_TRY

#include "../common.h"
#include "../types/types.h"
#include "../extensions/vector.h"

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
      static Try<S> handle(std::function<S()> func)
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
      static Try<S> handle(std::function<S*()> func)
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
      bool isSuccess();
      S match(std::function<S(const S&)> success, std::function<S(const exception&)> fail);
      S* match(std::function<S*(const S&)> success, std::function<S*(const exception&)> fail);
      S* match(std::function<S*(const S&)> success);
  };
}

#include "Try.imp.h"

#endif