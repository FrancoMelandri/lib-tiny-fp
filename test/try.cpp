
#include <boost/test/unit_test.hpp>
#include "Fakes.h"
#include "prelude.h"
#include "try/Try.h"
using namespace TinyFp;
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( test_suite_try )

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

    auto onFail = [](const exception& ex)
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

    auto onFail = [](const exception& ex)
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

BOOST_AUTO_TEST_SUITE_END()
