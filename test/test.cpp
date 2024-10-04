#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Option
#include <boost/test/included/unit_test.hpp>
#include "option/Option.h"

using namespace TinyFp;
using namespace boost::unit_test;

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

BOOST_AUTO_TEST_CASE(WhenNoneIsSomeIsFalse)
{
    auto option = TinyFp::Option<int>::None();
    BOOST_CHECK(option.IsSome() == false);
}

BOOST_AUTO_TEST_CASE(WhenSomeIsSomeIsTrue)
{
    int test = 10;
    auto option = TinyFp::Option<int>::Some(test);
    BOOST_CHECK(option.IsSome() == true);
}

BOOST_AUTO_TEST_CASE(WhenSomeAndOrElseReturnValue)
{
    int test = 10;
    auto mapped = TinyFp::Option<int>::Some(test);
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
    auto mapped = TinyFp::Option<FakeClass>::Some(test);
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


BOOST_AUTO_TEST_CASE(OptionRef_WhenNoneAndOrElseReturnDefaultReference)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::None();
    auto test1 = mapped.OrElse<FakeClass>([]() { return FakeClass(100); });
    BOOST_CHECK(mapped.IsSome() == false);
    BOOST_CHECK(test.value == 10);
    BOOST_CHECK(test1.value == 100);
}

BOOST_AUTO_TEST_CASE(OptionRef_WhenNoneAndMapSomeIsFalseReference)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::None()
                    .Map<FakeClassMapped>([](FakeClass& value) { return FakeClassMapped(value.value*20); } );
    auto test1 = mapped.OrElse<FakeClassMapped>([test]() { return FakeClassMapped(100); });
    BOOST_CHECK(mapped.IsSome() == false);
    BOOST_CHECK(test1.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(OptionRef_WhenSomeAndMapSomeIsTrueReference)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::Some(test)
                    .Map<FakeClassMapped>([](FakeClass& value) { return FakeClassMapped(value.value*20); } );
    auto test1 = mapped.OrElse<FakeClassMapped>([test]() { return FakeClassMapped(100); });
    BOOST_CHECK(mapped.IsSome() == true);
    BOOST_CHECK(test1.mappedValue == 200);
}

BOOST_AUTO_TEST_CASE(OptionRef_WhenNoneAndMatch_ReturnNone)
{
    auto mapped = TinyFp::Option<FakeClass>::None()
                    .Match<FakeClassMapped>(
                        [](FakeClass& value) { return FakeClassMapped(value.value*20); },
                        []() { return FakeClassMapped(100); });
    BOOST_CHECK(mapped.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(OptionRef_WhenSomeAndMatch_ReturnSome)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::Some(test)
                    .Match<FakeClassMapped>(
                        [](FakeClass& value) { return FakeClassMapped(value.value*20); },
                        []() { return FakeClassMapped(100); });
    BOOST_CHECK(mapped.mappedValue == 200);
}

BOOST_AUTO_TEST_CASE(OptionRef_WhenNoneAndMatch_ReturnNone_WithScalar)
{
    auto mapped = TinyFp::Option<FakeClass>::None()
                    .Match<int>(
                        [](FakeClass& value) { return value.value*20; },
                        []() { return 100; });
    BOOST_CHECK(mapped == 100);
}

BOOST_AUTO_TEST_CASE(OptionRef_WhenSomeAndMatch_ReturnSome_WithScalar)
{
    auto someFunc = [](FakeClass& value) { return value.value*20; };
    auto noneFunc = []() { return 100; };
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::Some(test)
                    .Match<int>(
                        someFunc,
                        noneFunc);
    BOOST_CHECK(mapped == 200);
}
