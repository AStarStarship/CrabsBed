// Copyright AStarship <https://astarship.net>.

#pragma once
#include <_Config.h>
#ifndef KABUKI_DMX_DMX_BUFFER_H
#define KABUKI_DMX_DMX_BUFFER_H

namespace _ {

class DMXBuffer {
 public:
  enum {
    cBufferCount = 512,
  };
  DMXBuffer() {}

 private:
  IUA buffer_[cBufferCount];
};
}  //< namespace _
#endif
