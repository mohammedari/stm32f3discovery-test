#include "stm32f30x.h"
#include "stm32f3_discovery.h"
#include "Timer.hpp"

int main()
{
  Timer::Init();
  const int delay = 100;

  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  STM_EVAL_LEDInit(LED7);
  STM_EVAL_LEDInit(LED8);
  STM_EVAL_LEDInit(LED9);
  STM_EVAL_LEDInit(LED10);

  while (true)
  {
    STM_EVAL_LEDToggle(LED3);
    Timer::WaitMs(delay);
    
    STM_EVAL_LEDToggle(LED5);
    Timer::WaitMs(delay);

    STM_EVAL_LEDToggle(LED7);
    Timer::WaitMs(delay);
    
    STM_EVAL_LEDToggle(LED9);
    Timer::WaitMs(delay);

    STM_EVAL_LEDToggle(LED10);
    Timer::WaitMs(delay);

    STM_EVAL_LEDToggle(LED8);
    Timer::WaitMs(delay);
    
    STM_EVAL_LEDToggle(LED6);
    Timer::WaitMs(delay);
   
    STM_EVAL_LEDToggle(LED4);
    Timer::WaitMs(delay);
  }

  return 0;
}
