# lib-tiny-fp

## abstract

The aim of `lib-tiny-fp` library is to implement the basic functional data types allows you to use **Railway Oriented Programming** in native way.

example:
```c++

    auto sut = makeOption<FakeClass>(
            TinyFp::Try<FakeClass>::Handle(onHandle)
                    .Match(_TrySuccess),
            _WhenNone)
        .ToEither<Error>(_LeftValue)
        .Map<FakeClassMapped>(_MapEither)
        .Match<int>(_OnRight,
                    _OnLeft);

```

## install