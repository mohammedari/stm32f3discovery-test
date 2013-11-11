#include "stm32f30x.h"
#include "stm32f3_discovery.h"
#include <string>
#include <iostream>
#include "Roulette.hpp"
#include "Serial.hpp"

extern "C" int main()
{
  std::string hoge("hoge");
  std::cout << hoge << std::endl;

  Roulette::Delay(100);

  int i = 0; 
  while (true)
  {
    std::cin >> i;
    Roulette::Update();
    std::cout << i << std::endl;
  }

  return 0;
}
