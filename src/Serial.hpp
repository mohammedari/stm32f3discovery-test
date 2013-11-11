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
  uint32_t Read(InsertIterator it, uint32_t size = 0)
  {
    return 0;
  }

  template<class ConstIterator>
  void Write(ConstIterator begin, ConstIterator end)
  {
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
