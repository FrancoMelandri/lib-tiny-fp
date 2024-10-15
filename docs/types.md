# Types

to let the code be more readable we introduce a bunch of custom types definition act as aliases for more convolute type we use.


**FuncSelector**

```c++
template<class A>
using FuncSelector = std::function<bool(const A&)>;
```

**FuncValue**

```c++
template<class B, class A>
using FuncValue = std::function<B(const A&)>;
```

**Guard**

```c++
template<class B, class A>
using Guard = std::tuple<FuncSelector<A>, FuncValue<B, A>>;
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
