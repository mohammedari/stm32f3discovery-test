#include "Roulette.hpp"

uint32_t Roulette::_delay;
uint32_t Roulette::_pos = 0;

const Led_TypeDef Roulette::_sequence[] 
  = { LED3, LED5, LED7, LED9, LED10, LED8, LED6, LED4 };

Roulette::Initializer Roulette::_initializer;
Roulette::Initializer::Initializer()
{
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  STM_EVAL_LEDInit(LED7);
  STM_EVAL_LEDInit(LED8);
  STM_EVAL_LEDInit(LED9);
  STM_EVAL_LEDInit(LED10);
}

void Roulette::Update()
{
  if (_timer().Count() == 0)
  {
    STM_EVAL_LEDToggle(_sequence[_pos % 8]);
    ++_pos;
    _timer().Count(_delay);
  }
}
