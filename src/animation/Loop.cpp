#include "lfw-core/animation/Loop.h"

#include <algorithm>
#include <limits>

LFW_NS_BEGIN

int Loop::count() const { return _count; }

void Loop::set_count(int v)
{
  _count = std::clamp(v, 0, _times);
}

Loop &Loop::set_count_chain(int v)
{
  set_count(v);
  return *this;
}

int Loop::times() const { return _times; }

void Loop::set_times(int v)
{
  _times = std::clamp(v, 0, std::numeric_limits<int>::max());
}

Loop &Loop::set_times_chain(int v)
{
  set_times(v);
  return *this;
}

Loop &Loop::set(int count_val, int times_val)
{
  set_times(times_val);
  set_count(count_val);
  return *this;
}

Loop &Loop::reset()
{
  _count = 0;
  return *this;
}

bool Loop::continue_loop()
{
  if (_times <= 0)
    return true;
  if (_count >= _times)
    return false;
  ++_count;
  return true;
}

bool Loop::done() const
{
  return _times > 0 && _count >= _times;
}

LFW_NS_END
