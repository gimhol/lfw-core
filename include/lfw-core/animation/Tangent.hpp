#ifndef LFW_CORE_ANIMATION_TANGENT_HPP
#define LFW_CORE_ANIMATION_TANGENT_HPP

#include <cmath>
#include <numbers>

#include "lfw-core/animation/Periodic.hpp"

LFW_NS_BEGIN

/**
 * 正切周期动画 — 对应 TS Tangent
 *
 * value = tan(v * 2π / 1000)
 */
class Tangent : public Periodic
{
public:
  using Periodic::Periodic;

  double method(double v) const override
  {
    constexpr double k = 2.0 * std::numbers::pi / 1000.0;
    return std::tan(v * k);
  }
};

LFW_NS_END

#endif // LFW_CORE_ANIMATION_TANGENT_HPP
