# Sequence

## factories

### from

```c++
static Sequence from(const std::vector<T>& vector);
static Sequence from(const std::list<T>& list);
```

## functional

### firstOf

```c++
T firstOf(Predicate<T> of);
```

### firstOfOrDefault

```c++
T firstOfOrDefault(Predicate<T> of, const T& def);
```

### fold

```c++
template<class R> R fold(const R& state, function<R(const R&, const T&)> step);
```

### map

```c++
template<class R> Sequence<R> map(Func<R, T> item);
Sequence<T> filter(Predicate<T> item);
```

## accessing

### at

```c++
T at(int n);
```

### size

```c++
int size();
```

### iterator

```c++
iterator begin();
const_iterator begin();
const_iterator cbegin();
iterator end();
const_iterator end() const;
const_iterator cend() const;
```

