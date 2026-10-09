// Copyright AStarship <https://astarship.net>.

#pragma once
#include <_Config.h>
#ifndef KABUKI_TEK_I2C_PORTAL_DECL
#define KABUKI_TEK_I2C_PORTAL_DECL

namespace _ {

/* A Portal for a half-duplex I2C data link. */
class I2cPortal : public _::Portal {
  /* Constructor creates a loop back port. */
  I2cPortal(_::Crabs* crabs, PinName sda_pin, PinName scl_pin);

  /* Feeds tx messages through the a without scanning them. */
  virtual void Feed();

  /* Pulls rx messages through the a and runs them through the scanner. */
  virtual void Pull();

 private:
  _::Crabs* expr_;  //< Crabs for this Portal.
  I2C i2c_;        //< mbed Serial port.
};                 //< class I2CPortal
}  //< namespace _
#endif
