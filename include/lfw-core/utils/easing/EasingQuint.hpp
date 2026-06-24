#ifndef LFW_CORE_UTILS_EASING_EASINGQUINT_HPP
#define LFW_CORE_UTILS_EASING_EASINGQUINT_HPP

#include <cmath>
#include <algorithm>

namespace lfw::easing
{

  /// 五次缓动 — 对应 TS ease_in_out_quint
  struct EasingQuint
  {
    template <typename T = double>
      requires std::is_floating_point_v<T>
    T operator()(T factor, T from = T(0), T to = T(1)) const
    {
      T ratio = factor < T(0.5)
                    ? T(16) * std::pow(factor, 5)
                    : T(1) - std::pow(T(-2) * factor + T(2), 5) / T(2);
      return from + ratio * (to - from);
    }

    template <typename T = double>
      requires std::is_floating_point_v<T>
    T backward(T value, T from = T(0), T to = T(1)) const
    {
      T v_min = std::min(from, to);
      T v_max = std::max(from, to);
      value = std::clamp(value, v_min, v_max);
      T ratio = (value - from) / (to - from);
      if (ratio < T(0.5))
        return std::pow(ratio / T(16), T(0.2));
      else
        return T(1) - std::pow(T(2) * (T(1) - ratio), T(0.2)) / T(2);
    }
  };

} // namespace lfw::easing

#endif
