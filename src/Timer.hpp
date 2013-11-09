#pragma once
#include <stdint.h>
#include <boost/utility.hpp>
#include <boost/scoped_ptr.hpp>
#include <vector>

class Timer : private boost::noncopyable
{
public:
  Timer();
  ~Timer();

  static inline void Tick()
  {
    for (std::vector<uint32_t*>::iterator it = _counts.begin();
         it != _counts.end();
         ++it)
    {
      if ((**it) > 0)
         --(**it);
    }
  }

  inline void WaitMs(uint32_t delay)
  {
    _count = delay;
    while (_count > 0);
  }

  inline void Count(uint32_t count)
  {
    _count = count;
  }

  inline uint32_t Count()
  {
    return _count;
  }

private:
  uint32_t _count;
  static std::vector<uint32_t*> _counts;
};
