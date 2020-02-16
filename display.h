/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /display.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_TEK_DISPLAY
#define KABUKI_TEK_DISPLAY 1

namespace _ {

class Controller;

/* An abstract Display. */
class Display : public _::Operation {
 public:
  /* Constructs an abstract display. */
  Display();

  /* Virtual destructor. */
  virtual ~Display() = 0;

  /* Virtual function updates the display. */
  virtual void Update() = 0;

  /*< Script operations. */
  const Operation* Star(char_t index, _::Expr* expr);

 private:
};
}  // namespace _

#endif
