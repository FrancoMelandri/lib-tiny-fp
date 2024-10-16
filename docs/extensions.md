# Extensions

## vector

### firstOf

```c++
template <class A>
A firstOf(const vector<A>& items, function<bool(const A&)> of);

```

find the first item satisfy the predicate of().


### firstOfOrDefault

```c++
template <class A>
A firstOfOrDefault(const vector<A>& items, function<bool(const A&)>of, const A& def);
```

find the first item satisfy the predicate of(); if no match return the default value.

## flow

### loop

```c++
template <class S>
S loop(Nullary<S> init, function<bool(const S&)> enabled, function<S(const S&)> body)
```

`loop` is a functional `while` whit initial state, exit condition and body function.

Due the fact it is functional, the **return** value is the state update by the body funciton after initializazion.

example:

```c++
BOOST_AUTO_TEST_CASE(while_should_works_fine)
{
    auto loop = loop<int>(
        []() { return 0; },                             // init
        [](const int& state) { return state < 10; },    // enabled
        [](const int& state) { return state + 1; }      // body
    );
    BOOST_CHECK(loop == 10);
}
```

### which

```c++
template <class S>
S which(Nullary<bool> condition, Nullary<S> onTrue, Nullary<S> onFalse);

template <class S, class T>
S which(const T& input,
        function<bool(const T&)> condition,
        function<S(const T&)> onTrue,
        function<S(const T&)> onFalse);

```

`which` is a functional `if`; it will call the onTrue callback when the condition result is true.
Otherwise the onFalse callback will be called.

Due the fact it is functional, the **return** value is returned in both onTrue and onFalse high order functions.

example:

```c++
BOOST_AUTO_TEST_CASE(which_Input_WhenFalse_onFalse)
{
    int value = 10;
    auto retVal = which<int, int>(value,
        [](const int& val) { return val == 1; },    // condition
        [](const int& val) { return 1; },           // onTrue
        [](const int& val) { return 10; }           // onFalse
    );
    BOOST_CHECK(retVal == 10);
}

BOOST_AUTO_TEST_CASE(which_Input_WhenTrue_onTrue)
{
    int value = 1;
    auto retVal = which<int, int>(value,
        [](const int& val) { return val == 1; },    // condition
        [](const int& val) { return 1; },           // onTrue
        [](const int& val) { return 10; }           // onFalse
    );
    BOOST_CHECK(retVal == 1);
}
```

### guard

```c++
template <class S>
S guard(
    function<S()> onDefault,
    const vector<tuple<function<bool()>, function<S()>>>& guards);

template <class S, class T>
S guard(
    const T& value,
    function<S(const T&)> onDefault,
    const vector<tuple<function<bool(const T&)>, function<S(const T&)>>>& guards);
```

`guard` is a functional `switch`; it will call the right callback when the related condition (a predicate selector) is verified.
If not match was found the default callback will be called.

Due the fact it is functional, the **return** value is returned i all function at the right of the selector in the tuple.

example:

```c++
BOOST_AUTO_TEST_CASE(Guard_WhenMatch_Matched)
{
   auto onDefault = [](const int& value)
    {
        return 999;
    };
    auto funcSelector1 = [](const int& value)
    {
        return false;
    };
    auto funcMap1 = [](const int& value)
    {
        return 666;
    };
    auto funcSelector2 = [](const int& value)
    {
        return value == 1;
    };
    auto funcMap2 = [](const int& value)
    {
        return 42;
    };
    tuple<function<bool(const int&)>, function<int(const int&)>> tuple1 = { funcSelector1, funcMap1 };
    tuple<function<bool(const int&)>, function<int(const int&)>> tuple2 = { funcSelector2, funcMap2 };
    vector<tuple<function<bool(const int&)>, function<int(const int&)>>> guards =
    {
        tuple1,
        tuple2
    };

    int value = 1;
    auto retVal = guard<int, int>(value,
        onDefault,
        guards
    );
    BOOST_CHECK(retVal == 42);
}
```
