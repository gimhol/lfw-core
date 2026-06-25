#ifndef LFW_CORE_ANIMATION_COSINE_H
#define LFW_CORE_ANIMATION_COSINE_H

#include <cmath>
#include <numbers>

#include "lfw-core/animation/Periodic.h"

LFW_NS_BEGIN

/**
 * 余弦周期动画 — 对应 TS Cosine
 *
 * value = height * (cos(offset + v * 2π / 1000) + 1) / 2 + bottom
 */
class Cosine : public Periodic
{
public:
  using Periodic::Periodic;

  double method(double v) const override
  {
    constexpr double k = 2.0 * std::numbers::pi / 1000.0;
    return (_h * (std::cos(offset + v * k) + 1.0) / 2.0) + _b;
  }
};

LFW_NS_END

#endif
