#ifndef LIB_TINY_FP_TEST_FAKES
#define LIB_TINY_FP_TEST_FAKES

#include "common.h"

class Error
{
public:
    Error() { code = 0; };
    Error(int val) { code = val; };
    int code;
};

class FakeClass
{    
public:
    FakeClass() { value = 0; };
    FakeClass(int val) { value = val; };
    int value;
};

class FakeClassMapped
{    
public:
    FakeClassMapped() { mappedValue = 0; };
    FakeClassMapped(int val) { mappedValue = val; };
    int mappedValue;
};

class FakeString
{    
public:
    FakeString() { value = ""; };
    FakeString(std::string val) { value = val; };
    std::string value;
};

class FakeContext
{
public:
    FakeContext() { context = 0; };
    FakeContext(int val) { context = val; };
    int context;
};

class FakeBuilderContext
{
private:
    FakeContext _first;
    FakeContext _second;
public:
    FakeBuilderContext() { };
    TinyFp::Unit setFirst(FakeContext& first)
    {
        _first = first;
        return TinyFp::Unit::Default();
    };
    TinyFp::Unit setSecond(const FakeContext& second)
    {
        _second = second;
        return TinyFp::Unit::Default();
    };
    FakeContext& getFirst()
    {
        return _first;
    };
    FakeContext& getSecond()
    {
        return _second;
    };
};

#endif
