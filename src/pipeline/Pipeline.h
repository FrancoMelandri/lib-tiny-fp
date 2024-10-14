#ifndef LIB_TINY_FP_PIPELINE
#define LIB_TINY_FP_PIPELINE

#include "../common.h"
#include "../either/Either.h"
#include "../sequence/Sequence.h"

using namespace std;

namespace TinyFp
{
  template <class E, class C>
  struct Stage
  {
  private:
    function<Either<E, C>(const C& context)> _forward;
    function<bool(const C& context)> _enabled;
  public:
    Stage(){};
    Stage(function<Either<E, C>(const C& context)> forward, function<bool(const C& context)> enabled)
    {
        _forward = forward;
        _enabled = enabled;
    };
    Either<E, C> forward (const C& context) { return _forward(context); };
    bool enabled (const C& context) { return _enabled(context); };
  };

  template <class C>
  struct Pipeline
  {
    private:
        C _context;

        Pipeline(C& context)
        {
            _context = context;
        }

    public:
        static Pipeline<C> given(C& context) { return Pipeline<C>(context); };
        template<class E> Either<E, C> fit(Sequence<Stage<E, C>>& stages);
  };
}

#include "Pipeline.imp.h"

#endif
