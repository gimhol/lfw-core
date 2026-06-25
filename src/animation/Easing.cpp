#include "lfw-core/animation/Easing.hpp"

#include <algorithm>
#include <cmath>

#include "lfw-core/utils/math/Math.hpp"

LFW_NS_BEGIN

Animation &Easing::calc()
{
  bool is_end = done();
  double t = _time;
  double dur = _duration;
  double v1 = _val_1;
  double v2 = _val_2;
  bool rev = reverse();

  if (v1 == v2)
  {
    _value = v1;
    return *this;
  }

  if (is_end)
  {
    _value = rev ? v1 : v2;
    return *this;
  }

  double factor = math::clamp(t / dur, 0.0, 1.0);

  if (_easing)
    _value = _easing(factor, v1, v2);
  else
    _value = v1 + (v2 - v1) * factor; // 线性 fallback

  return *this;
}

LFW_NS_END
