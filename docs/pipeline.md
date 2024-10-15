# Pipeline

This class allow you to handle a sequence of `ConditionalStage`.
Each `ConditionalStage` has an enabled function that act as forward step enabler.
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
template<class E> Either<E, C> flow(Sequence<ConditionalStage<E, C>>& stages);
template<class E> Either<E, C> flow(Sequence<Stage<E, C>>& stages);
```

Execute the pipeline flow invoking the **forward()** function for all **enabled()** stage

### Stage

`Stage` struct holds the **forward** callback to be called during pipeline flow.

```c++
template <class E, class C>
struct Stage
{
public:
    Stage();
    Stage(FuncValue<Either<E, C>, C> forward);
};

```
### ConditionalStage

`ConditionalStage` struct holds both the **forward** and **enabled** callback to be called during pipeline flow.

```c++
template <class E, class C>
struct ConditionalStage
{
public:
    ConditionalStage();
    ConditionalStage(FuncValue<Either<E, C>, C> forward, FuncSelector<C> enabled> enabled);
};
```

## example

conditional

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
```


builder

```c++
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

...

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

```
