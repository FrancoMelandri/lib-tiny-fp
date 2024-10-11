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
