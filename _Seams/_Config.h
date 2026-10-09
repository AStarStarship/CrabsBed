// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_BED_CONFIG
#define CRABS_BED_CONFIG
// Pull the core seams first (CRABS_* 1..23) and pin the core counter.
#include "_Seams.h"
// Set the seam BEFORE the config chain: _ConfigFooter.h defaults SEAM to
// CRABS_RELEASE when it is undefined. Overridable via -DCRABS_BED_SEAM=...
#ifndef CRABS_BED_SEAM
#define CRABS_BED_SEAM CRABS_BED_CORE
#endif
#define SEAM CRABS_BED_SEAM
#include "../../ASCIICrabs/_ConfigDefault.h"
#include "../../ASCIICrabs/_ConfigHeader.h"
#include "../../ASCIICrabs/_ConfigFooter.h"
#endif
