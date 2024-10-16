#ifndef LIB_TINY_FP_PIPELINE_STAGES
#define LIB_TINY_FP_PIPELINE_STAGES

#include "../common.h"
#include "../types/types.h"

using namespace std;

namespace TinyFp
{
  template <class E, class C>
  struct ConditionalStage
  {
  private:
    Unary<C, Either<E, C>> _forward;
    Predicate<C> _enabled;
  public:
    ConditionalStage(){};
    ConditionalStage(Unary<C, Either<E, C>> forward, Predicate<C> enabled)
    {
        _forward = forward;
        _enabled = enabled;
    };
    Either<E, C> forward (const C& context) { return _forward(context); };
    bool enabled (const C& context) { return _enabled(context); };
  };

  template <class E, class C>
  struct Stage
  {
  private:
    Unary<C, Either<E, C>> _forward;
  public:
    Stage(){};
    Stage(Unary<C, Either<E, C>> forward)
    {
        _forward = forward;
    };
    Either<E, C> forward (const C& context) { return _forward(context); };
  };
}

#endif
