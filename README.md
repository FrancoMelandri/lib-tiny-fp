# lib-tiny-fp

C++ Functional programming library.

## abstract

The aim of `lib-tiny-fp` library is to implement the basic functional data types allows you to use **Railway Oriented Programming** in native way.

Example:
```c++

    auto sut = makeOption<FakeClass>(
            TinyFp::Try<FakeClass>::handle(onHandle)
                    .match(_TrySuccess),
            _WhenNone)
        .toEither<Error>(_LeftValue)
        .map<FakeClassMapped>(_MapEither)
        .match<int>(_OnRight,
                    _OnLeft);

```

## install

To install the latest versionlibrary you can use directly the source code files.
clone the repository:

```bash
> git clone https://github.com/francomelandri/lib-tiny-fp

> cd lib-tiny-fp
> make install

```

The libray will be installed into `/usr/local/lib/libtinyfp` and `/usr/local/include/libtinyfp` folders.

To build your own code you should include these path in the Kakefile

```makefile
CFLAGS = -O1 -Wall -I/usr/local/inlcude/libtinyfp 
CCX = g++

LIBTINYFP = /usr/local/lib/libtinyfp/libtinyfp.a
APPNAME = test

all: $(APPNAME)

DEMOFILES = test.o

$(APPNAME): $(DEMOFILES)
	$(CCX) $(DEMOFILES)  $(LIBTINYFP) -o $(APPNAME)

%.o: %.cpp
	$(CCX) $(CFLAGS) -c $<

clean:
	rm -f $(APPNAME) $(DEMOFILES)

rebuild: clean all
```