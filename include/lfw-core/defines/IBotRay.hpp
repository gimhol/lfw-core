#ifndef LFW_CORE_DEFINES_IBOT_RAY_HPP
#define LFW_CORE_DEFINES_IBOT_RAY_HPP

#include <optional>

#include "lfw-core/base/Fields.h"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// IBotRay — XZ 射线检测
struct IBotRay
{
  double x = 0;
  double z = 0;
  std::optional<double> min_x;
  std::optional<double> max_x;
  std::optional<double> min_z;
  std::optional<double> max_z;
  /// 目标在射线上的投影距离平方最大值
  std::optional<double> max_d;
  /// 反转判定结果
  std::optional<bool> reverse;
};

inline const auto &bot_ray_fields()
{
  static const auto fs = fields<IBotRay>(
      field("x", FieldKind::Flt, &IBotRay::x, "射线向量X"),
      field("z", FieldKind::Flt, &IBotRay::z, "射线向量Z"),
      field("min_x", FieldKind::Flt, &IBotRay::min_x, "最小X距离"),
      field("max_x", FieldKind::Flt, &IBotRay::max_x, "最大X距离"),
      field("min_z", FieldKind::Flt, &IBotRay::min_z, "最小Z距离"),
      field("max_z", FieldKind::Flt, &IBotRay::max_z, "最大Z距离"),
      field("max_d", FieldKind::Flt, &IBotRay::max_d, "投影距离平方最大值"),
      field("reverse", FieldKind::Bool, &IBotRay::reverse, "反转判定"));
  return fs;
}

LFW_NS_END

#endif
