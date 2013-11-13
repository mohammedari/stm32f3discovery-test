#include "stm32f30x.h"
#include "stm32f3_discovery.h"
#include <string>
#include <iostream>
#include "Roulette.hpp"
#include "Serial.hpp"
#include "Timer.hpp"

extern "C" int main()
{
  std::string hoge("hoge");
  std::cout << hoge << std::endl;

  Roulette::Delay(100);
  Timer timer;

  while (true)
  {
    //std::cin >> i;
    Roulette::Update();
    std::cout << "barfoo" << 100 << std::endl;

    timer.WaitMs(1);
  }

  return 0;
}
