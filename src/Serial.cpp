#include "Serial.hpp"

boost::circular_buffer<uint8_t> Serial::_rbuf(Serial::_rbufsize);
boost::circular_buffer<uint8_t> Serial::_wbuf(Serial::_wbufsize);

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
  USART_ITConfig(USART1, USART_IT_TXE,  DISABLE); 
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART1, USART_IT_TC,   DISABLE); 
  USART_ITConfig(USART1, USART_IT_IDLE, DISABLE); 
  USART_ITConfig(USART1, USART_IT_CTS,  DISABLE); 
  USART_ITConfig(USART1, USART_IT_LBD,  DISABLE); 
  USART_ITConfig(USART1, USART_IT_NE,   DISABLE); 
  USART_ITConfig(USART1, USART_IT_FE,   DISABLE); 
  USART_ITConfig(USART1, USART_IT_PE,   DISABLE); 
  USART_ITConfig(USART1, USART_IT_ORE,  DISABLE); 
  USART_Cmd(USART1, ENABLE);
}

void Serial::InterruptHandler()
{
  //Receive
  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    _rbuf.push_back(static_cast<uint8_t>(USART_ReceiveData(USART1)));
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
  }
}
