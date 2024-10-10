# Option

## factories

## none

```c++
static Option<T> none();
```

## some

```c++
static Option<T> some(const T& value);
```

## toEither

```c++
template <class L> Either<L, T> toEither(function<L()> leftValue);
```

## composition

## map

```c++
template <class R> Option<R> map(function<R(const T&)> map);
```

## guardMap

```c++
template <class R> Option<R> guardMap(
function<R(const T&)> defaultMap,
const vector<tuple<function<bool(const T&)>, function<R(const T&)>>>& guards);
```

## bind

```c++
template <class R> Option<R> bind(function<Option<R>(const T&)> bind);
```

## guardBind

```c++
template <class R> Option<R> guardBind(
function<Option<R>(const T&)> defaultBind,
const vector<tuple<function<bool(const T&)>, function<Option<R>(const T&)>>>& guards);
```

## accessing

## isSome

```c++
bool isSome();
```

## orElse

```c++
template <class R> R orElse(function<R()> none);
```

## match

```c++
template <class R> R match(function<R(const T&)> some, function<R()> none);
```
