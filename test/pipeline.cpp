
#include <boost/test/unit_test.hpp>
#include "Fakes.h"
#include "prelude.h"
#include "pipeline/Pipeline.h"
using namespace TinyFp;
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( test_suite_pipeline )

BOOST_AUTO_TEST_CASE(Pipeline_builder)
{
    FakeContext context = FakeContext(1);

    auto pipeline = Pipeline<FakeContext>::given(context);

    auto result = pipeline
                    .fit<Error>()
                    .right([](const Error& err) { return err.code; });

    BOOST_CHECK(result.context == 1);
}

BOOST_AUTO_TEST_SUITE_END()
