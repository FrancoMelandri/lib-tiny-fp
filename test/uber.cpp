
#include <boost/test/unit_test.hpp>
#include "Fakes.h"
#include "prelude.h"
#include "try/Try.h"
#include "option/Option.h"
using namespace TinyFp;
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( test_suite_uber )

BOOST_AUTO_TEST_CASE(ROP_Failure)
{
    auto retVal = FakeClass(42);
    auto onHandle = [retVal]()
    {
        return (FakeClass*)&retVal;
    };

    auto _TrySuccess = [](FakeClass& value)
    {
        return (FakeClass*)&value;
    };

    auto _TryFailure = [](exception& ex)
    {
        return (FakeClass*)NULL;
    };

    auto whenNone = [](FakeClass& vlaue)
    {
        return vlaue.value == 44;
    };

    auto sut = makeOption<FakeClass>(
                        TinyFp::
                            Try<FakeClass>::
                            Handle(onHandle)
                            .Match(_TrySuccess),
                        whenNone);
    BOOST_CHECK(sut.IsSome() == true);
}

BOOST_AUTO_TEST_SUITE_END()
