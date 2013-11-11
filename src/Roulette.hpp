#pragma once

#include "Timer.hpp"
#include <boost/noncopyable.hpp>
#include <stdint.h>
#include "stm32f3_discovery.h"

class Roulette : private boost::noncopyable
{
  static struct Initializer
  {
    Initializer();
  } _initializer;

public:
  static void Delay(uint32_t delay) { _delay = delay; } 
  static void Update();

private:
  static uint32_t _delay;
  static uint32_t _pos;
  static const Led_TypeDef _sequence[8];

  static Timer& _timer()
  {
    static Timer timer;
    return timer;
  }
 
  Roulette();
};
