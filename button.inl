/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /button.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#include "button.h"

namespace _ {

Button::Button(offset_t bit) : bit_offset_(bit) {}

inline IUA Button::GetState(IUA* digital_ins) {
  if (!digital_ins) {
    return 0;
  }
  offset_t bit = bit_offset_;
  return digital_ins[bit >> kBitToByteShift] & (1 << (bit & kBitNumberMask));
}

inline void Button::Poll(IUA* debounced_xor) {
  offset_t index = bit_offset_ >> kBitToByteShift,
           mask = 1 << (bit_offset_ & kBitNumberMask),
           state = debounced_xor[index] & mask;

  if (state == 0) {
    return;
  }
  if (debounced_xor[index] & mask) {
    press_->Trigger();
    return;
  }

  depress_->Trigger();
}

ButtonOp::ButtonOp(Button* object) : object_(object) {
  // Nothing to do here!
}

const Operation* ButtonOp::Star(char_t index, Expr* expr) {
  object_->Star(index, expr);
}

}  // namespace _
