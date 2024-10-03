namespace TinyFp
{
  template <typename T>
  bool Option<T>::IsSome()
  {
    return _value != NO_VALUE;
  }
}
