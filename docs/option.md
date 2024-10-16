# Option

## factories

## none

```c++
static Option<T> none();
```

creating none `Option`; an empty option.


## some

```c++
static Option<T> some(const T& value);
```

creating some `Option`; a fullfilled option.


## toEither

```c++
template <class L> Either<L, T> toEither(Nullary<L> leftValue);
```

convert an `Option` into an `Either`.

The right value will be the some value; in case of none the **leftValue** callback will be called to initialize the left status Either.

## composition

## map

```c++
template <class R> Option<R> map(Unary<T, R> map);
```

Map the `Option` using a function as parameter. the uplift to `Option` is done by the map itself.

The paramater function will be called only for fullfilled option, otherwise a none option is returned.

```c++
BOOST_AUTO_TEST_CASE(Option_Map_WhenSome_isSomeIsTrue)
{
    auto test = FakeClass(10);
    auto mapped = makeOption(&test)
                    .map<FakeClassMapped>(
                        [](const FakeClass& value)
                            { 
                                return FakeClassMapped(value.value*20);
                            });
    auto test1 = mapped.orElse<FakeClassMapped>([test]() { return FakeClassMapped(100);});
    BOOST_CHECK(mapped.isSome() == true);
    BOOST_CHECK(test1.mappedValue == 200);
}
```

## guardMap

```c++
template <class R> Option<R> guardMap(Unary<T, R> defaultMap, const Guards<T, R>& guards);
```

**Map** the `Option` using a list of `Guard`, or the **defaultMap** if no match was found.

## bind

```c++
template <class R> Option<R> bind(Unary<T, Option<R>> bind);
```

**Bind** the `Option` using a function as parameter. The difference between map is that you have to define the uplift to option must be in the function inject as parameter.

The paramater function will be called only for some option state, otherwise a none option is returned.

## guardBind

```c++
template <class R> Option<R> guardBind(Unary<T, Option<R>> defaultBind, const Guards<T, Option<R>>& guards);
```

**Bind** the `Option` using a list of `Guard`, or the **defaulBind** if no match was found.

## accessing

## isSome

```c++
bool isSome();
```

**true** in case the `Option` is in the some state, otherwise **false**.

## orElse

```c++
template <class R> R orElse(Nullary<R> none);
```

Get the some value of the `Option`.

In case the `Option`is in none state the parameter function should provde a default some value.

## unwrap

```c++
T Option<T>::unwrap();
```

Get the some value of the `Option`.

In case the `Option`is in none state an exception will be thrown.


```c++
BOOST_AUTO_TEST_CASE(Option_unwrap_whenSome_returnstate)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::some(test);
    auto test1 = mapped.unwrap();
    BOOST_CHECK(test1.value == 10);
}

BOOST_AUTO_TEST_CASE(Option_unwrap_whenone_exception)
{
    auto mapped = TinyFp::Option<FakeClass>::none();
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

## match

```c++
template <class R> R match(Unary<T, R> some, Nullary<R> none);
```

Access to the wrapped status using **some** and **none** callback to map the internal status.

```c++
BOOST_AUTO_TEST_CASE(Option_Match_WhenNone_ReturnNone)
{
    auto mapped = TinyFp::Option<FakeClass>::none()
                    .match<FakeClassMapped>(
                        [](const FakeClass& value) { return FakeClassMapped(value.value*20);},
                        []() { return FakeClassMapped(100);});
    BOOST_CHECK(mapped.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(Option_Match_WhenSome_ReturnSome)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::some(test)
                    .match<FakeClassMapped>(
                        [](const FakeClass& value) { return FakeClassMapped(value.value*20);},
                        []() { return FakeClassMapped(100);});
    BOOST_CHECK(mapped.mappedValue == 200);
}
```
