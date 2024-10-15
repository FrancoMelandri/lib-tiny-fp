# Pipeline

This class allow you to handle a sequence of `Stage`.
Each `Stage` has an enabled function that act as forward step enabler.
The pipelines scan all stage to return Left in cas of one forward step fail, or the cumulative Right value.

The pipeline should be created using a **context** object; it acts as status of the pipeline.
The status will be passed as parameter in both **enabled** and **forward** function call.

## factories

### 

```c++
static Pipeline<C> given(C& context);
```

## functional

### flow

```c++
template<class E> Either<E, C> flow(Sequence<Stage<E, C>>& stages);
```

Execute the pipeline flow invoking the **forward()** function for all **enabled()** stage

## example

```c++

bool firstStepEnabled(const FakeContext& context)
{
    return true;
};

Either<Error, FakeContext> firstStep(const FakeContext& context)
{
    auto newContext = FakeContext(context.context + 1);
    return Either<Error, FakeContext>::right(newContext);
};

...

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
```

