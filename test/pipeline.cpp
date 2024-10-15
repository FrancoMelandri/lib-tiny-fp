
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

bool secondStepEnabled(const FakeContext& context)
{
    return true;
};

bool secondStepDisabled(const FakeContext& context)
{
    return false;
};

Either<Error, FakeContext> secondStep(const FakeContext& context)
{
    auto newContext = FakeContext(context.context + 2);
    return Either<Error, FakeContext>::right(newContext);
};

Either<Error, FakeContext> secondStepLeft(const FakeContext& context)
{
    auto error = Error(42);
    return Either<Error, FakeContext>::left(error);
};

bool thirdStepEnabled(const FakeContext& context)
{
    return true;
};

Either<Error, FakeContext> thirdStep(const FakeContext& context)
{
    auto newContext = FakeContext(context.context + 4);
    return Either<Error, FakeContext>::right(newContext);
};

BOOST_AUTO_TEST_SUITE( test_suite_pipeline )

BOOST_AUTO_TEST_CASE(Pipeline_builder_all_stage_acitve)
{
    auto context = FakeContext(1);
    vector<Stage<Error, FakeContext>> stagesVector = 
    {
        Stage<Error, FakeContext>(firstStep, firstStepEnabled),
        Stage<Error, FakeContext>(secondStep, secondStepEnabled),
        Stage<Error, FakeContext>(thirdStep, thirdStepEnabled)
    };
    auto seq = Sequence<Stage<Error, FakeContext>>::from(stagesVector);

    auto result = Pipeline<FakeContext>::given(context)
                    .flow<Error>(seq)
                    .right([](const Error& err) { return err.code; });

    BOOST_CHECK(result.context == 8);
}

BOOST_AUTO_TEST_CASE(Pipeline_builder_some_stage_acitve)
{
    auto context = FakeContext(1);
    vector<Stage<Error, FakeContext>> stagesVector = 
    {
        Stage<Error, FakeContext>(firstStep, firstStepEnabled),
        Stage<Error, FakeContext>(secondStep, secondStepDisabled),
        Stage<Error, FakeContext>(thirdStep, thirdStepEnabled)
    };
    auto seq = Sequence<Stage<Error, FakeContext>>::from(stagesVector);

    auto result = Pipeline<FakeContext>::given(context)
                    .flow<Error>(seq)
                    .right([](const Error& err) { return err.code; });

    BOOST_CHECK(result.context == 6);
}

BOOST_AUTO_TEST_CASE(Pipeline_builder_whenLeft_handleError)
{
    auto context = FakeContext(1);
    vector<Stage<Error, FakeContext>> stagesVector = 
    {
        Stage<Error, FakeContext>(firstStep, firstStepEnabled),
        Stage<Error, FakeContext>(secondStepLeft, secondStepEnabled),
        Stage<Error, FakeContext>(thirdStep, thirdStepEnabled)
    };
    auto seq = Sequence<Stage<Error, FakeContext>>::from(stagesVector);

    auto result = Pipeline<FakeContext>::given(context)
                    .flow<Error>(seq)
                    .right([](const Error& err) { return err.code; });

    BOOST_CHECK(result.context == 42);
}

BOOST_AUTO_TEST_SUITE_END()
