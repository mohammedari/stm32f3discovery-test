#include "Timer.hpp"

extern "C" {

void NMI_Handler()
{
}

void HardFault_Handler()
{
  while(true);
}

void MemManage_Handler()
{
  while(true);
}

void BusFault_Handler()
{
  while(true);
}

void UsageFault_Handler()
{
  while(true);
}

void SVC_Handler()
{
}

void DebugMon_Handler()
{
}

void PendSV_Handler()
{
}

void SysTick_Handler()
{
  Timer::Tick();
}

}
