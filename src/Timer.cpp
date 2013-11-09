#include "Timer.hpp"
#include "stm32f30x.h"
#include <algorithm>

std::vector<uint32_t*> Timer::_counts;

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
  _counts.erase(std::find(_counts.begin(), _counts.end(), &_count));
}
