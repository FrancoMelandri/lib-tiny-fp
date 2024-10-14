namespace TinyFp
{
  template <class C>
  template<class E>
  Either<E, C> Pipeline<C>::fit(const Sequence<Stage<E, C>>& stages)
  {
    return Either<E, C>::right(_context);
  }
}
