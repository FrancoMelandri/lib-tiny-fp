
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

BOOST_AUTO_TEST_SUITE_END()
