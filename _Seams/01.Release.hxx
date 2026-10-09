// Copyright AStarship <https://astarship.net>.
#include <_Config.h>
#if SEAM >= CRABS_BED_CORE
namespace CBTest {

// The release demo unit. Always defined so TTestTree can reference it; the
// demo body only runs when the build is at the release seam.
inline const CHA* Release(const CHA* args) {
  (void)args;
#if SEAM >= CRABS_BED_RELEASE
  IUA chain[4] = {0, 0, 0, 0};
  for (IUC i = 0; i < 32; ++i) TurnLedOn(chain, i);
  D_COUT(" CrabsBed release: 32-LED SPI chain pattern:");
  for (ISC byte = 0; byte < 4; ++byte) D_COUT(" " << (IUC)chain[byte]);
  D_COUT("\n");
#endif
  return NILP;
}

}  //< namespace CBTest
#endif
