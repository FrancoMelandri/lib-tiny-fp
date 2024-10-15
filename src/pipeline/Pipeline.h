#ifndef LIB_TINY_FP_PIPELINE
#define LIB_TINY_FP_PIPELINE

#include "../common.h"
#include "../either/Either.h"
#include "../sequence/sequence.h"
#include "Pipeline.stages.h"

using namespace std;

namespace TinyFp
{
  template <class C>
  struct Pipeline
  {
    private:
        C _context;

        Pipeline(C& context) { _context = context; }
    public:
        static Pipeline<C> given(C& context) { return Pipeline<C>(context); };
        template<class E> Either<E, C> flow(Sequence<ConditionalStage<E, C>>& stages);
        template<class E> Either<E, C> flow(Sequence<Stage<E, C>>& stages);
  };
}

#include "Pipeline.imp.h"

#endif
