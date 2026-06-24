#ifndef LFW_CORE_UTILS_EASING_EASINGLINEAR_HPP
#define LFW_CORE_UTILS_EASING_EASINGLINEAR_HPP

#include <type_traits>

#include "lfw-core/core.hpp"

LFW_NS_BEGIN
namespace easing
{

  /// 线性缓动 — 对应 TS ease_linearity
  struct EasingLinear
  {
    template <typename T = double>
      requires std::is_arithmetic_v<T>
    constexpr T operator()(T factor, T from = T(0), T to = T(1)) const
    {
      return from + (to - from) * factor;
    }

    template <typename T = double>
      requires std::is_arithmetic_v<T>
    constexpr T backward(T value, T from = T(0), T to = T(1)) const
    {
      return (value - from) / (to - from);
    }
  };

} // namespace easing
LFW_NS_END

#endif
