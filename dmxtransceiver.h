/* Kabuki Tek Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki.toolkit.tek.git
@file    /dmx_receiver.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright 2014-20 (C) Kabuki Starship (TM) <kabukistarship.com>.
This Source Code Form is subject to the terms of the Mozilla Public License, v. 
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <_config.h>
#ifndef KABUKI_TEK_DMX_DMXTRANSCEIVER_H
#define KABUKI_TEK_DMX_DMXTRANSCEIVER_H

#include "dmxreceiver.h"
#include "dmxtransmitter.h"

namespace _ {

template <IUA NumPorts>
class DMXTransceiver {
 public:
  /* Default constructor. */
  DMXTransceiver();

  /* Returns a reference to the DMXTransmitter. */
  DMXTransmitter& GetTransmitter();

  /* Returns a reference to the DMXReceiver. */
  DMXReceiver& GetReceiver;

 private:
  DMXTransmitter transmitter_;
  DMXReceiver receiver_;
};
}  // namespace _
#endif
