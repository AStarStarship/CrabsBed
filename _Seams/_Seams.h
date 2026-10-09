// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef CRABS_BED_SEAMS_H
#define CRABS_BED_SEAMS_H

// Pull the core seams first (CRABS_* 1..23) so the core type headers resolve.
#include "../../ASCIICrabs/_Seams/_Seams.h"

// Pin the core counter so a future upstream bump fails loudly here.
static_assert(SEAM_N == CRABS_SCRIPT,
              "ASCIICrabs seam counter changed; re-pin CRABS_BED_BASE");

// Core counter at the time of the CrabsBed port (2026-10-08).
#define CRABS_BED_BASE 23

// CrabsBed implementation seams.
#define CRABS_BED_DEBOUNCER 24
#define CRABS_BED_COLOR     25
#define CRABS_BED_LEDS      26
#define CRABS_BED_UNICONTROLLER 27
#define CRABS_BED_MIDI          28
#define CRABS_BED_BREADBOARD    29

// Test seams.
#define CRABS_BED_CORE     40  //< FIRST — the unit-test seam (default).
#define CRABS_BED_RELEASE  41  //< LAST  — the release demo seam.
#define SEAM_N             CRABS_BED_RELEASE

#endif
