#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Option
#include <boost/test/included/unit_test.hpp>
#include "Option.h"

using namespace TinyFp;
using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(WhenNoneIsSomeIsFalse)
{
    auto option = TinyFp::Option<int>::None();
    BOOST_CHECK(option.IsSome() == false);
}

BOOST_AUTO_TEST_CASE(WhenSomeWithNullIsSomeIsFalse)
{
    auto option = TinyFp::Option<int>::Some(NULL);
    BOOST_CHECK(option.IsSome() == false);
}

BOOST_AUTO_TEST_CASE(WhenSomeIsSomeIsTrue)
{
    int test = 10;
    auto option = TinyFp::Option<int>::Some(&test);
    BOOST_CHECK(option.IsSome() == true);
}

BOOST_AUTO_TEST_CASE(WhenNoneAndMapSomeIsFalse)
{
    auto mapped = TinyFp::Option<int>::None()
                    .Map<int>([](int* value) { return value; } );
    BOOST_CHECK(mapped.IsSome() == false);
}

BOOST_AUTO_TEST_CASE(WhenSomeAndMapSomeIsTrue)
{
    int test = 10;
    auto mapped = TinyFp::Option<int>::Some(&test)
                    .Map<int>([](int* value) { return value; } );
    BOOST_CHECK(mapped.IsSome() == true);
}
