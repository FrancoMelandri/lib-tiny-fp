
#include <boost/test/unit_test.hpp>
#include "Fakes.h"
#include "prelude.h"
#include "pipeline/Pipeline.h"
using namespace TinyFp;
using namespace boost::unit_test;

bool firstStepEnabled(const FakeContext& context)
{
    return true;
};

Either<Error, FakeContext> firstStep(const FakeContext& context)
{
    auto newContext = FakeContext(context.context + 1);
    return Either<Error, FakeContext>::right(newContext);
};

BOOST_AUTO_TEST_SUITE( test_suite_pipeline )

BOOST_AUTO_TEST_CASE(Pipeline_builder)
{
    auto stageFirstStep = Stage<Error, FakeContext>(firstStep, firstStepEnabled);
    vector<Stage<Error, FakeContext>> stagesVector = 
    {
        stageFirstStep
    };

    FakeContext context = FakeContext(1);
    auto seq = Sequence<Stage<Error, FakeContext>>::from(stagesVector);
    auto pipeline = Pipeline<FakeContext>::given(context);
    auto result = pipeline
                    .fit<Error>(seq)
                    .right([](const Error& err) { return err.code; });

    BOOST_CHECK(result.context == 1);
}

BOOST_AUTO_TEST_SUITE_END()
