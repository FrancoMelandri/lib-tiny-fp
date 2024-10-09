
#include <boost/test/unit_test.hpp>
#include "Fakes.h"
#include "prelude.h"
#include "option/Option.h"

using namespace TinyFp;
using namespace boost::unit_test;
using namespace std;

BOOST_AUTO_TEST_SUITE( test_suite_prelude )

BOOST_AUTO_TEST_CASE(MakeOption_WhenNull_ReturnNone)
{
    auto option = makeOption<FakeClass>(NULL);
    BOOST_CHECK(option.IsSome() == false);
}

BOOST_AUTO_TEST_CASE(MakeOption_WhenNotNull_ButWhenNone_ReturnNone)
{
    FakeClass test = FakeClass(42);
    auto whenNone = [](const FakeClass& vlaue)
    {
        return vlaue.value == 42;
    };
    auto option = makeOption<FakeClass>(&test, whenNone);
    BOOST_CHECK(option.IsSome() == false);
}

BOOST_AUTO_TEST_CASE(MakeOption_WhenNotNull_AndNottWhenNone_ReturnSome)
{
    FakeClass test = FakeClass(42);
    auto whenNone = [](const FakeClass& vlaue)
    {
        return vlaue.value == 666;
    };
    auto option = makeOption<FakeClass>(&test, whenNone);
    BOOST_CHECK(option.IsSome() == true);
}

BOOST_AUTO_TEST_SUITE_END()
