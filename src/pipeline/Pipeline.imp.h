namespace TinyFp
{
  template <class C>
  template<class E>
  Either<E, C> Pipeline<C>::flow(Sequence<ConditionalStage<E, C>>& stages)
  {
    auto ctx = _context;
    for (auto & item : stages) {
      if (!item.enabled(ctx))
        continue;
      
      auto nextState = item.forward(ctx);
      if(nextState.isLeft())
        return nextState;

      ctx = nextState.unwrap();
    };
    _context = ctx;
    return Either<E, C>::right(_context);
  }

  template <class C>
  template<class E>
  Either<E, C> Pipeline<C>::flow(Sequence<Stage<E, C>>& stages)
  {
    auto ctx = _context;
    for (auto & item : stages) {
      auto nextState = item.forward(ctx);
      if(nextState.isLeft())
        return nextState;

      ctx = nextState.unwrap();
    };
    _context = ctx;
    return Either<E, C>::right(_context);
  }
}
