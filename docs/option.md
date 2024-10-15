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
template <class R> Option<R> map(FuncValue<R, T> map);
```

## guardMap

```c++
template <class R> Option<R> guardMap(FuncValue<R, T> defaultMap, const Guards<R, T>& guards);
```

## bind

```c++
template <class R> Option<R> bind(FuncValue<Option<R>, T> bind);
```

## guardBind

```c++
template <class R> Option<R> guardBind(FuncValue<Option<R>, T> defaultBind, const Guards<Option<R>, T>& guards);
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
template <class R> R match(FuncValue<R, T> some, function<R()> none);
```
