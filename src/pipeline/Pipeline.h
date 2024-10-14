#ifndef LIB_TINY_FP_PIPELINE
#define LIB_TINY_FP_PIPELINE

#include "../common.h"
#include "../either/Either.h"

using namespace std;

namespace TinyFp
{
  template <class C>
  struct Pipeline
  {
    private:
        C _context;

        Pipeline(const C& context)
        {
            _context = context;
        }

    public:
        static Pipeline<C> given(const C& context) { return Pipeline<C>(context); };
        template<class E> Either<E, C> fit();
  };
}

#include "Pipeline.imp.h"

#endif
