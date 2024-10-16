# Types

to let the code be more readable we introduce a bunch of custom types definition act as aliases for more convolute type we use.


**Predicate**

```c++
template<class A>
using Predicate = std::function<bool(const A&)>;
```

This **type** define a function that reutn a boolena using the template type as input parameter.

**Func**

```c++
template<class B, class A>
using Func = std::function<B(const A&)>;
```

**Guard**

```c++
template<class B, class A>
using Guard = std::tuple<Predicate<A>, Func<B, A>>;
```

**GuardVector**

```c++
template<class B, class A>
using GuardVector = std::vector<Guard<B, A>>;
```

**Guards**

```c++
template<class B, class A>
using Guards = TinyFp::Sequence<Guard<B, A>>;
```
