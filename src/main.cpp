#include "stm32f30x.h"
#include "stm32f3_discovery.h"
#include <string>
#include <iostream>
#include "Roulette.hpp"

int main()
{
  std::string hoge("hoge");
//  std::cout << hoge << std::endl;

  SystemInit();
  Roulette& roulette = Roulette::GetInstance();
  roulette.Delay(100);

  while (true)
  {
    roulette.Update(); 
  }

  return 0;
}
