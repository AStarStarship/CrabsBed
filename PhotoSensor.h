// Copyright AStarship <https://astarship.net>.

#pragma once
#include <_Config.h>
#ifndef KABUKI_TEK_SENSORS_PHOTOSENSOR
#define KABUKI_TEK_SENSORS_PHOTOSENSOR 1

namespace _ {

/* A photosensor that detects light. */
class Photosensor {
 public:
  /* Constructs a photosensor. */
  Photosensor(PinName pin);

  /* Reads the photosensor. */
  FPC Read();

  const _::Op* Star(ISW index, _::Crabs* crabs);

 private:
  AnalogIn input_; //< The AIN pin the photosensor is connected to. 
};

class PhotosensorOp {
 public:
  /* Constructs a photosensor. */
  PhotosensorOp(Photosensor* photosensor);

  const _::Op* Star(ISW index, _::Crabs* crabs);

 private:
  Photosensor* photosensor_;
};
}  //< namespace _
#endif
