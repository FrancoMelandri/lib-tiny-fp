
#include <boost/test/unit_test.hpp>
#include "Fakes.h"
#include "prelude.h"
#include "either/Either.h"
using namespace TinyFp;
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( test_suite_either )

BOOST_AUTO_TEST_CASE(Either_WhenLeft_IsLeftIsTrue)
{
    auto onLeft = [](long value)
    {
        int retVal = 42;
        return retVal;
    };

    int leftValue = 10;
    auto either = TinyFp::Either<int, long>::left(leftValue);
    auto inner = either.right(onLeft);

    BOOST_CHECK(either.isLeft() == true);
    BOOST_CHECK(either.isRight() == false);
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
    auto either = TinyFp::Either<int, long>::right(rightValue);
    auto inner = either.right(onLeft);

    BOOST_CHECK(either.isRight() == true);
    BOOST_CHECK(either.isLeft() == false);
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
    auto either = TinyFp::Either<int, long>::right(rightValue)
                    .map<char>(onMap);

    auto inner = either.right(onLeft);
    BOOST_CHECK(either.isRight() == true);
    BOOST_CHECK(either.isLeft() == false);
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
    auto either = TinyFp::Either<int, long>::left(leftValue)
                    .map<char>(onMap);

    auto inner = either.right(onLeft);
    BOOST_CHECK(either.isRight() == false);
    BOOST_CHECK(either.isLeft() == true);
    BOOST_CHECK(inner == 'b');
}

BOOST_AUTO_TEST_CASE(Either_WhenRight_AndBind_ReturnBinded)
{
    auto onBind = [](long value)
    {
        char retVal = 'a';
        return Either<int, char>::right(retVal);
    };
    auto onLeft = [](int value)
    {
        char retVal = 'b';
        return retVal;
    };

    long rightValue = 10;
    auto either = TinyFp::Either<int, long>::right(rightValue)
                    .bind<char>(onBind);

    auto inner = either.right(onLeft);
    BOOST_CHECK(either.isRight() == true);
    BOOST_CHECK(either.isLeft() == false);
    BOOST_CHECK(inner == 'a');
}

BOOST_AUTO_TEST_CASE(Either_WhenLeft_AndBind_ReturnLEft)
{
    auto onBind = [](long value)
    {
        char retVal = 'a';
        return Either<int, char>::right(retVal);
    };
    auto onLeft = [](int value)
    {
        char retVal = 'b';
        return retVal;
    };

    int leftValue = 10;
    auto either = TinyFp::Either<int, long>::left(leftValue)
                    .bind<char>(onBind);

    auto inner = either.right(onLeft);
    BOOST_CHECK(either.isRight() == false);
    BOOST_CHECK(either.isLeft() == true);
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
    auto inner = TinyFp::Either<int, long>::left(leftValue)
                    .match<char>(
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
    auto inner = TinyFp::Either<int, long>::right(rightValue)
                    .match<char>(
                        onRight,
                        onLeft);
    BOOST_CHECK(inner == 'a');
}

BOOST_AUTO_TEST_CASE(Either_GuardMap_WhenNone_IsLeft)
{
    auto defaultMap = [](const FakeClass& value)
    {
        return FakeClassMapped(value.value*20);
    };
    auto onLeft = [](const int& value)
    {
        return 100;
    };

    auto funcSelector1 = [](const FakeClass& value)
    {
        return true;
    };
    auto funcMap1 = [](const FakeClass& value)
    {
        return FakeClassMapped(99);
    };
    tuple<function<bool(const FakeClass&)>, function<FakeClassMapped(const FakeClass&)>> tuple1 = { funcSelector1, funcMap1 };
    vector<tuple<function<bool(const FakeClass&)>, function<FakeClassMapped(const FakeClass&)>>> guards =
    {
        tuple1
    };
    int leftValue = 10;
    auto mapped = TinyFp::Either<int, FakeClass>::left(leftValue)
                    .guardMap<FakeClassMapped>(
                        defaultMap,
                        guards);
    auto test1 = mapped.right(onLeft);
    BOOST_CHECK(mapped.isLeft() == true);
    BOOST_CHECK(test1.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(Either_GuardMap_WhenSome_NoSelector_DefaultMap)
{
    auto defaultMap = [](const FakeClass& value)
    {
        return FakeClassMapped(value.value*20);
    };
    auto onLeft = [](const int& value)
    {
        return 100;
    };

    auto funcSelector1 = [](const FakeClass& value)
    {
        return false;
    };
    auto funcMap1 = [](const FakeClass& value)
    {
        return FakeClassMapped(99);
    };
    tuple<function<bool(const FakeClass&)>, function<FakeClassMapped(const FakeClass&)>> tuple1 = { funcSelector1, funcMap1 };
    vector<tuple<function<bool(const FakeClass&)>, function<FakeClassMapped(const FakeClass&)>>> guards =
    {
        tuple1
    };
    auto rightValue = FakeClass(10);
    auto mapped = TinyFp::Either<int, FakeClass>::right(rightValue)
                    .guardMap<FakeClassMapped>(
                        defaultMap,
                        guards);
    auto test1 = mapped.right(onLeft);
    BOOST_CHECK(mapped.isRight() == true);
    BOOST_CHECK(test1.mappedValue == 200);
}

BOOST_AUTO_TEST_CASE(Either_GuardMap_WhenSome_OneSelector_Select)
{
    auto defaultMap = [](const FakeClass& value)
    {
        return FakeClassMapped(value.value*20);
    };
    auto onLeft = [](const int& value)
    {
        return 100;
    };

    auto funcSelector1 = [](const FakeClass& value)
    {
        return true;
    };
    auto funcMap1 = [](const FakeClass& value)
    {
        return FakeClassMapped(99);
    };
    tuple<function<bool(const FakeClass&)>, function<FakeClassMapped(const FakeClass&)>> tuple1 = { funcSelector1, funcMap1 };
    vector<tuple<function<bool(const FakeClass&)>, function<FakeClassMapped(const FakeClass&)>>> guards =
    {
        tuple1
    };
    auto rightValue = FakeClass(10);
    auto mapped = TinyFp::Either<int, FakeClass>::right(rightValue)
                    .guardMap<FakeClassMapped>(
                        defaultMap,
                        guards);
    auto test1 = mapped.right(onLeft);
    BOOST_CHECK(mapped.isRight() == true);
    BOOST_CHECK(test1.mappedValue == 99);
}

BOOST_AUTO_TEST_CASE(Either_GuardMap_WhenSome_TwoSelector_Select)
{
    auto defaultMap = [](const FakeClass& value)
    {
        return FakeClassMapped(value.value*20);
    };
    auto onLeft = [](const int& value)
    {
        return 100;
    };

    auto funcSelector1 = [](const FakeClass& value)
    {
        return false;
    };
    auto funcMap1 = [](const FakeClass& value)
    {
        return FakeClassMapped(99);
    };
    auto funcSelector2 = [](const FakeClass& value)
    {
        return true;
    };
    auto funcMap2 = [](const FakeClass& value)
    {
        return FakeClassMapped(101);
    };
    tuple<function<bool(const FakeClass&)>, function<FakeClassMapped(const FakeClass&)>> tuple1 = { funcSelector1, funcMap1 };
    tuple<function<bool(const FakeClass&)>, function<FakeClassMapped(const FakeClass&)>> tuple2 = { funcSelector2, funcMap2 };
    vector<tuple<function<bool(const FakeClass&)>, function<FakeClassMapped(const FakeClass&)>>> guards =
    {
        tuple1,
        tuple2
    };
    auto rightValue = FakeClass(10);
    auto mapped = TinyFp::Either<int, FakeClass>::right(rightValue)
                    .guardMap<FakeClassMapped>(
                        defaultMap,
                        guards);
    auto test1 = mapped.right(onLeft);
    BOOST_CHECK(mapped.isRight() == true);
    BOOST_CHECK(test1.mappedValue == 101);
}

BOOST_AUTO_TEST_CASE(Either_GuardBind_WhenNone_IsLeft)
{
    auto defaultBind = [](const FakeClass& value)
    {
          auto retVal = FakeClassMapped(value.value*20);
          return Either<int, FakeClassMapped>::right(retVal);
    };
    auto onLeft = [](const int& value)
    {
        return 100;
    };

    auto funcSelector1 = [](const FakeClass& value)
    {
        return true;
    };
    auto funcMap1 = [](const FakeClass& value)
    {
          auto retVal = FakeClassMapped(99);
          return Either<int, FakeClassMapped>::right(retVal);
    };
    tuple<function<bool(const FakeClass&)>, function<Either<int, FakeClassMapped>(const FakeClass&)>> tuple1 = { funcSelector1, funcMap1 };
    vector<tuple<function<bool(const FakeClass&)>, function<Either<int, FakeClassMapped>(const FakeClass&)>>> guards =
    {
        tuple1
    };
    int leftValue = 10;
    auto mapped = TinyFp::Either<int, FakeClass>::left(leftValue)
                    .guardBind<FakeClassMapped>(
                        defaultBind,
                        guards);
    auto test1 = mapped.right(onLeft);
    BOOST_CHECK(mapped.isLeft() == true);
    BOOST_CHECK(test1.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(Either_GuardBind_WhenSome_NoSelector_DefaultBind)
{
     auto test = FakeClass(10);
    auto defaultBind = [](const FakeClass& value)
    {
          auto retVal = FakeClassMapped(value.value*20);
          return Either<int, FakeClassMapped>::right(retVal);
    };
    auto onLeft = [](const int& value)
    {
        return 100;
    };

    auto funcSelector1 = [](const FakeClass& value)
    {
        return false;
    };
    auto funcMap1 = [](const FakeClass& value)
    {
          auto retVal = FakeClassMapped(99);
          return Either<int, FakeClassMapped>::right(retVal);
    };
    tuple<function<bool(const FakeClass&)>, function<Either<int, FakeClassMapped>(const FakeClass&)>> tuple1 = { funcSelector1, funcMap1 };
    vector<tuple<function<bool(const FakeClass&)>, function<Either<int, FakeClassMapped>(const FakeClass&)>>> guards =
    {
        tuple1
    };
    auto mapped = TinyFp::Either<int, FakeClass>::right(test)
                    .guardBind<FakeClassMapped>(
                        defaultBind,
                        guards);
    auto test1 = mapped.right(onLeft);
    BOOST_CHECK(mapped.isRight() == true);
    BOOST_CHECK(test1.mappedValue == 200);
}

BOOST_AUTO_TEST_CASE(Either_GuardBind_WhenSome_AndSelector_Select)
{
     auto test = FakeClass(10);
    auto defaultBind = [](const FakeClass& value)
    {
          auto retVal = FakeClassMapped(value.value*20);
          return Either<int, FakeClassMapped>::right(retVal);
    };
    auto onLeft = [](const int& value)
    {
        return 100;
    };

    auto funcSelector1 = [](const FakeClass& value)
    {
        return true;
    };
    auto funcMap1 = [](const FakeClass& value)
    {
          auto retVal = FakeClassMapped(99);
          return Either<int, FakeClassMapped>::right(retVal);
    };
    tuple<function<bool(const FakeClass&)>, function<Either<int, FakeClassMapped>(const FakeClass&)>> tuple1 = { funcSelector1, funcMap1 };
    vector<tuple<function<bool(const FakeClass&)>, function<Either<int, FakeClassMapped>(const FakeClass&)>>> guards =
    {
        tuple1
    };
    auto mapped = TinyFp::Either<int, FakeClass>::right(test)
                    .guardBind<FakeClassMapped>(
                        defaultBind,
                        guards);
    auto test1 = mapped.right(onLeft);
    BOOST_CHECK(mapped.isRight() == true);
    BOOST_CHECK(test1.mappedValue == 99);
}

BOOST_AUTO_TEST_SUITE_END()
