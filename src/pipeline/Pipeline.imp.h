namespace TinyFp
{
  template <class C>
  template<class E>
  Either<E, C> Pipeline<C>::fit(Sequence<Stage<E, C>>& stages)
  {
    for (auto & item : stages) {
      if (!item.enabled(_context))
      {
        continue;
      }
      auto newContext = item.forward(_context);
      auto ctx = _context;
      _context = newContext.right([ctx](const E& error) { return ctx; } );
    };
    return Either<E, C>::right(_context);
  }
}
