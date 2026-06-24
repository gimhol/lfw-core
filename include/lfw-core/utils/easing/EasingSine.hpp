#ifndef LFW_CORE_UTILS_EASING_EASINGSINE_HPP
#define LFW_CORE_UTILS_EASING_EASINGSINE_HPP

#include <cmath>
#include <algorithm>

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// 正弦缓动 — 对应 TS ease_in_out_sine
struct EasingSine
{
  template <typename T = double>
    requires std::is_floating_point_v<T>
  T operator()(T factor, T from = T(0), T to = T(1)) const
  {
    constexpr T pi = T(3.14159265358979323846);
    return from - ((to - from) * (std::cos(pi * factor) - T(1))) / T(2);
  }

  template <typename T = double>
    requires std::is_floating_point_v<T>
  T backward(T value, T from = T(0), T to = T(1)) const
  {
    constexpr T pi = T(3.14159265358979323846);
    T v_min = std::min(from, to);
    T v_max = std::max(from, to);
    value = std::clamp(value, v_min, v_max);
    return std::acos((T(2) * (from - value)) / (to - from) + T(1)) / pi;
  }
};

LFW_NS_END

#endif
