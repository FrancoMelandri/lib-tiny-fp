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
