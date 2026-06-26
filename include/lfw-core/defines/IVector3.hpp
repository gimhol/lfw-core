#ifndef LFW_CORE_DEFINES_IVECTOR3_HPP
#define LFW_CORE_DEFINES_IVECTOR3_HPP

#include <cmath>

#include "IVector3Like.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// IVector3 — 三维向量（继承 IVector3Like）
struct IVector3 : IVector3Like
{
  IVector3() = default;
  IVector3(double x, double y, double z) : IVector3Like{x, y, z} {}

  /// 设置
  void set(double ix, double iy, double iz)
  {
    x = ix;
    y = iy;
    z = iz;
  }

  /// 加法（改变自身）
  auto &add(const IVector3Like &o)
  {
    x += o.x;
    y += o.y;
    z += o.z;
    return *this;
  }

  /// 减法（改变自身）
  auto &sub(const IVector3Like &o)
  {
    x -= o.x;
    y -= o.y;
    z -= o.z;
    return *this;
  }

  /// 复制
  void copy(const IVector3Like &o)
  {
    x = o.x;
    y = o.y;
    z = o.z;
  }

  /// 克隆
  [[nodiscard]] IVector3 clone() const { return *this; }

  /// 向量长度
  [[nodiscard]] double length() const
  {
    return std::sqrt(x * x + y * y + z * z);
  }

  /// 归一化
  auto &normalize()
  {
    auto len = length();
    if (len > 0)
    {
      x /= len;
      y /= len;
      z /= len;
    }
    return *this;
  }

  /// 相等判断
  [[nodiscard]] bool equals(const IVector3Like &o) const
  {
    return x == o.x && y == o.y && z == o.z;
  }
};

LFW_NS_END

#endif
