#include "stm32f30x.h"
#include "stm32f3_discovery.h"
#include <string>
#include <iostream>
#include "Roulette.hpp"
#include "Serial.hpp"
#include "Timer.hpp"
#include <unistd.h>
#include <boost/array.hpp>

extern "C" int main()
{
  std::string hoge("Hello World!");
  std::cout << hoge << std::endl;

  Roulette::Delay(100);
  Timer timer;

  boost::array<char, 256> buf;
  while (true)
  {
    size_t n = read(STDIN_FILENO, buf.data(), buf.size() - 1);
    if (n > 0)
    {
      buf[n] = '\0';
      write(STDOUT_FILENO, buf.data(), n);
    }

    Roulette::Update();
    timer.WaitMs(1000);
  }

  return 0;
}
