#ifndef LFW_CORE_DEFINES_IVECTOR2_HPP
#define LFW_CORE_DEFINES_IVECTOR2_HPP

#include <cmath>

#include "IVector2Like.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// IVector2 — 二维向量（继承 IVector2Like）
struct IVector2 : IVector2Like
{
  IVector2() = default;
  IVector2(double x, double y) : IVector2Like{x, y} {}

  /// 设置
  void set(double ix, double iy)
  {
    x = ix;
    y = iy;
  }

  /// 加法（改变自身）
  auto &add(const IVector2Like &o)
  {
    x += o.x;
    y += o.y;
    return *this;
  }

  /// 减法（改变自身）
  auto &sub(const IVector2Like &o)
  {
    x -= o.x;
    y -= o.y;
    return *this;
  }

  /// 向量长度
  [[nodiscard]] double length() const
  {
    return std::sqrt(x * x + y * y);
  }

  /// 克隆
  [[nodiscard]] IVector2 clone() const { return *this; }

  /// 归一化
  auto &normalize()
  {
    auto len = length();
    if (len > 0)
    {
      x /= len;
      y /= len;
    }
    return *this;
  }

  /// 相等判断
  [[nodiscard]] bool equals(const IVector2Like &o) const
  {
    return x == o.x && y == o.y;
  }
};

LFW_NS_END

#endif
