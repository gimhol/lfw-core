#include "lfw-core/animation/Easing.h"

#include <algorithm>
#include <cmath>

#include "lfw-core/utils/math/Math.hpp"

LFW_NS_BEGIN

Easing::Easing(double begin_val, double end_val)
{
  _val_1 = begin_val;
  _val_2 = end_val;
}

double Easing::val_1() const { return _val_1; }
void Easing::set_val_1(double v) { _val_1 = v; }

double Easing::val_2() const { return _val_2; }
void Easing::set_val_2(double v) { _val_2 = v; }

const Easing::EasingFunc &Easing::easing() const { return _easing; }
void Easing::set_easing(EasingFunc v) { _easing = std::move(v); }

Easing &Easing::set(double begin_val, double end_val)
{
  _val_1 = begin_val;
  _val_2 = end_val;
  return *this;
}

Easing &Easing::set_easing_chain(EasingFunc v)
{
  _easing = std::move(v);
  return *this;
}

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
    _value = v1 + (v2 - v1) * factor;

  return *this;
}

LFW_NS_END
