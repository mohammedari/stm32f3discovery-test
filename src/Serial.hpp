#pragma once

#include "stm32f30x.h"
#include <stdint.h>
#include <boost/utility.hpp>
#include <boost/circular_buffer.hpp>

class Serial : boost::noncopyable
{
  static struct Initializer
  {
    Initializer();
  } _initializer;

public:
  static size_t Read(char* ptr, size_t len = _rbufsize);
  static size_t Write(char* ptr, size_t len);
  static void InterruptHandler();

private:
  static const uint32_t _baudrate = 115200;
  static const size_t _rbufsize = 512;
  static const size_t _wbufsize = 512;

  static boost::circular_buffer<char> _rbuf;
  static boost::circular_buffer<char> _wbuf;

  Serial();
};
