/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /switch.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#include "switch.h"

namespace _ {

Switch::Switch(PinName pin) : input_(pin) {
  /// Nothing to do here!
}

const Operation* Switch::Star(char_t index, Expr* expr) {
  static const Operation This = {"Switch", NumOperations(0),
                                 FirstOperation('A'),
                                 "A software debounced switch.", 0};

  void* args[1];

  switch (index) {
    case '?':
      return &This;
    case 'a': {
      static const Operation OpA = {"Read", Params<1, ISC>(), Params<NIL>(),
                                    "Reads the switch state."};
      if (!expr) return &OpA;

      ISC temp = 0;  // input;
      IUA switchState = (IUA)temp;

      return Result(expr, Params<NIL>(), Args(args, &switchState));
    }
  }
  return nullptr;
}

SwitchOp::SwitchOp(Switch* object) : object_(object) {
  // Nothing to do here!
}

const Operation* SwitchOp::Star(char_t index, Expr* expr) {
  return object_->Star(index, expr);
}

}  // namespace _
