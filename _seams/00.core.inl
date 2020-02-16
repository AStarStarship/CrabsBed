/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /_seams/00.coreinl
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright 2019 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>

#if SEAM == ASTARTUP_COOKBOOK_TEST
#include "_debug.inl"
#else
#include "_release.inl"
#endif

using namespace _;

namespace astartup {
namespace cookbook {
inline const CHA* _0_Foo(CHA* seam_log, CHA* seam_end, const CHA* args) {
#if SEAM >= ASTARTUP_COOKBOOK_TEST
  TEST_BEGIN;

  PRINT_HEADING("Testing Foo Fun.");

#endif
  return 0;
}
}  // namespace cookbook
}  // namespace astartup
