
#include <boost/test/unit_test.hpp>
#include "Fakes.h"
#include "prelude.h"
#include "extensions/extensions.h"

using namespace TinyFp::Extensions;
using namespace boost::unit_test;
using namespace std;

BOOST_AUTO_TEST_SUITE( test_suite_extensions_flow )

BOOST_AUTO_TEST_CASE(while_should_works_fine_with_init)
{
    auto retVal = loop<int>(
        []() { return 0; },
        [](const int& state){return false;},
        [](const int& state){return 0;}
    );
    BOOST_CHECK(retVal == 0);
}

BOOST_AUTO_TEST_CASE(while_should_works_fine)
{
    auto retVal = loop<int>(
        []() { return 0; },
        [](const int& state) { return state < 10; },
        [](const int& state) { return state + 1; }
    );
    BOOST_CHECK(retVal == 10);
}

BOOST_AUTO_TEST_CASE(which_WhenFalse_onFalse)
{
    auto retVal = which<int>(
        []() { return false; },
        []() { return 1; },
        []() { return 10; }
    );
    BOOST_CHECK(retVal == 10);
}

BOOST_AUTO_TEST_CASE(which_WhenTrue_onTrue)
{
    auto retVal = which<int>(
        []() { return true; },
        []() { return 1; },
        []() { return 10; }
    );
    BOOST_CHECK(retVal == 1);
}

BOOST_AUTO_TEST_CASE(which_Input_WhenFalse_onFalse)
{
    int value = 10;
    auto retVal = which<int, int>(value,
        [](const int& val) { return val == 1; },
        [](const int& val) { return 1; },
        [](const int& val) { return 10; }
    );
    BOOST_CHECK(retVal == 10);
}

BOOST_AUTO_TEST_CASE(which_Input_WhenTrue_onTrue)
{
    int value = 1;
    auto retVal = which<int, int>(value,
        [](const int& val) { return val == 1; },
        [](const int& val) { return 1; },
        [](const int& val) { return 10; }
    );
    BOOST_CHECK(retVal == 1);
}

BOOST_AUTO_TEST_CASE(Guard_WhenNoMatch_Default)
{
   auto onDefault = [](const int& value)
    {
        return 999;
    };
    auto funcSelector1 = [](const int& value)
    {
        return false;
    };
    auto funcMap1 = [](const int& value)
    {
        return 666;
    };
    auto funcSelector2 = [](const int& value)
    {
        return false;
    };
    auto funcMap2 = [](const FakeClass& value)
    {
        return 42;
    };
    tuple<function<bool(const int&)>, function<int(const int&)>> tuple1 = { funcSelector1, funcMap1 };
    tuple<function<bool(const int&)>, function<int(const int&)>> tuple2 = { funcSelector2, funcMap2 };
    vector<tuple<function<bool(const int&)>, function<int(const int&)>>> guards =
    {
        tuple1,
        tuple2
    };

    int value = 1;
    auto retVal = guard<int, int>(value,
        onDefault,
        guards
    );
    BOOST_CHECK(retVal == 999);
}

BOOST_AUTO_TEST_CASE(Guard_WhenMatch_Matched)
{
   auto onDefault = [](const int& value)
    {
        return 999;
    };
    auto funcSelector1 = [](const int& value)
    {
        return false;
    };
    auto funcMap1 = [](const int& value)
    {
        return 666;
    };
    auto funcSelector2 = [](const int& value)
    {
        return value == 1;
    };
    auto funcMap2 = [](const int& value)
    {
        return 42;
    };
    tuple<function<bool(const int&)>, function<int(const int&)>> tuple1 = { funcSelector1, funcMap1 };
    tuple<function<bool(const int&)>, function<int(const int&)>> tuple2 = { funcSelector2, funcMap2 };
    vector<tuple<function<bool(const int&)>, function<int(const int&)>>> guards =
    {
        tuple1,
        tuple2
    };

    int value = 1;
    auto retVal = guard<int, int>(value,
        onDefault,
        guards
    );
    BOOST_CHECK(retVal == 42);
}

BOOST_AUTO_TEST_CASE(Guard_NoInput_WhenMatch_Matched)
{
   auto onDefault = []()
    {
        return 999;
    };
    auto funcSelector1 = []()
    {
        return false;
    };
    auto funcMap1 = []()
    {
        return 666;
    };
    auto funcSelector2 = []()
    {
        return true;
    };
    auto funcMap2 = []()
    {
        return 42;
    };
    tuple<function<bool()>, function<int()>> tuple1 = { funcSelector1, funcMap1 };
    tuple<function<bool()>, function<int()>> tuple2 = { funcSelector2, funcMap2 };
    vector<tuple<function<bool()>, function<int()>>> guards =
    {
        tuple1,
        tuple2
    };

    auto retVal = guard<int>(
        onDefault,
        guards);
    BOOST_CHECK(retVal == 42);
}

BOOST_AUTO_TEST_SUITE_END()
