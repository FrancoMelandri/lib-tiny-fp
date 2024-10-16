# Try

## factories

### handle

```c++
static Try<S> handle(std::function<S()> func);
static Try<S> handle(std::function<S*()> func);
```

handle the exception side effect.


## accessing

### isSuccess

```c++
bool isSuccess();
```
true if no excpetion was thrown; false in case of exception during handling function.


### match

```c++
S match(std::function<S(const S&)> success, std::function<S(const exception&)> fail);
S* match(std::function<S*(const S&)> success, std::function<S*(const exception&)> fail);
S* match(std::function<S*(const S&)> success);
```
access to the wrapped status using succes and fail callback to map the internal status.

```c++

BOOST_AUTO_TEST_CASE(Try_WhenSuccess_ReturnSuccess)
{
    auto onHandle = []()->int
    {
        return 100;
    };

    auto onSuccess = [](int value)
    {
        return value;
    };

    auto onFail = [](const exception& ex)
    {
        int retVal = 42;
        return retVal;
    };

    auto inner = TinyFp::Try<int>::handle(onHandle)
                    .match(
                        onSuccess,
                        onFail);
    BOOST_CHECK(inner == 100);
}

BOOST_AUTO_TEST_CASE(Try_WhenException_ReturnFail)
{
    auto onHandle = []()->int
    {
        throw;
    };

    auto onSuccess = [](int value)
    {
        return value;
    };

    auto onFail = [](const exception& ex)
    {
        int retVal = 42;
        return retVal;
    };

    auto inner = TinyFp::Try<int>::handle(onHandle)
                    .match(
                        onSuccess,
                        onFail);
    BOOST_CHECK(inner == 42);
}
```