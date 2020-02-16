/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /_seams/00.core.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2019 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>

#if SEAM == KABUKI_TEK_CORE
#include "_debug.inl"
#else
#include "_release.inl"
#endif

using namespace _;

namespace kabuki {
namespace tek {
inline const CHA* Core(const CHA* args) {
#if SEAM >= KABUKI_TEK_CORE
  TEST_BEGIN;

#endif
  return 0;
}
}  // namespace tek
}  // namespace kabuki
