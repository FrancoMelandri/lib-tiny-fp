
#include <boost/test/unit_test.hpp>
#include "Fakes.h"
#include "prelude.h"
#include "sequence/sequence.h"
using namespace TinyFp;
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( test_suite_sequence )

BOOST_AUTO_TEST_CASE(Sequence_firstOf_WhenMatch_ReturnItem)
{
    vector<FakeClass> items = 
    { 
        FakeClass(1), 
        FakeClass(2), 
        FakeClass(3)
    };
    auto sequence = Sequence<FakeClass>::from(items);
    auto selector = [](const FakeClass& value)->bool
    {
        return value.value == 2;
    };
    auto item = sequence.firstOf(selector);
    BOOST_CHECK(item.value == 2);
}

BOOST_AUTO_TEST_CASE(Sequence_firstOfOrDefault_WhenMatch_ReturnItem)
{
    vector<FakeClass> items = 
    { 
        FakeClass(1), 
        FakeClass(2), 
        FakeClass(3)
    };
    auto sequence = Sequence<FakeClass>::from(items);
    auto selector = [](const FakeClass& value)->bool
    {
        return value.value == 2;
    };
    auto def = FakeClass(42);
    auto item = sequence.firstOfOrDefault(selector, def);
    BOOST_CHECK(item.value == 2);
}

BOOST_AUTO_TEST_CASE(Sequence_firstOfOrDefault_WhenNoMatch_ReturnDefault)
{
    vector<FakeClass> items = 
    { 
        FakeClass(1), 
        FakeClass(2), 
        FakeClass(3)
    };
    auto sequence = Sequence<FakeClass>::from(items);
    auto selector = [](const FakeClass& value)->bool
    {
        return value.value == 4;
    };
    auto def = FakeClass(42);
    auto item = sequence.firstOfOrDefault(selector, def);
    BOOST_CHECK(item.value == 42);
}

BOOST_AUTO_TEST_CASE(Sequence_fold_ReturnAggregate)
{
    vector<FakeClass> items = 
    { 
        FakeClass(1), 
        FakeClass(2), 
        FakeClass(3)
    };
    auto step = [](const int& acc, const FakeClass& item)
    {
        return acc + item.value;
    };
    auto sequence = Sequence<FakeClass>::from(items);
    int state = 0;
    auto aggregation = sequence.fold<int>(state, step);
    BOOST_CHECK(aggregation == 6);
}

BOOST_AUTO_TEST_SUITE_END()
