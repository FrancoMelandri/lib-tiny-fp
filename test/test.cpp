#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Option
#include <boost/test/included/unit_test.hpp>
#include "Option.h"

using namespace TinyFp;
using namespace boost::unit_test;

class FakeClass
{    
public:
    FakeClass(int val) { value = val; };
    int value;
};

class FakeClassMapped
{    
public:
    FakeClassMapped(int val) { mappedValue = val; };
    int mappedValue;
};

BOOST_AUTO_TEST_CASE(WhenNoneIsSomeIsFalse)
{
    auto option = TinyFp::Option<int>::None();
    BOOST_CHECK(option.IsSome() == false);
}

BOOST_AUTO_TEST_CASE(WhenSomeWithNullIsSomeIsFalse)
{
    auto option = TinyFp::Option<int>::Some(NULL);
    BOOST_CHECK(option.IsSome() == false);
}

BOOST_AUTO_TEST_CASE(WhenSomeIsSomeIsTrue)
{
    int test = 10;
    auto option = TinyFp::Option<int>::Some(&test);
    BOOST_CHECK(option.IsSome() == true);
}

BOOST_AUTO_TEST_CASE(WhenNoneAndMapSomeIsFalse)
{
    auto mapped = TinyFp::Option<int>::None()
                    .Map<int>([](int* value) { return value; } );
    BOOST_CHECK(mapped.IsSome() == false);
}

BOOST_AUTO_TEST_CASE(WhenSomeAndMapSomeIsTrue)
{
    int test = 10;
    auto mapped = TinyFp::Option<int>::Some(&test)
                    .Map<int>([](int* value) { return value; } );
    BOOST_CHECK(mapped.IsSome() == true);
}

BOOST_AUTO_TEST_CASE(WhenSomeAndMapSomeIsTrueReference)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::Some(&test)
                    .Map<FakeClassMapped>([](FakeClass* value) { return new FakeClassMapped(value->value*20); } );
    auto test1 = mapped.OrElse<FakeClassMapped>([test]() { return FakeClassMapped(100); });
    BOOST_CHECK(mapped.IsSome() == true);
    BOOST_CHECK(test1.mappedValue == 200);
}

BOOST_AUTO_TEST_CASE(WhenNoneAndMapSomeIsFalseReference)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::None()
                    .Map<FakeClassMapped>([](FakeClass* value) { return new FakeClassMapped(value->value*20); } );
    auto test1 = mapped.OrElse<FakeClassMapped>([test]() { return FakeClassMapped(100); });
    BOOST_CHECK(mapped.IsSome() == false);
    BOOST_CHECK(test1.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(WhenSomeAndOrElseReturnValue)
{
    int test = 10;
    auto mapped = TinyFp::Option<int>::Some(&test);
    auto test1 = mapped.OrElse<int>([test]() { return test; });
    BOOST_CHECK(mapped.IsSome() == true);
    BOOST_CHECK(test == 10);
    BOOST_CHECK(test1 == 10);
}

BOOST_AUTO_TEST_CASE(WhenNoneAndOrElseReturnDefault)
{
    int test = 10;
    auto mapped = TinyFp::Option<int>::None();
    auto test1 = mapped.OrElse<int>([test]() { return test*10; });
    BOOST_CHECK(mapped.IsSome() == false);
    BOOST_CHECK(test == 10);
    BOOST_CHECK(test1 == 100);
}

BOOST_AUTO_TEST_CASE(WhenSomeAndOrElseReturnValueReference)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::Some(&test);
    auto test1 = mapped.OrElse<FakeClass>([]() { return FakeClass(100); });
    BOOST_CHECK(mapped.IsSome() == true);
    BOOST_CHECK(test.value == 10);
    BOOST_CHECK(test1.value == 10);
}

BOOST_AUTO_TEST_CASE(WhenNoneAndOrElseReturnDefaultReference)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::None();
    auto test1 = mapped.OrElse<FakeClass>([]() { return FakeClass(100); });
    BOOST_CHECK(mapped.IsSome() == false);
    BOOST_CHECK(test.value == 10);
    BOOST_CHECK(test1.value == 100);
}
