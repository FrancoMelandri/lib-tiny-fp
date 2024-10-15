namespace TinyFp
{
  template <class C>
  template<class E>
  Either<E, C> Pipeline<C>::flow(Sequence<Stage<E, C>>& stages)
  {
    auto ctx = _context;
    for (auto & item : stages) {
      if (!item.enabled(ctx))
        continue;
      
      auto nextState = item.forward(ctx);
      if(!nextState.isRight())
        return nextState;

      ctx = nextState.right([ctx](const E& error) { return ctx; } );
    };
    _context = ctx;
    return Either<E, C>::right(_context);
  }
}
