#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Option
#include <boost/test/included/unit_test.hpp>
#include "Option.h"

using namespace TinyFp;

BOOST_AUTO_TEST_CASE(WhenNoneIsSomeIsFalse)
{
    auto option = TinyFp::Option<int>::None();
    BOOST_CHECK(option->IsSome() == false);
    delete option;
}

BOOST_AUTO_TEST_CASE(WhenSomeWithNullIsSomeIsFalse)
{
    auto option = TinyFp::Option<int>::Some(NULL);
    BOOST_CHECK(option->IsSome() == false);
    delete option;
}

BOOST_AUTO_TEST_CASE(WhenSomeIsSomeIsTrue)
{
    int test = 10;
    auto option = TinyFp::Option<int>::Some(&test);
    BOOST_CHECK(option->IsSome() == true);
    delete option;
}