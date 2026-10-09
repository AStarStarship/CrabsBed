// Copyright AStarship <https://astarship.net>.

#pragma once
#include <_Config.h>
#ifndef KABUKI_TEK_PORTALWIFI
#define KABUKI_TEK_PORTALWIFI 1
namespace _ {

class PortalWifi : _::Portal {
 public:
  /* Constructor creates a loop back port. */
  PortalWifi(_::Crabs* crabs);

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
  _::Crabs* crabs;  //< Crabs for this Portal.
};                //< class I2CPortal
}  //< namespace _
#endif
