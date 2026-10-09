// Copyright AStarship <https://astarship.net>.
#include <_Config.h>
#include "_Tests.hxx"
using namespace ::_;

ISN main(ISN arg_count, CHA** args) {
  const CHA* argss = ArgsToString(arg_count, args);
#if SEAM == SEAM_N
  return SeamResult(CBTest::Release(argss));
#else
  return TTestTree<CrabsBedTests>(arg_count, args);
#endif
}
