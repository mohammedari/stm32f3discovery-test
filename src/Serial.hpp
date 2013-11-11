#pragma once

#include "stm32f30x.h"
#include <stdint.h>
#include <boost/utility.hpp>
#include <boost/circular_buffer.hpp>

class Serial : boost::noncopyable
{
public: //debug
  static struct Initializer
  {
    Initializer();
  } _initializer;

public:
  template<class InsertIterator>
  static uint32_t Read(InsertIterator iit, uint32_t size = _rbufsize)
  {
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    uint32_t received = 0;
    while (!_rbuf.empty() && received < size)
    {
      *iit = _rbuf.front();
      _rbuf.pop_front();
      ++iit;

      ++received;
    }
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    return received;
  }

  template<class ConstIterator>
  static void Write(ConstIterator begin, ConstIterator end)
  {
    USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
    for (ConstIterator it = begin; it != end; ++it)
      _wbuf.push_back(*it);
    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  }

  static void InterruptHandler();

private:
  static const uint32_t _baudrate = 115200;
  static const uint32_t _rbufsize = 512;
  static const uint32_t _wbufsize = 512;

  static boost::circular_buffer<uint8_t> _rbuf;
  static boost::circular_buffer<uint8_t> _wbuf;

  Serial();
};
