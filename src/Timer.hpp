#pragma once

#include <stdint.h>

class Timer
{
public:
  static void Init(); 

  static inline void Tick()
  {
    if (count > 0)
       --count;
  }

  static inline void WaitMs(uint32_t delay)
  {
    count = delay;
    while (count > 0);
  }

private:
  static uint32_t count;
};
