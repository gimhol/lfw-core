#ifndef LFW_CORE_ANIMATION_SINE_HPP
#define LFW_CORE_ANIMATION_SINE_HPP

#include <cmath>
#include <numbers>

#include "lfw-core/animation/Periodic.hpp"

LFW_NS_BEGIN

/**
 * 正弦周期动画 — 对应 TS Sine
 *
 * value = height * (sin(v * 2π / 1000) + 1) / 2 + bottom
 */
class Sine : public Periodic
{
public:
  using Periodic::Periodic;

  double method(double v) const override
  {
    constexpr double k = 2.0 * std::numbers::pi / 1000.0;
    return (_h * (std::sin(v * k) + 1.0) / 2.0) + _b;
  }
};

LFW_NS_END

#endif // LFW_CORE_ANIMATION_SINE_HPP
