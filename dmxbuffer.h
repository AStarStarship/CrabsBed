/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /dmx_buffer.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_DMX_DMX_BUFFER_H
#define KABUKI_DMX_DMX_BUFFER_H

namespace _ {

class DMXBuffer {
 public:
  enum {
    cBufferCount = 512,
  };
  DMXBuffer() {}

 private:
  IUA buffer_[cBufferCount];
};
}  // namespace _
#endif
