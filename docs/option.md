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
template <class L> Either<L, T> toEither(function<L()> leftValue);
```

convert an `Option` into an `Either`.

The right value will be the some value; in case of none the **leftValue** callback will be called to initialize the left status Either.

## composition

## map

```c++
template <class R> Option<R> map(Func<R, T> map);
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
template <class R> Option<R> guardMap(Func<R, T> defaultMap, const Guards<R, T>& guards);
```

**Map** the `Option` using a list of `Guard`, or the **defaultMap** if no match was found.

## bind

```c++
template <class R> Option<R> bind(Func<Option<R>, T> bind);
```

**Bind** the `Option` using a function as parameter. The difference between map is that you have to define the uplift to option must be in the function inject as parameter.

The paramater function will be called only for some option state, otherwise a none option is returned.

## guardBind

```c++
template <class R> Option<R> guardBind(Func<Option<R>, T> defaultBind, const Guards<Option<R>, T>& guards);
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
template <class R> R orElse(function<R()> none);
```

Get the some value of the `Option`.

In case the `Option`is in none state the parameter function should provde a default some value.

## match

```c++
template <class R> R match(Func<R, T> some, function<R()> none);
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
