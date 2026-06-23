#ifndef LFW_CORE_UTILS_MATH_HPP
#define LFW_CORE_UTILS_MATH_HPP

#include <cmath>
#include <stdexcept>
#include <vector>

// ============================================================
// 基础数学函数 — 对应 base.ts
// ============================================================
namespace math
{

  /// 判断 v 是否在 [min, max] 范围内
  template <typename T>
  constexpr bool between(const T &v, const T &min, const T &max)
  {
    return v >= min && v <= max;
  }

  /// 将 value 限制在 [min, max] 区间 — 对应 clamp.ts
  template <typename T>
  constexpr T clamp(T value, T min, T max)
  {
    return value < min ? min : value > max ? max
                                           : value;
  }

  /// 舍入到指定精度 — 对应 round_float.ts
  inline double round_float(double n, double multiplier = 1000.0)
  {
    return std::round(n * multiplier) / multiplier;
  }

  /// 向下舍入到指定精度 — 对应 floor_float.ts
  inline double floor_float(double n, double multiplier = 1000.0)
  {
    return std::floor(n * multiplier) / multiplier;
  }

  /// 浮点数近似相等 — 对应 float_equal.ts
  inline bool float_equal(double x, double y)
  {
    return round_float(std::abs(x - y)) < 0.0001;
  }

  /// 带偏移的 clamp — 对应 clamp_add.ts
  inline double clamp_add(double value, double offset, double min, double max)
  {
    value = round_float(value + offset);
    return clamp(value, min, max);
  }

  /// 符号函数 — 对应 normalize.ts（返回 -1 / 0 / 1）
  /// @param precision 精度小数位数，0 表示不截断，>0 表示保留几位小数
  inline int normalize(double n, int precision = 3)
  {
    if (precision > 0)
    {
      double mult = std::pow(10.0, precision);
      n = math::floor_float(n, mult);
    }
    if (n > 0)
      return 1;
    if (n < 0)
      return -1;
    return 0;
  }

  // ============================================================
  // 概率 — 对应 probability.ts
  // ============================================================
  inline double probability(double times, double prob)
  {
    double x = clamp(prob, 0.0, 1.0);
    if (x <= 0)
      return 0;
    if (x >= 1)
      return 1;
    return 1.0 - std::pow(1.0 - x, 1.0 / times);
  }

  // ============================================================
  // 点到直线投影 — 对应 project_to_line.ts
  // ============================================================
  inline std::pair<double, double> project_to_line(double px, double py,
                                                   double dx, double dy)
  {
    double d = round_float(dx * dx + dy * dy);
    if (d == 0)
      throw std::invalid_argument("invalid line: direction vector is zero");
    double t = (px * dx + py * dy) / d;
    return {round_float(t * dx), round_float(t * dy)};
  }

  // ============================================================
  // 等差数列 — 对应 range.ts
  // ============================================================
  template <typename T>
  std::vector<T> range(T from, T to, T gap = T(1))
  {
    if (gap == T(0) || (to - from) / gap < T(0))
      throw std::invalid_argument("[range] dead loop!");
    std::vector<T> ret;
    ret.push_back(from);
    for (int i = 1;; ++i)
    {
      T v = from + static_cast<T>(i) * gap;
      if (gap > T(0) ? v > to : v < to)
        break;
      ret.push_back(v);
    }
    return ret;
  }

} // namespace math

// ============================================================
// MersenneTwister — 梅森旋转伪随机数生成器
// 拆分至 MT.hpp
// ============================================================
#include "MT.hpp"

#endif // LFW_CORE_UTILS_MATH_HPP
