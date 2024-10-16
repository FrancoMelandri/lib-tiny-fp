# Types

We've introduced a bunch of custom types to let the code be more readable.

Any definition act as aliases for more convolute type we use.


**Predicate**

```c++
template<class A>
using Predicate = std::function<bool(const A&)>;
```

This **type** define a function that reutn a boolena using the template type as input parameter.


**Nullary**

```c++
template<class A>
using Func = std::function<A()>;

```

**Func**

```c++
template<class A, class B>
using Func = std::function<B(const A&)>;
```

**Unary**

```c++
template<class A, class B>
using Func = std::function<B(const A&)>;
```

**Binary**

```c++
template<class A, class B, class C>
using Func = std::function<C(const A&, const B&)>;
```

**Guard**

```c++
template<class B, class A>
using Guard = std::tuple<Predicate<A>, Unary<B, A>>;
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
