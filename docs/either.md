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
template <class Q> Either<L, Q> map(function<Q(const R&)> map);
```

### guardMap

```c++
template <class Q> Either<L, Q> guardMap(
        function<Q(const R&)> defaultMap,
        const vector<tuple<function<bool(const R&)>, function<Q(const R&)>& guards);
```

### bind

```c++
template <class Q> Either<L, Q> bind(function<Either<L, Q>(const R&)> bind);
```

### guardBind

```c++
template <class Q> Either<L, Q> guardBind(
        function<Either<L, Q>(const R&)> defaultBind,
        const vector<tuple<function<bool(const R&)>, function<Either<L, Q>(const R&)>>>& guards);
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
R right(function<R(const L&)> onLeft);
```

### match

```c++
template <class Q> Q match(function<Q(const R&)> right, function<Q(const L&)> left);
```
access to the wrapped status using succes and fail callback to map the internal status.

