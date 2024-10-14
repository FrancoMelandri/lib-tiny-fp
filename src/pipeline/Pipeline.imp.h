namespace TinyFp
{
  template <class C>
  template<class E>
  Either<E, C> Pipeline<C>::fit()
  {
    return Either<E, C>::right(_context);
  }
}
