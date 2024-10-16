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
template <class R> Option<R> map(Func<R, T> map);
```

## guardMap

```c++
template <class R> Option<R> guardMap(Func<R, T> defaultMap, const Guards<R, T>& guards);
```

## bind

```c++
template <class R> Option<R> bind(Func<Option<R>, T> bind);
```

## guardBind

```c++
template <class R> Option<R> guardBind(Func<Option<R>, T> defaultBind, const Guards<Option<R>, T>& guards);
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
template <class R> R match(Func<R, T> some, function<R()> none);
```
