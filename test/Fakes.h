#ifndef LIB_TINY_FP_TEST_FAKES
#define LIB_TINY_FP_TEST_FAKES

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

#endif
