#pragma once
#include <stdint.h>
#include <boost/utility.hpp>
#include <boost/scoped_ptr.hpp>
#include <list>

class Timer : private boost::noncopyable
{
public:
  Timer();
  ~Timer();

  static inline void Tick()
  {
    ++_time;
    for (std::list<uint32_t*>::iterator it = _counts().begin();
         it != _counts().end();
         ++it)
    {
      if ((**it) > 0)
         --(**it);
    }
  }
  
  static inline uint32_t Now()
  {
    return _time;
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
  static uint32_t _time;

  static std::list<uint32_t*>& _counts()
  {
    static std::list<uint32_t*> counts;
    return counts;
  }
};
