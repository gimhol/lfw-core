#include "lfw-core/animation/Animation.hpp"

#include <algorithm>
#include <cmath>

#include "lfw-core/utils/math/Math.hpp"

LFW_NS_BEGIN

// ============================================================
// IAnimation 接口实现
// ============================================================

void Animation::set_duration(double v)
{
  _duration = std::max(0.0, v);
  _time = math::clamp(_time, 0.0, _duration);
}

void Animation::set_time(double v)
{
  _time = math::clamp(v, 0.0, _duration);
}

void Animation::set_reverse(bool v)
{
  _direction = v ? -1 : 1;
}

// ============================================================
// 核心方法
// ============================================================

bool Animation::done() const
{
  if (_duration <= 0)
    return true;
  return _loop.done();
}

void Animation::set_fill_mode(int v)
{
  if (v == 1 || v == 0)
    _fill_mode = v;
}

void Animation::set_direction(int v)
{
  if (v == -1 || v == 1)
    _direction = v;
}

Animation &Animation::start(bool reverse_val)
{
  _loop.reset();
  set_reverse(reverse_val);
  _time = reverse_val ? _duration : 0;
  return *this;
}

Animation &Animation::end(bool reverse_val)
{
  _loop.set_count(std::max(0, _loop.times()));
  set_reverse(reverse_val);
  _time = reverse_val ? 0 : _duration;
  return *this;
}

Animation &Animation::calc()
{
  _value = (_duration == 0) ? _value : _time / _duration;
  return *this;
}

Animation &Animation::update(double dt)
{
  if (done())
    return *this;

  double dur = _duration;
  int dir = _direction;
  double t = _time + dir * dt;

  if (t <= 0)
  {
    do
    {
      _loop.continue_loop();
      t += dur;
    } while (t <= 0);

    if (done() && _fill_mode)
      t = 0;
  }
  else if (t >= dur)
  {
    do
    {
      _loop.continue_loop();
      t -= dur;
    } while (t >= dur);

    if (done() && _fill_mode)
      t = dur;
  }

  _time = math::clamp(t, 0.0, dur);
  calc();
  return *this;
}

Animation &Animation::auto_trip(bool reverse_val, double dt)
{
  if (reverse() == reverse_val)
    return update(dt);

  if (done())
    start(reverse_val);
  else
    set_reverse(reverse_val);

  return update(dt);
}

LFW_NS_END
