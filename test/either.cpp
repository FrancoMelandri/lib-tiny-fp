
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

BOOST_AUTO_TEST_SUITE_END()
