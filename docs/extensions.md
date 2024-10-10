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

### While

```c++
template <class S>
S While(function<S()> init, function<bool(const S&)> enabled, function<S(const S&)> body)
```

Functional `While` whit initial state, exit condition and body function.

Due the fact it is functional, the **return** value is the state update by the body funciton after initializazion.
