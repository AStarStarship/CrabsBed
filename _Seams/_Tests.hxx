// Copyright AStarship <https://astarship.net>.
#include <_Config.h>
// Core package (COut, Random, etc. — the implementations the bed needs).
#include "../../ASCIICrabs/_Package.hxx"
// The Debug/Release macro set. Must come after _Package.hxx: Test.hxx pulls
// _Release.h, which undefs the Debug macros.
#include "../../ASCIICrabs/_Debug.h"
#include "Debouncer.h"
#include "Color.h"
#include "Color.hxx"
#include "LED.h"
#include "LED.hxx"
#include "Midi.h"
#include "Midi.hxx"
#include "VirtualBreadboard.h"
#include "UnicontrollerDriver.h"
#include "00.Core.hxx"
#include "01.Release.hxx"
#include "../../ASCIICrabs/Test.hpp"
using namespace ::_;

inline const CHA* CrabsBedTests(const CHA* args) {
  return TTestTree<CBTest::Core, CBTest::Release>(args);
}
