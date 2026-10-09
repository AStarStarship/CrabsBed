// Copyright AStarship <https://astarship.net>.
vv
#pragma once
#include <_Config.h>
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
  const Operation* Star(ISW index, _::Crabs* crabs);

 private:
};
}  //< namespace _

#endif
