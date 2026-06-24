#ifndef LFW_CORE_DEFINES_IWPOINT_INFO_HPP
#define LFW_CORE_DEFINES_IWPOINT_INFO_HPP

#include <optional>
#include <string>

#include "lfw-core/base/Fields.hpp"

/// IWpointInfo — 武器挂载点信息
struct IWpointInfo
{
  int kind = 0;
  double x = 0;
  double y = 0;
  double z = 0;
  std::string weaponact;
  std::optional<std::string> attacking;
  std::optional<double> dvx;
  std::optional<double> dvy;
  std::optional<double> dvz;
};

inline const auto &wpoint_info_fields()
{
  static const auto fs = fields<IWpointInfo>(
      field("kind", FieldKind::Int, &IWpointInfo::kind, "类型"),
      field("x", FieldKind::Float, &IWpointInfo::x, "X"),
      field("y", FieldKind::Float, &IWpointInfo::y, "Y"),
      field("z", FieldKind::Float, &IWpointInfo::z, "Z"),
      field("weaponact", FieldKind::String, &IWpointInfo::weaponact, "武器动作"),
      field("attacking", FieldKind::String, &IWpointInfo::attacking, "攻击动作"),
      field("dvx", FieldKind::Float, &IWpointInfo::dvx, "初速度X"),
      field("dvy", FieldKind::Float, &IWpointInfo::dvy, "初速度Y"),
      field("dvz", FieldKind::Float, &IWpointInfo::dvz, "初速度Z"));
  return fs;
}

#endif
