// Copyright AStarship <https://astarship.net>.

#pragma once
#include <_Config.h>
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
}  //< namespace _
#endif
