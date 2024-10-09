
#include <boost/test/unit_test.hpp>
#include "Fakes.h"
#include "prelude.h"
#include "try/Try.h"
#include "option/Option.h"
using namespace TinyFp;
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( test_suite_uber )

FakeClass* _TrySuccess(const FakeClass& value)
{
    return (FakeClass*)&value;
}

int _OnRight(const FakeClassMapped& mapped)
{
    return mapped.mappedValue;
}

int _OnLeft(const Error& error)
{
    return error.code;
}

bool _WhenNone(const FakeClass& vlaue)
{
    return vlaue.value == 44;
}

Error _LeftValue()
{
    auto left = Error(666);
    return left;
}

FakeClassMapped _MapEither(const FakeClass& vlaue)
{
    auto mapped = FakeClassMapped(vlaue.value * 2);
    return mapped;
}

BOOST_AUTO_TEST_CASE(ROP_Success)
{
    auto retVal = FakeClass(21);
    auto onHandle = [retVal]()
    {
        return (FakeClass*)&retVal;
    };

    auto sut = makeOption<FakeClass>(
                        TinyFp::Try<FakeClass>::Handle(onHandle)
                            .Match(_TrySuccess),
                        _WhenNone)
                .ToEither<Error>(_LeftValue)
                .map<FakeClassMapped>(_MapEither)
                .match<int>(
                    _OnRight,
                    _OnLeft);
    BOOST_CHECK(sut == 42);
}

BOOST_AUTO_TEST_CASE(ROP_Failure_Exception)
{
    auto onHandle = []() -> FakeClass*
    {
        throw 999;
    };

    auto sut = makeOption<FakeClass>(
                        TinyFp::Try<FakeClass>::Handle(onHandle)
                            .Match(_TrySuccess),
                        _WhenNone)
                .ToEither<Error>(_LeftValue)
                .map<FakeClassMapped>(_MapEither)
                .match<int>(
                    _OnRight,
                    _OnLeft);
    BOOST_CHECK(sut == 666);
}

BOOST_AUTO_TEST_CASE(ROP_Failure_WhenNone)
{
    auto retVal = FakeClass(44);
    auto onHandle = [retVal]()
    {
        return (FakeClass*)&retVal;
    };

    auto sut = makeOption<FakeClass>(
                        TinyFp::Try<FakeClass>::Handle(onHandle)
                            .Match(_TrySuccess),
                        _WhenNone)
                .ToEither<Error>(_LeftValue)
                .map<FakeClassMapped>(_MapEither)
                .match<int>(
                    _OnRight,
                    _OnLeft);
    BOOST_CHECK(sut == 666);
}

BOOST_AUTO_TEST_SUITE_END()
