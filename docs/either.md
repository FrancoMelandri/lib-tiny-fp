# Either

## factories

## right

```c++
static Either<L, R> right(const R& value);
```

creating `Either` in right status

## left

```c++
static Either<L, R> left(const L& value);
```

creating `Either` in left status


## composition

### map

```c++
template <class Q> Either<L, Q> map(FuncValue<Q, R> map);
```

### guardMap

```c++
template <class Q> Either<L, Q> guardMap(FuncValue<Q, R> defaultMap, const Guards<Q, R>& guards);
```

### bind

```c++
template <class Q> Either<L, Q> bind(FuncValue<Either<L, Q>, R> bind);
```

### guardBind

```c++
template <class Q> Either<L, Q> guardBind(function<Either<L, Q>(const R&)> defaultBind, const Guards<Either<L, Q>, R>& guards);
```

## accessing


### isRight

```c++
bool isRight();
```

### isLeft

```c++
bool isLeft();
```

### right

```c++
R right(FuncValue<R, L> onLeft);
```

### match

```c++
template <class Q> Q match(FuncValue<Q, R> right, FuncValue<Q, L> left);
```
access to the wrapped status using succes and fail callback to map the internal status.

