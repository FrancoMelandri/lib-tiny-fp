
#include <boost/test/unit_test.hpp>
#include "Fakes.h"
#include "prelude.h"
#include "option/Option.h"

using namespace TinyFp;
using namespace boost::unit_test;
using namespace std;

BOOST_AUTO_TEST_SUITE( test_suite_option )

BOOST_AUTO_TEST_CASE(Option_IsSome_WhenNone_IsFalse)
{
    auto option = TinyFp::Option<int>::None();
    BOOST_CHECK(option.IsSome() == false);
}

BOOST_AUTO_TEST_CASE(Option_IsSome_WhenSomeIsTrue)
{
    int test = 10;
    auto option = TinyFp::Option<int>::Some(test);
    BOOST_CHECK(option.IsSome() == true);
}

BOOST_AUTO_TEST_CASE(Option_OrElse_WhenSomeReturnValue)
{
    int test = 10;
    auto mapped = makeOption(&test);
    auto test1 = mapped.OrElse<int>([test]() { return test;});
    BOOST_CHECK(mapped.IsSome() == true);
    BOOST_CHECK(test == 10);
    BOOST_CHECK(test1 == 10);
}

BOOST_AUTO_TEST_CASE(Option_OrElse_WhenNoneReturnDefault)
{
    int test = 10;
    auto mapped = makeOption((int*)NULL);
    auto test1 = mapped.OrElse<int>([test]() { return test*10;});
    BOOST_CHECK(mapped.IsSome() == false);
    BOOST_CHECK(test == 10);
    BOOST_CHECK(test1 == 100);
}

BOOST_AUTO_TEST_CASE(Option_OrElse_WhenSomeReturnValue_Reference)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::Some(test);
    auto test1 = mapped.OrElse<FakeClass>([]() { return FakeClass(100);});
    BOOST_CHECK(mapped.IsSome() == true);
    BOOST_CHECK(test.value == 10);
    BOOST_CHECK(test1.value == 10);
}

BOOST_AUTO_TEST_CASE(Option_OrElse_WhenNoneReturnDefault_Reference_)
{
    FakeClass* test = NULL;
    auto mapped = makeOption(test);
    auto test1 = mapped.OrElse<FakeClass>([]() { return FakeClass(100);});
    BOOST_CHECK(mapped.IsSome() == false);
    BOOST_CHECK(test1.value == 100);
}

BOOST_AUTO_TEST_CASE(Option_OrElse_WhenNoneReturnDefault_Reference)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::None();
    auto test1 = mapped.OrElse<FakeClass>([]() { return FakeClass(100);});
    BOOST_CHECK(mapped.IsSome() == false);
    BOOST_CHECK(test.value == 10);
    BOOST_CHECK(test1.value == 100);
}

BOOST_AUTO_TEST_CASE(Option_Map_WhenNone_IsSomeIsFalse_Reference)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::None()
                    .Map<FakeClassMapped>([](FakeClass& value) { return FakeClassMapped(value.value*20);} );
    auto test1 = mapped.OrElse<FakeClassMapped>([test]() { return FakeClassMapped(100);});
    BOOST_CHECK(mapped.IsSome() == false);
    BOOST_CHECK(test1.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(Option_Map_WhenSome_IsSomeIsTrue_Reference)
{
    auto test = FakeClass(10);
    auto mapped = makeOption(&test)
                    .Map<FakeClassMapped>([](FakeClass& value) { return FakeClassMapped(value.value*20);} );
    auto test1 = mapped.OrElse<FakeClassMapped>([test]() { return FakeClassMapped(100);});
    BOOST_CHECK(mapped.IsSome() == true);
    BOOST_CHECK(test1.mappedValue == 200);
}

BOOST_AUTO_TEST_CASE(Option_Match_WhenNone_ReturnNone)
{
    auto mapped = TinyFp::Option<FakeClass>::None()
                    .Match<FakeClassMapped>(
                        [](FakeClass& value) { return FakeClassMapped(value.value*20);},
                        []() { return FakeClassMapped(100);});
    BOOST_CHECK(mapped.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(Option_Match_WhenSome_ReturnSome)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::Some(test)
                    .Match<FakeClassMapped>(
                        [](FakeClass& value) { return FakeClassMapped(value.value*20);},
                        []() { return FakeClassMapped(100);});
    BOOST_CHECK(mapped.mappedValue == 200);
}

BOOST_AUTO_TEST_CASE(Option_Match_WhenNone_ReturnNone_WithScalar)
{
    auto mapped = TinyFp::Option<FakeClass>::None()
                    .Match<int>(
                        [](FakeClass& value) { return value.value*20;},
                        []() { return 100;});
    BOOST_CHECK(mapped == 100);
}

BOOST_AUTO_TEST_CASE(Option_Match_WhenSome_ReturnSome_WithScalar)
{
    auto someFunc = [](FakeClass& value) { return value.value*20;};
    auto noneFunc = []() { return 100;};
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::Some(test)
                    .Match<int>(
                        someFunc,
                        noneFunc);
    BOOST_CHECK(mapped == 200);
}

BOOST_AUTO_TEST_CASE(Option_Bind_WhenNone_ReturnDefault)
{
    auto onBind = [](FakeClass& value)
    {
        auto fake = FakeClassMapped(value.value*20);
        return TinyFp::Option<FakeClassMapped>::Some(fake);
    };
    auto onDefault = []()
    {
        return FakeClassMapped(100);
    };
    auto test1 = TinyFp::Option<FakeClass>::None()
                    .Bind<FakeClassMapped>(onBind)
                    .OrElse<FakeClassMapped>(onDefault);
    BOOST_CHECK(test1.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(Option_Bind_WhenSome_ReturnBinded)
{
    auto onBind = [](FakeClass& value)
    {
        auto fake = FakeClassMapped(value.value*20);
        return TinyFp::Option<FakeClassMapped>::Some(fake);
    };
    auto onDefault = []()
    {
        return FakeClassMapped(100);
    };
    auto fake = FakeClass(10);
    auto test1 = TinyFp::Option<FakeClass>::Some(fake)
                    .Bind<FakeClassMapped>(onBind)
                    .OrElse<FakeClassMapped>(onDefault);
    BOOST_CHECK(test1.mappedValue == 200);
}

BOOST_AUTO_TEST_CASE(Option_Bind_Map_WhenSome_ReturnBinded)
{
    auto onBind = [](FakeClass& value)
    {
        auto fake = FakeClassMapped(value.value*20);
        return TinyFp::Option<FakeClassMapped>::Some(fake);
    };
    auto onMap = [](FakeClass& value)
    {
        return FakeClass(value.value*2);
    };
    auto onDefault = []()
    {
        return FakeClassMapped(100);
    };
    auto fake = FakeClass(10);
    auto test1 = TinyFp::Option<FakeClass>::Some(fake)
                    .Map<FakeClass>(onMap)
                    .Bind<FakeClassMapped>(onBind)
                    .OrElse<FakeClassMapped>(onDefault);
    BOOST_CHECK(test1.mappedValue == 400);
}

BOOST_AUTO_TEST_CASE(Option_GuardMap_WhenNone_IsSomeIsFalse)
{
    auto test = FakeClass(10);
    auto defaultMap = [](FakeClass& value)
    {
        return FakeClassMapped(value.value*20);
    };
    auto orElseDefault = [test]()
    {
        return FakeClassMapped(100);
    };

    auto funcSelector1 = [](FakeClass& value)
    {
        return true;
    };
    auto funcMap1 = [](FakeClass& value)
    {
        return FakeClassMapped(99);
    };
    tuple<function<bool(FakeClass&)>, function<FakeClassMapped(FakeClass&)>> tuple1 = { funcSelector1, funcMap1 };
    vector<tuple<function<bool(FakeClass&)>, function<FakeClassMapped(FakeClass&)>>> guards =
    {
        tuple1
    };
    auto mapped = TinyFp::Option<FakeClass>::None()
                    .GuardMap<FakeClassMapped>(
                        defaultMap,
                        guards);
    auto test1 = mapped.OrElse<FakeClassMapped>(orElseDefault);
    BOOST_CHECK(mapped.IsSome() == false);
    BOOST_CHECK(test1.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(Option_GuardMap_WhenSome_AndNoSelector_DefaultMap)
{
    auto test = FakeClass(10);
    auto defaultMap = [](FakeClass& value)
    {
        return FakeClassMapped(value.value*20);
    };
    auto orElseDefault = [test]()
    {
        return FakeClassMapped(100);
    };

    auto funcSelector1 = [](FakeClass& value)
    {
        return false;
    };
    auto funcMap1 = [](FakeClass& value)
    {
        return FakeClassMapped(99);
    };
    tuple<function<bool(FakeClass&)>, function<FakeClassMapped(FakeClass&)>> tuple1 = { funcSelector1, funcMap1 };
    vector<tuple<function<bool(FakeClass&)>, function<FakeClassMapped(FakeClass&)>>> guards =
    {
        tuple1
    };
    auto mapped = TinyFp::Option<FakeClass>::Some(test)
                    .GuardMap<FakeClassMapped>(
                        defaultMap,
                        guards);
    auto test1 = mapped.OrElse<FakeClassMapped>(orElseDefault);
    BOOST_CHECK(mapped.IsSome() == true);
    BOOST_CHECK(test1.mappedValue == 200);
}

BOOST_AUTO_TEST_CASE(Option_GuardMap_WhenSome_AndOneSelector_SelectorMap)
{
    auto test = FakeClass(10);
    auto defaultMap = [](FakeClass& value)
    {
        return FakeClassMapped(value.value*20);
    };
    auto orElseDefault = [test]()
    {
        return FakeClassMapped(100);
    };

    auto funcSelector1 = [](FakeClass& value)
    {
        return true;
    };
    auto funcMap1 = [](FakeClass& value)
    {
        return FakeClassMapped(99);
    };
    tuple<function<bool(FakeClass&)>, function<FakeClassMapped(FakeClass&)>> tuple1 = { funcSelector1, funcMap1 };
    vector<tuple<function<bool(FakeClass&)>, function<FakeClassMapped(FakeClass&)>>> guards =
    {
        tuple1
    };
    auto mapped = TinyFp::Option<FakeClass>::Some(test)
                    .GuardMap<FakeClassMapped>(
                        defaultMap,
                        guards);
    auto test1 = mapped.OrElse<FakeClassMapped>(orElseDefault);
    BOOST_CHECK(mapped.IsSome() == true);
    BOOST_CHECK(test1.mappedValue == 99);
}

BOOST_AUTO_TEST_CASE(Option_GuardMap_WhenSome_AndTwoSelector_SelectorMap)
{
    auto test = FakeClass(10);
    auto defaultMap = [](FakeClass& value)
    {
        return FakeClassMapped(value.value*20);
    };
    auto orElseDefault = [test]()
    {
        return FakeClassMapped(100);
    };

    auto funcSelector1 = [](FakeClass& value)
    {
        return false;
    };
    auto funcMap1 = [](FakeClass& value)
    {
        return FakeClassMapped(99);
    };
    auto funcSelector2 = [](FakeClass& value)
    {
        return true;
    };
    auto funcMap2 = [](FakeClass& value)
    {
        return FakeClassMapped(101);
    };
    tuple<function<bool(FakeClass&)>, function<FakeClassMapped(FakeClass&)>> tuple1 = { funcSelector1, funcMap1 };
    tuple<function<bool(FakeClass&)>, function<FakeClassMapped(FakeClass&)>> tuple2 = { funcSelector2, funcMap2 };
    vector<tuple<function<bool(FakeClass&)>, function<FakeClassMapped(FakeClass&)>>> guards =
    {
        tuple1,
        tuple2
    };
    auto mapped = TinyFp::Option<FakeClass>::Some(test)
                    .GuardMap<FakeClassMapped>(
                        defaultMap,
                        guards);
    auto test1 = mapped.OrElse<FakeClassMapped>(orElseDefault);
    BOOST_CHECK(mapped.IsSome() == true);
    BOOST_CHECK(test1.mappedValue == 101);
}

BOOST_AUTO_TEST_CASE(Option_GuardBind_WhenNone_IsSomeIsFalse)
{
    auto test = FakeClass(10);
    auto defaultMap = [](FakeClass& value)
    {
        auto retVal = FakeClassMapped(value.value*20);
        return Option<FakeClassMapped>::Some(retVal);
    };
    auto orElseDefault = [test]()
    {
        return FakeClassMapped(100);
    };

    auto funcSelector1 = [](FakeClass& value)
    {
        return true;
    };
    auto funcMap1 = [](FakeClass& value)
    {
        auto retVal = FakeClassMapped(99);
        return Option<FakeClassMapped>::Some(retVal);
    };
    tuple<function<bool(FakeClass&)>, function<Option<FakeClassMapped>(FakeClass&)>> tuple1 = { funcSelector1, funcMap1 };
    vector<tuple<function<bool(FakeClass&)>, function<Option<FakeClassMapped>(FakeClass&)>>> guards =
    {
        tuple1
    };
    auto mapped = TinyFp::Option<FakeClass>::None()
                    .GuardBind<FakeClassMapped>(
                        defaultMap,
                        guards);
    auto test1 = mapped.OrElse<FakeClassMapped>(orElseDefault);
    BOOST_CHECK(mapped.IsSome() == false);
    BOOST_CHECK(test1.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(Option_GuardBind_WhenSome_NoSelector_DefaultBind)
{
    auto test = FakeClass(10);
    auto defaultBind = [](FakeClass& value)
    {
        auto retVal = FakeClassMapped(value.value*20);
        return Option<FakeClassMapped>::Some(retVal);
    };
    auto orElseDefault = [test]()
    {
        return FakeClassMapped(100);
    };

    auto funcSelector1 = [](FakeClass& value)
    {
        return false;
    };
    auto funcMap1 = [](FakeClass& value)
    {
        auto retVal = FakeClassMapped(99);
        return Option<FakeClassMapped>::Some(retVal);
    };
    tuple<function<bool(FakeClass&)>, function<Option<FakeClassMapped>(FakeClass&)>> tuple1 = { funcSelector1, funcMap1 };
    vector<tuple<function<bool(FakeClass&)>, function<Option<FakeClassMapped>(FakeClass&)>>> guards =
    {
        tuple1
    };
    auto mapped = TinyFp::Option<FakeClass>::Some(test)
                    .GuardBind<FakeClassMapped>(
                        defaultBind,
                        guards);
    auto test1 = mapped.OrElse<FakeClassMapped>(orElseDefault);
    BOOST_CHECK(mapped.IsSome() == true);
    BOOST_CHECK(test1.mappedValue == 200);
}
BOOST_AUTO_TEST_CASE(Option_GuardBind_WhenSome_AndSelector_Select)
{
    auto test = FakeClass(10);
    auto defaultBind = [](FakeClass& value)
    {
        auto retVal = FakeClassMapped(value.value*20);
        return Option<FakeClassMapped>::Some(retVal);
    };
    auto orElseDefault = [test]()
    {
        return FakeClassMapped(100);
    };

    auto funcSelector1 = [](FakeClass& value)
    {
        return true;
    };
    auto funcMap1 = [](FakeClass& value)
    {
        auto retVal = FakeClassMapped(99);
        return Option<FakeClassMapped>::Some(retVal);
    };
    tuple<function<bool(FakeClass&)>, function<Option<FakeClassMapped>(FakeClass&)>> tuple1 = { funcSelector1, funcMap1 };
    vector<tuple<function<bool(FakeClass&)>, function<Option<FakeClassMapped>(FakeClass&)>>> guards =
    {
        tuple1
    };
    auto mapped = TinyFp::Option<FakeClass>::Some(test)
                    .GuardBind<FakeClassMapped>(
                        defaultBind,
                        guards);
    auto test1 = mapped.OrElse<FakeClassMapped>(orElseDefault);
    BOOST_CHECK(mapped.IsSome() == true);
    BOOST_CHECK(test1.mappedValue == 99);
}

BOOST_AUTO_TEST_SUITE_END()
