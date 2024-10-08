
#include <boost/test/unit_test.hpp>
#include "Fakes.h"
#include "prelude.h"
#include "try/Try.h"
#include "option/Option.h"
using namespace TinyFp;
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( test_suite_uber )

// Option<FakeClass> _TrySuccess(int& value)
// {
//     auto val = FakeClass(value);
//     auto retVal = Option<FakeClass>::Some(val);
//     return retVal;
// }

// Option<FakeClass> _TryFailure(exception& ex)
// {
//     auto retVal = Option<FakeClass>::None();
//     return retVal;
// }

BOOST_AUTO_TEST_CASE(ROP_Failure)
{
    auto onHandle = []()
    {
        auto retVal = FakeClass(42);
        return retVal;
    };

    auto _TrySuccess = [](FakeClass& value)
    {
        auto retVal = FakeClass(value);
        return retVal;
    };

    auto _TryFailure = [](exception& ex)
    {
        auto retVal = FakeClass(666);
        return retVal;
    };

    auto inner = TinyFp::Try<FakeClass>::Handle(onHandle)
                    .Match(
                        _TrySuccess,
                        _TryFailure);
                    // .OrElse<FakeClass>([](){ return FakeClass(666); });
    BOOST_CHECK(inner.value == 42);
}

BOOST_AUTO_TEST_SUITE_END()
