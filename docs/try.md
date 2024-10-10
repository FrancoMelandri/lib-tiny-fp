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

