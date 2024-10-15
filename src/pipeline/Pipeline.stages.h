#ifndef LIB_TINY_FP_PIPELINE_STAGES
#define LIB_TINY_FP_PIPELINE_STAGES

#include "../common.h"

using namespace std;

namespace TinyFp
{
  template <class E, class C>
  struct ConditionalStage
  {
  private:
    function<Either<E, C>(const C& context)> _forward;
    function<bool(const C& context)> _enabled;
  public:
    ConditionalStage(){};
    ConditionalStage(function<Either<E, C>(const C& context)> forward, function<bool(const C& context)> enabled)
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
    function<Either<E, C>(const C& context)> _forward;
  public:
    Stage(){};
    Stage(function<Either<E, C>(const C& context)> forward)
    {
        _forward = forward;
    };
    Either<E, C> forward (const C& context) { return _forward(context); };
  };
}

#endif
