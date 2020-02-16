/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /portal_wifi.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_TEK_PORTALWIFI
#define KABUKI_TEK_PORTALWIFI 1
namespace _ {

class WifiPortal : _::Portal {
 public:
  /* Constructor creates a loop back port. */
  WifiPortal(_::Expr* expr);

  /* Sets the Portal up for a batch of bytes transfer.
    Implementation of this function is not required to do anything, but
    regardless it will be called by the Set. */
  // virtual void Prime ();

  /* Gets the length of current portal.
      @warning Length might not be the actual length, but rather the length
               of the data that is read to be pulled. */
  // virtual uint_t Length ();

  /* Feeds tx messages through the a without scanning them. */
  virtual void Feed();

  /* Pulls rx messages through the a and runs them through the scanner. */
  virtual void Pull();

 private:
  _::Expr* expr;  //< Expr for this Portal.
};                //< class I2CPortal
}  // namespace _
#endif
