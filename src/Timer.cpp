#include "Timer.hpp"
#include "stm32f30x.h"

uint32_t Timer::count = 0;

void Timer::Init()
{
  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock / 1000);
}
