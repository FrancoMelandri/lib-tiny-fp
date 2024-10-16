
#include <boost/test/unit_test.hpp>
#include "Fakes.h"
#include "prelude.h"
#include "option/Option.h"

using namespace TinyFp;
using namespace boost::unit_test;
using namespace std;

BOOST_AUTO_TEST_SUITE( test_suite_option )

BOOST_AUTO_TEST_CASE(Option_isSome_WhenNone_IsFalse)
{
    auto option = TinyFp::Option<int>::none();
    BOOST_CHECK(option.isSome() == false);
}

BOOST_AUTO_TEST_CASE(Option_isSome_WhenSomeIsTrue)
{
    int test = 10;
    auto option = TinyFp::Option<int>::some(test);
    BOOST_CHECK(option.isSome() == true);
}

BOOST_AUTO_TEST_CASE(Option_orElse_WhenSomeReturnValue)
{
    int test = 10;
    auto mapped = makeOption(&test);
    auto test1 = mapped.orElse<int>([test]() { return test;});
    BOOST_CHECK(mapped.isSome() == true);
    BOOST_CHECK(test == 10);
    BOOST_CHECK(test1 == 10);
}

BOOST_AUTO_TEST_CASE(Option_orElse_WhenNoneReturnDefault)
{
    int test = 10;
    auto mapped = makeOption((int*)NULL);
    auto test1 = mapped.orElse<int>([test]() { return test*10;});
    BOOST_CHECK(mapped.isSome() == false);
    BOOST_CHECK(test == 10);
    BOOST_CHECK(test1 == 100);
}

BOOST_AUTO_TEST_CASE(Option_orElse_WhenSomeReturnValue_Reference)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::some(test);
    auto test1 = mapped.orElse<FakeClass>([]() { return FakeClass(100);});
    BOOST_CHECK(mapped.isSome() == true);
    BOOST_CHECK(test.value == 10);
    BOOST_CHECK(test1.value == 10);
}

BOOST_AUTO_TEST_CASE(Option_orElse_WhenNoneReturnDefault_Reference_)
{
    FakeClass* test = NULL;
    auto mapped = makeOption(test);
    auto test1 = mapped.orElse<FakeClass>([]() { return FakeClass(100);});
    BOOST_CHECK(mapped.isSome() == false);
    BOOST_CHECK(test1.value == 100);
}

BOOST_AUTO_TEST_CASE(Option_orElse_WhenNoneReturnDefault_Reference)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::none();
    auto test1 = mapped.orElse<FakeClass>([]() { return FakeClass(100);});
    BOOST_CHECK(mapped.isSome() == false);
    BOOST_CHECK(test.value == 10);
    BOOST_CHECK(test1.value == 100);
}

BOOST_AUTO_TEST_CASE(Option_unwrap_whenSome_returnstate)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::some(test);
    auto test1 = mapped.unwrap();
    BOOST_CHECK(test1.value == 10);
}

BOOST_AUTO_TEST_CASE(Option_unwrap_whenone_exception)
{
    auto mapped = TinyFp::Option<FakeClass>::none();
    try
    {
        auto test1 = mapped.unwrap();
        BOOST_CHECK(test1.value == 10);
    }
    catch(...)
    {
        BOOST_CHECK(true == true);
    }
}

BOOST_AUTO_TEST_CASE(Option_Map_WhenNone_isSomeIsFalse_Reference)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::none()
                    .map<FakeClassMapped>([](const FakeClass& value) { return FakeClassMapped(value.value*20);} );
    auto test1 = mapped.orElse<FakeClassMapped>([test]() { return FakeClassMapped(100);});
    BOOST_CHECK(mapped.isSome() == false);
    BOOST_CHECK(test1.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(Option_Map_WhenSome_isSomeIsTrue_Reference)
{
    auto test = FakeClass(10);
    auto mapped = makeOption(&test)
                    .map<FakeClassMapped>([](const FakeClass& value) { return FakeClassMapped(value.value*20);} );
    auto test1 = mapped.orElse<FakeClassMapped>([test]() { return FakeClassMapped(100);});
    BOOST_CHECK(mapped.isSome() == true);
    BOOST_CHECK(test1.mappedValue == 200);
}

BOOST_AUTO_TEST_CASE(Option_Match_WhenNone_ReturnNone)
{
    auto mapped = TinyFp::Option<FakeClass>::none()
                    .match<FakeClassMapped>(
                        [](const FakeClass& value) { return FakeClassMapped(value.value*20);},
                        []() { return FakeClassMapped(100);});
    BOOST_CHECK(mapped.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(Option_Match_WhenSome_ReturnSome)
{
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::some(test)
                    .match<FakeClassMapped>(
                        [](const FakeClass& value) { return FakeClassMapped(value.value*20);},
                        []() { return FakeClassMapped(100);});
    BOOST_CHECK(mapped.mappedValue == 200);
}

BOOST_AUTO_TEST_CASE(Option_Match_WhenNone_ReturnNone_WithScalar)
{
    auto mapped = TinyFp::Option<FakeClass>::none()
                    .match<int>(
                        [](const FakeClass& value) { return value.value*20;},
                        []() { return 100;});
    BOOST_CHECK(mapped == 100);
}

BOOST_AUTO_TEST_CASE(Option_Match_WhenSome_ReturnSome_WithScalar)
{
    auto someFunc = [](const FakeClass& value) { return value.value*20;};
    auto noneFunc = []() { return 100;};
    auto test = FakeClass(10);
    auto mapped = TinyFp::Option<FakeClass>::some(test)
                    .match<int>(
                        someFunc,
                        noneFunc);
    BOOST_CHECK(mapped == 200);
}

BOOST_AUTO_TEST_CASE(Option_Bind_WhenNone_ReturnDefault)
{
    auto onBind = [](const FakeClass& value)
    {
        auto fake = FakeClassMapped(value.value*20);
        return TinyFp::Option<FakeClassMapped>::some(fake);
    };
    auto onDefault = []()
    {
        return FakeClassMapped(100);
    };
    auto test1 = TinyFp::Option<FakeClass>::none()
                    .bind<FakeClassMapped>(onBind)
                    .orElse<FakeClassMapped>(onDefault);
    BOOST_CHECK(test1.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(Option_Bind_WhenSome_ReturnBinded)
{
    auto onBind = [](const FakeClass& value)
    {
        auto fake = FakeClassMapped(value.value*20);
        return TinyFp::Option<FakeClassMapped>::some(fake);
    };
    auto onDefault = []()
    {
        return FakeClassMapped(100);
    };
    auto fake = FakeClass(10);
    auto test1 = TinyFp::Option<FakeClass>::some(fake)
                    .bind<FakeClassMapped>(onBind)
                    .orElse<FakeClassMapped>(onDefault);
    BOOST_CHECK(test1.mappedValue == 200);
}

BOOST_AUTO_TEST_CASE(Option_Bind_Map_WhenSome_ReturnBinded)
{
    auto onBind = [](const FakeClass& value)
    {
        auto fake = FakeClassMapped(value.value*20);
        return TinyFp::Option<FakeClassMapped>::some(fake);
    };
    auto onMap = [](const FakeClass& value)
    {
        return FakeClass(value.value*2);
    };
    auto onDefault = []()
    {
        return FakeClassMapped(100);
    };
    auto fake = FakeClass(10);
    auto test1 = TinyFp::Option<FakeClass>::some(fake)
                    .map<FakeClass>(onMap)
                    .bind<FakeClassMapped>(onBind)
                    .orElse<FakeClassMapped>(onDefault);
    BOOST_CHECK(test1.mappedValue == 400);
}

BOOST_AUTO_TEST_CASE(Option_GuardMap_WhenNone_isSomeIsFalse)
{
    auto test = FakeClass(10);
    auto defaultMap = [](const FakeClass& value)
    {
        return FakeClassMapped(value.value*20);
    };
    auto orElseDefault = [test]()
    {
        return FakeClassMapped(100);
    };

    auto funcSelector1 = [](const FakeClass& value)
    {
        return true;
    };
    auto funcMap1 = [](const FakeClass& value)
    {
        return FakeClassMapped(99);
    };
    Guard<FakeClass,FakeClassMapped> tuple1 = { funcSelector1, funcMap1 };
    GuardVector<FakeClass, FakeClassMapped> guards =
    {
        tuple1
    };
    auto sequence = TinyFp::Types::Guards<FakeClass, FakeClassMapped>::from(guards);
    auto mapped = TinyFp::Option<FakeClass>::none()
                    .guardMap<FakeClassMapped>(
                        defaultMap,
                        sequence);
    auto test1 = mapped.orElse<FakeClassMapped>(orElseDefault);
    BOOST_CHECK(mapped.isSome() == false);
    BOOST_CHECK(test1.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(Option_GuardMap_WhenSome_AndNoSelector_DefaultMap)
{
    auto test = FakeClass(10);
    auto defaultMap = [](const FakeClass& value)
    {
        return FakeClassMapped(value.value*20);
    };
    auto orElseDefault = [test]()
    {
        return FakeClassMapped(100);
    };

    auto funcSelector1 = [](const FakeClass& value)
    {
        return false;
    };
    auto funcMap1 = [](const FakeClass& value)
    {
        return FakeClassMapped(99);
    };

    Guard<FakeClass, FakeClassMapped> tuple1 = { funcSelector1, funcMap1 };
    GuardVector<FakeClass, FakeClassMapped> guards =
    {
        tuple1
    };
    auto sequence = TinyFp::Types::Guards<FakeClass, FakeClassMapped>::from(guards);

    auto mapped = TinyFp::Option<FakeClass>::some(test)
                    .guardMap<FakeClassMapped>(
                        defaultMap,
                        sequence);
    auto test1 = mapped.orElse<FakeClassMapped>(orElseDefault);
    BOOST_CHECK(mapped.isSome() == true);
    BOOST_CHECK(test1.mappedValue == 200);
}

BOOST_AUTO_TEST_CASE(Option_GuardMap_WhenSome_AndOneSelector_SelectorMap)
{
    auto test = FakeClass(10);
    auto defaultMap = [](const FakeClass& value)
    {
        return FakeClassMapped(value.value*20);
    };
    auto orElseDefault = [test]()
    {
        return FakeClassMapped(100);
    };

    auto funcSelector1 = [](const FakeClass& value)
    {
        return true;
    };
    auto funcMap1 = [](const FakeClass& value)
    {
        return FakeClassMapped(99);
    };
    
    Guard<FakeClass, FakeClassMapped> tuple1 = { funcSelector1, funcMap1 };
    GuardVector<FakeClass, FakeClassMapped> guards =
    {
        tuple1
    };
    auto sequence = TinyFp::Types::Guards<FakeClass, FakeClassMapped>::from(guards);
    auto mapped = TinyFp::Option<FakeClass>::some(test)
                    .guardMap<FakeClassMapped>(
                        defaultMap,
                        sequence);
    auto test1 = mapped.orElse<FakeClassMapped>(orElseDefault);
    BOOST_CHECK(mapped.isSome() == true);
    BOOST_CHECK(test1.mappedValue == 99);
}

BOOST_AUTO_TEST_CASE(Option_GuardMap_WhenSome_AndTwoSelector_SelectorMap)
{
    auto test = FakeClass(10);
    auto defaultMap = [](const FakeClass& value)
    {
        return FakeClassMapped(value.value*20);
    };
    auto orElseDefault = [test]()
    {
        return FakeClassMapped(100);
    };

    auto funcSelector1 = [](const FakeClass& value)
    {
        return false;
    };
    auto funcMap1 = [](const FakeClass& value)
    {
        return FakeClassMapped(99);
    };
    auto funcSelector2 = [](const FakeClass& value)
    {
        return true;
    };
    auto funcMap2 = [](const FakeClass& value)
    {
        return FakeClassMapped(101);
    };

    Guard<FakeClass, FakeClassMapped> tuple1 = { funcSelector1, funcMap1 };
    Guard<FakeClass, FakeClassMapped> tuple2 = { funcSelector2, funcMap2 };
    GuardVector<FakeClass, FakeClassMapped> guards =
    {
        tuple1,
        tuple2
    };
    auto sequence = TinyFp::Types::Guards<FakeClass, FakeClassMapped>::from(guards);
    auto mapped = TinyFp::Option<FakeClass>::some(test)
                    .guardMap<FakeClassMapped>(
                        defaultMap,
                        sequence);
    auto test1 = mapped.orElse<FakeClassMapped>(orElseDefault);
    BOOST_CHECK(mapped.isSome() == true);
    BOOST_CHECK(test1.mappedValue == 101);
}

BOOST_AUTO_TEST_CASE(Option_GuardBind_WhenNone_isSomeIsFalse)
{
    auto test = FakeClass(10);
    auto defaultMap = [](const FakeClass& value)
    {
        auto retVal = FakeClassMapped(value.value*20);
        return Option<FakeClassMapped>::some(retVal);
    };
    auto orElseDefault = [test]()
    {
        return FakeClassMapped(100);
    };

    auto funcSelector1 = [](const FakeClass& value)
    {
        return true;
    };
    auto funcMap1 = [](const FakeClass& value)
    {
        auto retVal = FakeClassMapped(99);
        return Option<FakeClassMapped>::some(retVal);
    };
    
    Guard<FakeClass, Option<FakeClassMapped>> tuple1 = { funcSelector1, funcMap1 };
    GuardVector<FakeClass, Option<FakeClassMapped>> guards =
    {
        tuple1
    };
    auto sequence = TinyFp::Types::Guards<FakeClass, Option<FakeClassMapped>>::from(guards);

    auto mapped = TinyFp::Option<FakeClass>::none()
                    .guardBind<FakeClassMapped>(
                        defaultMap,
                        sequence);
    auto test1 = mapped.orElse<FakeClassMapped>(orElseDefault);
    BOOST_CHECK(mapped.isSome() == false);
    BOOST_CHECK(test1.mappedValue == 100);
}

BOOST_AUTO_TEST_CASE(Option_GuardBind_WhenSome_NoSelector_DefaultBind)
{
    auto test = FakeClass(10);
    auto defaultBind = [](const FakeClass& value)
    {
        auto retVal = FakeClassMapped(value.value*20);
        return Option<FakeClassMapped>::some(retVal);
    };
    auto orElseDefault = [test]()
    {
        return FakeClassMapped(100);
    };

    auto funcSelector1 = [](const FakeClass& value)
    {
        return false;
    };
    auto funcMap1 = [](const FakeClass& value)
    {
        auto retVal = FakeClassMapped(99);
        return Option<FakeClassMapped>::some(retVal);
    };

    Guard<FakeClass, Option<FakeClassMapped>> tuple1 = { funcSelector1, funcMap1 };
    GuardVector<FakeClass, Option<FakeClassMapped>> guards =
    {
        tuple1
    };
    auto sequence = TinyFp::Types::Guards<FakeClass, Option<FakeClassMapped>>::from(guards);
    auto mapped = TinyFp::Option<FakeClass>::some(test)
                    .guardBind<FakeClassMapped>(
                        defaultBind,
                        sequence);
    auto test1 = mapped.orElse<FakeClassMapped>(orElseDefault);
    BOOST_CHECK(mapped.isSome() == true);
    BOOST_CHECK(test1.mappedValue == 200);
}
BOOST_AUTO_TEST_CASE(Option_GuardBind_WhenSome_AndSelector_Select)
{
    auto test = FakeClass(10);
    auto defaultBind = [](const FakeClass& value)
    {
        auto retVal = FakeClassMapped(value.value*20);
        return Option<FakeClassMapped>::some(retVal);
    };
    auto orElseDefault = [test]()
    {
        return FakeClassMapped(100);
    };

    auto funcSelector1 = [](const FakeClass& value)
    {
        return true;
    };
    auto funcMap1 = [](const FakeClass& value)
    {
        auto retVal = FakeClassMapped(99);
        return Option<FakeClassMapped>::some(retVal);
    };

    Guard<FakeClass, Option<FakeClassMapped>> tuple1 = { funcSelector1, funcMap1 };
    GuardVector<FakeClass, Option<FakeClassMapped>> guards =
    {
        tuple1
    };
    auto sequence = TinyFp::Types::Guards<FakeClass, Option<FakeClassMapped>>::from(guards);
    auto mapped = TinyFp::Option<FakeClass>::some(test)
                    .guardBind<FakeClassMapped>(
                        defaultBind,
                        sequence);
    auto test1 = mapped.orElse<FakeClassMapped>(orElseDefault);
    BOOST_CHECK(mapped.isSome() == true);
    BOOST_CHECK(test1.mappedValue == 99);
}

BOOST_AUTO_TEST_SUITE_END()
