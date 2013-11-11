#include "Timer.hpp"
#include "stm32f30x.h"
#include <algorithm>

Timer::Timer()
 : _count(0)
{
  static bool firstTime = true;
  if (firstTime)
  {
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);

    firstTime = false;
  }

  _counts().push_back(&_count);
}

Timer::~Timer()
{
  _counts().remove(&_count);
}
