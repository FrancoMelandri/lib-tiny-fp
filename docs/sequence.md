# Sequence

## factories

### from

```c++
static Sequence from(const std::vector<T>& vector);
static Sequence from(const std::list<T>& list);
```

## funcitonal

### firstOf

```c++
T firstOf(function<bool(const T&)> of);
```

### firstOfOrDefault

```c++
T firstOfOrDefault(function<bool(const T&)> of, const T& def);
```

### fold

```c++
template<class R> R fold(const R& state, function<R(const R&, const T&)> step);
```

### map

```c++
template<class R> Sequence<R> map(function<R(const T&)> item);
Sequence<T> filter(function<bool(const T&)> item);
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

