/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /tests/01_bar.hpp
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright 2019 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <module_config.h>

#if SEAM == UNICONTROLLER_FIRMWARE_0
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

using namespace _;

namespace project { namespace unicontroller_firmware { 
inline const CHA* Bar (CHA* seam_log, CHA* seam_end, const CHA* args) {
#if SEAM >= UNICONTROLLER_FIRMWARE_0
  A_TEST_BEGIN;

  

#endif
  return 0;
}
}  //< namespace unicontroller_firmware
}  //< namespace project
