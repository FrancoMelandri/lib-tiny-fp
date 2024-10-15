
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

Either<Error, FakeBuilderContext> firstBuilder(const FakeBuilderContext& state)
{
    auto first = FakeContext(1);
    auto newState = state;
    newState.setFirst(first);
    return Either<Error, FakeBuilderContext>::right(newState);
};

Either<Error, FakeBuilderContext> secondBuilder(const FakeBuilderContext& state)
{
    auto second = FakeContext(42);
    auto newState = state;
    newState.setSecond(second);
    return Either<Error, FakeBuilderContext>::right(newState);
};

Either<Error, FakeBuilderContext> secondBuilderError(const FakeBuilderContext& state)
{
    auto error = Error(42);
    return Either<Error, FakeBuilderContext>::left(error);
};

BOOST_AUTO_TEST_SUITE( test_suite_pipeline )

BOOST_AUTO_TEST_CASE(Pipeline_builder_all_stage_acitve)
{
    auto context = FakeContext(1);
    vector<ConditionalStage<Error, FakeContext>> stagesVector = 
    {
        ConditionalStage<Error, FakeContext>(firstStep, firstStepEnabled),
        ConditionalStage<Error, FakeContext>(secondStep, secondStepEnabled),
        ConditionalStage<Error, FakeContext>(thirdStep, thirdStepEnabled)
    };
    auto seq = Sequence<ConditionalStage<Error, FakeContext>>::from(stagesVector);

    auto result = Pipeline<FakeContext>::given(context)
                    .flow<Error>(seq)
                    .right([](const Error& err) { return err.code; });

    BOOST_CHECK(result.context == 8);
}

BOOST_AUTO_TEST_CASE(Pipeline_builder_some_stage_acitve)
{
    auto context = FakeContext(1);
    vector<ConditionalStage<Error, FakeContext>> stagesVector = 
    {
        ConditionalStage<Error, FakeContext>(firstStep, firstStepEnabled),
        ConditionalStage<Error, FakeContext>(secondStep, secondStepDisabled),
        ConditionalStage<Error, FakeContext>(thirdStep, thirdStepEnabled)
    };
    auto seq = Sequence<ConditionalStage<Error, FakeContext>>::from(stagesVector);

    auto result = Pipeline<FakeContext>::given(context)
                    .flow<Error>(seq)
                    .right([](const Error& err) { return err.code; });

    BOOST_CHECK(result.context == 6);
}

BOOST_AUTO_TEST_CASE(Pipeline_builder_whenLeft_handleError)
{
    auto context = FakeContext(1);
    vector<ConditionalStage<Error, FakeContext>> stagesVector = 
    {
        ConditionalStage<Error, FakeContext>(firstStep, firstStepEnabled),
        ConditionalStage<Error, FakeContext>(secondStepLeft, secondStepEnabled),
        ConditionalStage<Error, FakeContext>(thirdStep, thirdStepEnabled)
    };
    auto seq = Sequence<ConditionalStage<Error, FakeContext>>::from(stagesVector);

    auto result = Pipeline<FakeContext>::given(context)
                    .flow<Error>(seq)
                    .right([](const Error& err) { return err.code; });

    BOOST_CHECK(result.context == 42);
}

BOOST_AUTO_TEST_CASE(Pipeline_builder_NoConditional)
{
    auto context = FakeBuilderContext();
    vector<Stage<Error, FakeBuilderContext>> stagesVector = 
    {
        Stage<Error, FakeBuilderContext>(firstBuilder),
        Stage<Error, FakeBuilderContext>(secondBuilder)
    };
    auto seq = Sequence<Stage<Error, FakeBuilderContext>>::from(stagesVector);

    auto result = Pipeline<FakeBuilderContext>::given(context)
                    .flow<Error>(seq)
                    .right([](const Error& err) { return FakeBuilderContext(); });

    BOOST_CHECK(result.getFirst().context == 1);
    BOOST_CHECK(result.getSecond().context == 42);
}

BOOST_AUTO_TEST_CASE(Pipeline_builder_NoConditional_Error)
{
    auto context = FakeBuilderContext();
    vector<Stage<Error, FakeBuilderContext>> stagesVector = 
    {
        Stage<Error, FakeBuilderContext>(firstBuilder),
        Stage<Error, FakeBuilderContext>(secondBuilderError)
    };
    auto seq = Sequence<Stage<Error, FakeBuilderContext>>::from(stagesVector);

    auto result = Pipeline<FakeBuilderContext>::given(context)
                    .flow<Error>(seq)
                    .right([](const Error& err) { return FakeBuilderContext(); });

    BOOST_CHECK(result.getFirst().context == 0);
    BOOST_CHECK(result.getSecond().context == 0);
}

BOOST_AUTO_TEST_SUITE_END()
