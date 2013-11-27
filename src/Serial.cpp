#include "Serial.hpp"

boost::circular_buffer<char> Serial::_rbuf(Serial::_rbufsize);
boost::circular_buffer<char> Serial::_wbuf(Serial::_wbufsize);

Serial::Initializer Serial::_initializer;
Serial::Initializer::Initializer()
{
  //Interrupt Configuration
  NVIC_InitTypeDef nvic;
  nvic.NVIC_IRQChannel = USART1_IRQn;
  nvic.NVIC_IRQChannelPreemptionPriority = 1;
  nvic.NVIC_IRQChannelSubPriority = 0;
  nvic.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic);

  //Clock Configuration
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  //USART GPIO Connection
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);

  //GPIO Configuration
  GPIO_InitTypeDef gpio;
  gpio.GPIO_Mode = GPIO_Mode_AF;
  gpio.GPIO_Speed = GPIO_Speed_50MHz;
  gpio.GPIO_OType = GPIO_OType_PP;
  gpio.GPIO_PuPd = GPIO_PuPd_UP;
  gpio.GPIO_Pin = GPIO_Pin_9;
  GPIO_Init(GPIOA, &gpio);
  gpio.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOA, &gpio);

  //USART Configuration
  USART_InitTypeDef usart;
  usart.USART_BaudRate = _baudrate;
  usart.USART_WordLength = USART_WordLength_8b;
  usart.USART_StopBits = USART_StopBits_1;
  usart.USART_Parity = USART_Parity_No;
  usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &usart);

  //enable USART
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART1, ENABLE);
}

size_t Serial::Read(char* ptr, size_t len)
{
  USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
  size_t received = 0;
  while (!_rbuf.empty() && received < len)
  {
    *ptr++ = _rbuf.front();
    _rbuf.pop_front();

    ++received;
  }
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

  return received;
} 

size_t Serial::Write(char* ptr, size_t len)
{
  USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
  size_t sent = 0;
  while (sent < len)
  {
    _wbuf.push_back(*ptr++);
    ++sent;
  }
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

  return sent;
}

void Serial::InterruptHandler()
{
  //Receive
  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    _rbuf.push_back(static_cast<char>(USART_ReceiveData(USART1)));
    return;
  }

  //Send
  if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {
    if (!_wbuf.empty())
    {
      USART_SendData(USART1, _wbuf.front());
      _wbuf.pop_front();
    }
    else
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);

    return;
  }

  //Interrupts which is not permitted raised!
  //This happens when so many packetes are received.
  //Something is wrong... reset USART module.
  USART_Cmd(USART1, DISABLE);
  USART_Cmd(USART1, ENABLE);
}
