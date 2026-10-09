// Copyright AStarship <https://astarship.net>.

#pragma once
#include <_Config.h>
#ifndef KABUKI_TEK_SPI_PORTAL
#define KABUKI_TEK_SPI_PORTAL 1

namespace _ {

/* A type of Portal that allows for reading and writing to the local system. */
class SpiPortal : public _::Portal {
 public:
  /* Constructs a SpiPortal. */
  SpiPortal(_::Crabs* crabs, PinName mosi_pin, PinName miso_pin,
            PinName clock_pin, PinName strobe_pin);

  /* Feeds B-Output bytes through the slot. */
  virtual void Feed();

  /* Pulls B-Input bytes through the slot. */
  virtual void Pull();

 private:
  _::Crabs* expr_;    //< Crabs for this Portal.
  ISC start_index_,  //< Start index of the buffer.
      stop_index_,   //< Stop index of the buffer.
      buffer_size_;  //< Buffer size in bytes.
  SPI spi_;          //< SPI port.
};
}  //< namespace _
#endif
