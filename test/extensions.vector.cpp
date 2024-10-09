
#include <boost/test/unit_test.hpp>
#include "Fakes.h"
#include "prelude.h"
#include "extensions/vector.h"

using namespace TinyFp::Extensions;
using namespace boost::unit_test;
using namespace std;

BOOST_AUTO_TEST_SUITE( test_suite_extensions_vecotr )

BOOST_AUTO_TEST_CASE(firstOf_WhenMatch_ReturnItem)
{
    vector<FakeClass> items = 
    { 
        FakeClass(1), 
        FakeClass(2), 
        FakeClass(3)
    };
    auto selector = [](FakeClass& value)->bool
    {
        return value.value == 2;
    };
    auto item = firstOf<FakeClass>(items, selector);
    BOOST_CHECK(item.value == 2);
}

BOOST_AUTO_TEST_CASE(firstOf_WhenNoMatch_ReturnUndefined)
{
    vector<FakeClass> items = 
    { 
        FakeClass(1), 
        FakeClass(2), 
        FakeClass(3)
    };
    auto selector = [](FakeClass& value)->bool
    {
        return value.value == 4;
    };
    auto item = firstOf<FakeClass>(items, selector);
    BOOST_CHECK( item.value == 0 );
}

BOOST_AUTO_TEST_CASE(firstOfOrDefault_WhenMatch_ReturnItem)
{
    vector<FakeClass> items = 
    { 
        FakeClass(1), 
        FakeClass(2), 
        FakeClass(3)
    };
    auto selector = [](FakeClass& value)->bool
    {
        return value.value == 2;
    };
    auto def = FakeClass(42);
    auto item = firstOfOrDefault<FakeClass>(items, selector, def);
    BOOST_CHECK(item.value == 2);
}

BOOST_AUTO_TEST_CASE(firstOfOrDefault_WhenNoMatch_ReturnDefault)
{
    vector<FakeClass> items = 
    { 
        FakeClass(1), 
        FakeClass(2), 
        FakeClass(3)
    };
    auto selector = [](FakeClass& value)->bool
    {
        return value.value == 4;
    };
    auto def = FakeClass(42);
    auto item = firstOfOrDefault<FakeClass>(items, selector, def);
    BOOST_CHECK( item.value == 42 );
}

BOOST_AUTO_TEST_SUITE_END()
