#include "Timer.hpp"
#include "stm32f30x.h"
#include <algorithm>

std::list<uint32_t*> Timer::_counts __attribute__((init_priority(150)));

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

  _counts.push_back(&_count);
}

Timer::~Timer()
{
  _counts.remove(&_count);
}
