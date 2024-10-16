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
template <class Q> Either<L, Q> map(Func<R, Q> map);
```

Map the `Either` using a function as parameter. the uplift to `Either` is done by the map itself.

The paramater function will be called only for right either state, otherwise a left either is returned.


```c++
BOOST_AUTO_TEST_CASE(Either_WhenRight_AndMap_ReturnMapped)
{
    auto onMap = [](long value)
    {
        char retVal = 'a';
        return retVal;
    };
    auto onLeft = [](int value)
    {
        int retVal = 42;
        return retVal;
    };

    long rightValue = 10;
    auto either = TinyFp::Either<int, long>::right(rightValue)
                    .map<char>(onMap);

    auto inner = either.right(onLeft);
    BOOST_CHECK(either.isRight() == true);
    BOOST_CHECK(either.isLeft() == false);
    BOOST_CHECK(inner == 'a');
}
```


### guardMap

```c++
template <class Q> Either<L, Q> guardMap(Func<R, Q> defaultMap, const Guards<Q, R>& guards);
```

**Map** the `Either` using a list of `Guard`, or the **defaultMap** if no match was found.

### bind

```c++
template <class Q> Either<L, Q> bind(Func<R, Either<L, Q>> bind);
```

**Bind** the `Either` using a function as parameter. The difference between map is that you have to define the uplift to either must be in the function inject as parameter.

The paramater function will be called only for right either state, otherwise a left either is returned.

### guardBind

```c++
template <class Q> Either<L, Q> guardBind(function<Either<L, Q>(const R&)> defaultBind, const Guards<R, Either<L, Q>>& guards);
```

**Bind** the `Either` using a list of `Guard`, or the **defaulBind** if no match was found.

## accessing

### isRight

```c++
bool isRight();
```

**true** in case the `Either` is in the right state, otherwise **false**.

### isLeft

```c++
bool isLeft();
```

**true** in case the `Either` is in the left state, otherwise **false**.

### right

```c++
R right(Func<R, L> onLeft);
```

Get the right value of the `Either`.

In case the `Either`is in left state the parameter function should provde a default right value considering the left value.

## unwrap

```c++
R Either<L, R>::unwrap();
```

Get the right value of the `Either`.

In case the `Either`is in left state an exception will be thrown.


```c++
BOOST_AUTO_TEST_CASE(Either_unwrap_whenright_returnstate)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Either<int, FakeClass>::right(test);
    auto test1 = mapped.unwrap();
    BOOST_CHECK(test1.value == 10);
}

BOOST_AUTO_TEST_CASE(Either_unwrap_whenleft_throw)
{
    int left = 10;
    auto mapped = TinyFp::Either<int, FakeClass>::left(left);
    try
    {
        auto test1 = mapped.unwrap();
        BOOST_CHECK(test1.value == 10);
    }
    catch(...)
    {
        BOOST_CHECK(true == true);
    }
}
```

### match

```c++
template <class Q> Q match(Func<R, Q> right, Func<Q, L> left);
```
Access to the wrapped status using **right** and **left** callback to map the internal status.


```c++
BOOST_AUTO_TEST_CASE(Either_WhenLeft_AndMatch_ReturnLeft)
{
    auto onRight = [](long value)
    {
        char retVal = 'a';
        return retVal;
    };
    auto onLeft = [](int value)
    {
        char retVal = 'b';
        return retVal;
    };

    int leftValue = 10;
    auto inner = TinyFp::Either<int, long>::left(leftValue)
                    .match<char>(
                        onRight,
                        onLeft);
    BOOST_CHECK(inner == 'b');
}

BOOST_AUTO_TEST_CASE(Either_WhenRight_AndMatch_ReturnRight)
{
    auto onRight = [](long value)
    {
        char retVal = 'a';
        return retVal;
    };
    auto onLeft = [](int value)
    {
        char retVal = 'b';
        return retVal;
    };

    long rightValue = 10;
    auto inner = TinyFp::Either<int, long>::right(rightValue)
                    .match<char>(
                        onRight,
                        onLeft);
    BOOST_CHECK(inner == 'a');
}
```
