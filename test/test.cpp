#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Option
#include <boost/test/included/unit_test.hpp>
#include "Fakes.h"
#include "prelude.h"
#include "option/Option.h"
#include "either/Either.h"
#include "try/Try.h"

using namespace TinyFp;
using namespace boost::unit_test;

using namespace std;
using std::cout;
using std::endl;

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
    auto mapped = createOption(&test);
    auto test1 = mapped.OrElse<int>([test]() { return test; });
    BOOST_CHECK(mapped.IsSome() == true);
    BOOST_CHECK(test == 10);
    BOOST_CHECK(test1 == 10);
}

BOOST_AUTO_TEST_CASE(WhenNoneAndOrElseReturnDefault)
{
    int test = 10;
    auto mapped = createOption((int*)NULL);
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
    FakeClass* test = NULL;
    auto mapped = createOption(test);
    auto test1 = mapped.OrElse<FakeClass>([]() { return FakeClass(100); });
    BOOST_CHECK(mapped.IsSome() == false);
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
    auto mapped = createOption(&test)
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

BOOST_AUTO_TEST_CASE(OptionRef_Bind_WhenNone_ReturnDefault)
{
    auto onBind = [](FakeClass& value)
    {
        auto fake = FakeClassMapped(value.value*20);
        return TinyFp::Option<FakeClassMapped>::Some(fake);
    };
    auto onDefault = []()
    {
        return FakeClassMapped(100);
    };
    auto test1 = TinyFp::Option<FakeClass>::None()
                    .Bind<FakeClassMapped>(onBind)
                    .OrElse<FakeClassMapped>(onDefault);
    BOOST_CHECK(test1.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(OptionRef_Bind_WhenSome_ReturnBinded)
{
    auto onBind = [](FakeClass& value)
    {
        auto fake = FakeClassMapped(value.value*20);
        return TinyFp::Option<FakeClassMapped>::Some(fake);
    };
    auto onDefault = []()
    {
        return FakeClassMapped(100);
    };
    auto fake = FakeClass(10);
    auto test1 = TinyFp::Option<FakeClass>::Some(fake)
                    .Bind<FakeClassMapped>(onBind)
                    .OrElse<FakeClassMapped>(onDefault);
    BOOST_CHECK(test1.mappedValue == 200);
}

BOOST_AUTO_TEST_CASE(OptionRef_Bind_Map_WhenSome_ReturnBinded)
{
    auto onBind = [](FakeClass& value)
    {
        auto fake = FakeClassMapped(value.value*20);
        return TinyFp::Option<FakeClassMapped>::Some(fake);
    };
    auto onMap = [](FakeClass& value)
    {
        return FakeClass(value.value*2);
    };
    auto onDefault = []()
    {
        return FakeClassMapped(100);
    };
    auto fake = FakeClass(10);
    auto test1 = TinyFp::Option<FakeClass>::Some(fake)
                    .Map<FakeClass>(onMap)
                    .Bind<FakeClassMapped>(onBind)
                    .OrElse<FakeClassMapped>(onDefault);
    BOOST_CHECK(test1.mappedValue == 400);
}

BOOST_AUTO_TEST_CASE(Either_WhenLeft_IsLeftIsTrue)
{
    auto onLeft = [](long value)
    {
        int retVal = 42;
        return retVal;
    };

    int leftValue = 10;
    auto either = TinyFp::Either<int, long>::Left(leftValue);
    auto inner = either.Right(onLeft);

    BOOST_CHECK(either.IsLeft() == true);
    BOOST_CHECK(either.IsRight() == false);
    BOOST_CHECK(inner == 42);
}

BOOST_AUTO_TEST_CASE(Either_WhenRight_IsRightIsTrue)
{
     auto onLeft = [](long value)
    {
        int retVal = 42;
        return retVal;
    };

    long rightValue = 10;
    auto either = TinyFp::Either<int, long>::Right(rightValue);
    auto inner = either.Right(onLeft);

    BOOST_CHECK(either.IsRight() == true);
    BOOST_CHECK(either.IsLeft() == false);
    BOOST_CHECK(inner == 10);
}

BOOST_AUTO_TEST_CASE(Either_WhenRight_AndMap_ReturnMapped)
{
    auto onMap = [](long value)
    {
        char retVal = 'a';
        return retVal;
    };
    auto onLeft = [](int value)
    {
        int retVal = 42;
        return retVal;
    };

    long rightValue = 10;
    auto either = TinyFp::Either<int, long>::Right(rightValue)
                    .Map<char>(onMap);

    auto inner = either.Right(onLeft);
    BOOST_CHECK(either.IsRight() == true);
    BOOST_CHECK(either.IsLeft() == false);
    BOOST_CHECK(inner == 'a');
}

BOOST_AUTO_TEST_CASE(Either_WhenLeft_AndMap_ReturnLeft)
{
    auto onMap = [](long value)
    {
        char retVal = 'a';
        return retVal;
    };
    auto onLeft = [](int value)
    {
        char retVal = 'b';
        return retVal;
    };

    int leftValue = 10;
    auto either = TinyFp::Either<int, long>::Left(leftValue)
                    .Map<char>(onMap);

    auto inner = either.Right(onLeft);
    BOOST_CHECK(either.IsRight() == false);
    BOOST_CHECK(either.IsLeft() == true);
    BOOST_CHECK(inner == 'b');
}

BOOST_AUTO_TEST_CASE(Either_WhenRight_AndBind_ReturnBinded)
{
    auto onBind = [](long value)
    {
        char retVal = 'a';
        return Either<int, char>::Right(retVal);
    };
    auto onLeft = [](int value)
    {
        char retVal = 'b';
        return retVal;
    };

    long rightValue = 10;
    auto either = TinyFp::Either<int, long>::Right(rightValue)
                    .Bind<char>(onBind);

    auto inner = either.Right(onLeft);
    BOOST_CHECK(either.IsRight() == true);
    BOOST_CHECK(either.IsLeft() == false);
    BOOST_CHECK(inner == 'a');
}

BOOST_AUTO_TEST_CASE(Either_WhenLeft_AndBind_ReturnLEft)
{
    auto onBind = [](long value)
    {
        char retVal = 'a';
        return Either<int, char>::Right(retVal);
    };
    auto onLeft = [](int value)
    {
        char retVal = 'b';
        return retVal;
    };

    int leftValue = 10;
    auto either = TinyFp::Either<int, long>::Left(leftValue)
                    .Bind<char>(onBind);

    auto inner = either.Right(onLeft);
    BOOST_CHECK(either.IsRight() == false);
    BOOST_CHECK(either.IsLeft() == true);
    BOOST_CHECK(inner == 'b');
}

BOOST_AUTO_TEST_CASE(Either_WhenLeft_AndMatch_ReturnLeft)
{
    auto onRight = [](long value)
    {
        char retVal = 'a';
        return retVal;
    };
    auto onLeft = [](int value)
    {
        char retVal = 'b';
        return retVal;
    };

    int leftValue = 10;
    auto inner = TinyFp::Either<int, long>::Left(leftValue)
                    .Match<char>(
                        onRight,
                        onLeft);
    BOOST_CHECK(inner == 'b');
}

BOOST_AUTO_TEST_CASE(Either_WhenRight_AndMatch_ReturnRight)
{
    auto onRight = [](long value)
    {
        char retVal = 'a';
        return retVal;
    };
    auto onLeft = [](int value)
    {
        char retVal = 'b';
        return retVal;
    };

    long rightValue = 10;
    auto inner = TinyFp::Either<int, long>::Right(rightValue)
                    .Match<char>(
                        onRight,
                        onLeft);
    BOOST_CHECK(inner == 'a');
}

BOOST_AUTO_TEST_CASE(Try_WhenSuccess_ReturnSuccess)
{
    auto onHandle = []()->int
    {
        return 100;
    };

    auto onSuccess = [](int value)
    {
        return value;
    };

    auto onFail = [](exception& ex)
    {
        int retVal = 42;
        return retVal;
    };

    auto inner = TinyFp::Try<int>::Handle(onHandle)
                    .Match(
                        onSuccess,
                        onFail);
    BOOST_CHECK(inner == 100);
}

BOOST_AUTO_TEST_CASE(Try_WhenException_ReturnFail)
{
    auto onHandle = []()->int
    {
        throw 42;
    };

    auto onSuccess = [](int value)
    {
        return value;
    };

    auto onFail = [](exception& ex)
    {
        int retVal = 42;
        return retVal;
    };

    auto inner = TinyFp::Try<int>::Handle(onHandle)
                    .Match(
                        onSuccess,
                        onFail);
    BOOST_CHECK(inner == 42);
}
