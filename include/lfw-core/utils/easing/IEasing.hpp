#ifndef LFW_CORE_UTILS_EASING_IEASING_HPP
#define LFW_CORE_UTILS_EASING_IEASING_HPP

#include <concepts>

namespace lfw::easing
{

  /// 缓动函数概念 — 对应 TS IEasing<Factor, Value>
  /// 要求: operator()(factor, from, to) 和 backward(value, from, to)
  template <typename E, typename T = double>
  concept EasingFunction = requires(E e, T factor, T from, T to, T value) {
    { e(factor, from, to) } -> std::convertible_to<T>;
    { e.backward(value, from, to) } -> std::convertible_to<T>;
  };

} // namespace lfw::easing

#endif
