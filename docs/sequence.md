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

Find the first item of the sequence satysfying the predicate paramater function.

The predicate parameter should return true for at least one item in the collection.


```c++
BOOST_AUTO_TEST_CASE(Sequence_firstOf_WhenMatch_ReturnItem)
{
    vector<FakeClass> items = 
    { 
        FakeClass(1), 
        FakeClass(2), 
        FakeClass(3)
    };
    auto sequence = Sequence<FakeClass>::from(items);
    auto selector = [](const FakeClass& value)
    {
        return value.value == 2;
    };
    auto item = sequence.firstOf(selector);
    BOOST_CHECK(item.value == 2);
}
```

### firstOfOrDefault

```c++
T firstOfOrDefault(Predicate<T> of, const T& def);
```

Find the first item of the sequence satysfying the predicate paramater function.

If no tiem was found the def default value will be returned.

The predicate parameter should return true for at least one item in the collection.


```c++
BOOST_AUTO_TEST_CASE(Sequence_firstOfOrDefault_WhenNoMatch_ReturnDefault)
{
    vector<FakeClass> items = 
    { 
        FakeClass(1), 
        FakeClass(2), 
        FakeClass(3)
    };
    auto sequence = Sequence<FakeClass>::from(items);
    auto selector = [](const FakeClass& value)
    {
        return value.value == 4;
    };
    auto def = FakeClass(42);
    auto item = sequence.firstOfOrDefault(selector, def);
    BOOST_CHECK(item.value == 42);
}
```

### fold

```c++
template<class R> R fold(const R& state, function<R(const R&, const T&)> step);
```

This method allows you to **aggregat e(reduce)**  the sequence into one value.

The iteration start from the initial **state** and go through all items in the sequence calling the callback with two parameters: the current aggregate state and the item.

The aggregate callback should return the new aggregated *state** for the next item.


```c++
BOOST_AUTO_TEST_CASE(Sequence_fold_ReturnAggregate)
{
    vector<FakeClass> items = 
    { 
        FakeClass(1), 
        FakeClass(2), 
        FakeClass(3)
    };
    auto step = [](const int& acc, const FakeClass& item)
    {
        return acc + item.value;
    };
    auto sequence = Sequence<FakeClass>::from(items);
    int state = 0;
    auto aggregation = sequence.fold<int>(state, step);
    BOOST_CHECK(aggregation == 6);
}
```

### filter

```c++
Sequence<T> filter(Predicate<T> item);
```

This method allows you to **filter** the sequence into a new sequence containing only the items satisyong the item predicate.


```c++
BOOST_AUTO_TEST_CASE(Sequence_filter_ReturnFiltered)
{
    vector<FakeClass> items = 
    { 
        FakeClass(1), 
        FakeClass(2), 
        FakeClass(3)
    };
    auto filterItem = [](const FakeClass& item)
    {
        return item.value != 2;
    };
    auto sequence = Sequence<FakeClass>::from(items);
    auto filtered = sequence.filter(filterItem);
    auto item = items.at(1);
    auto itemFiltered = filtered.at(1);
    BOOST_CHECK(item.value == 2);
    BOOST_CHECK(itemFiltered.value == 3);
    BOOST_CHECK(filtered.size() == 2);
}
```

### map

```c++
template<class R> Sequence<R> map(Func<R, T> item);
```

This method allows you to **map (convert)** all the sequence items into a new sequence. 

The **item** callback will be called to initialize every new item in the new sequence starting fro previous one.


```c++
BOOST_AUTO_TEST_CASE(Sequence_map_ReturnMapped)
{
    vector<FakeClass> items = 
    { 
        FakeClass(1), 
        FakeClass(2), 
        FakeClass(3)
    };
    auto mapItem = [](const FakeClass& item)
    {
        return FakeClass(item.value *2);
    };
    auto sequence = Sequence<FakeClass>::from(items);
    auto mapped = sequence.map<FakeClass>(mapItem);
    auto item = items.at(1);
    auto itemMapped = mapped.at(1);
    BOOST_CHECK(item.value == 2);
    BOOST_CHECK(itemMapped.value == 4);
    BOOST_CHECK(mapped.size() == 3);
}
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

