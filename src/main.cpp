#include "stm32f30x.h"
#include "stm32f3_discovery.h"
#include <string>
#include <iostream>
#include "Roulette.hpp"

extern "C" int main()
{

  std::string hoge("hoge");
//  std::cout << hoge << std::endl;

  Roulette::Delay(100);

  while (true)
  {
    Roulette::Update(); 
  }

  return 0;
}
