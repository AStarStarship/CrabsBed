/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /portal_serial.h
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#include "portalserial.h"

namespace _ {

SerialPortal::SerialPortal(Expr* expr, PinName tx_pin, PinName rx_pin)
    : expr_(expr), serial_(tx_pin, rx_pin) {
  /// Nothing to do here!
}

void SerialPortal::Feed() {
  // while (serial_.readable ()) expr_.StreamTxByte ();
}

void SerialPortal::Pull() {
  // while (serial_.readable ()) expr_.StreamRxByte (serial_.getc ());
}

}  // namespace _
