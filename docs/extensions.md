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
S loop(function<S()> init, function<bool(const S&)> enabled, function<S(const S&)> body)
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
S which(function<bool()> condition, function<S()> onTrue, function<S()> onFalse);

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
