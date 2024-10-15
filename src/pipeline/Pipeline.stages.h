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
    FuncValue<Either<E, C>, C> _forward;
    FuncSelector<C> _enabled;
  public:
    ConditionalStage(){};
    ConditionalStage(FuncValue<Either<E, C>, C> forward, FuncSelector<C> enabled)
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
    FuncValue<Either<E, C>, C> _forward;
  public:
    Stage(){};
    Stage(FuncValue<Either<E, C>, C> forward)
    {
        _forward = forward;
    };
    Either<E, C> forward (const C& context) { return _forward(context); };
  };
}

#endif
