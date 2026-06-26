#ifndef LFW_CORE_DEFINES_IWPOINT_INFO_HPP
#define LFW_CORE_DEFINES_IWPOINT_INFO_HPP

#include <optional>
#include <string>

#include "IQubePair.hpp"
#include "lfw-core/base/Fields.h"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

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
  std::optional<IQubePair> indicator_info;
};

inline const auto &wpoint_info_fields()
{
  static const auto fs = fields<IWpointInfo>(
      field("kind", FieldKind::Int, &IWpointInfo::kind, "类型"),
      field("x", FieldKind::Flt, &IWpointInfo::x, "X"),
      field("y", FieldKind::Flt, &IWpointInfo::y, "Y"),
      field("z", FieldKind::Flt, &IWpointInfo::z, "Z"),
      field("weaponact", FieldKind::Str, &IWpointInfo::weaponact, "武器动作"),
      field("attacking", FieldKind::Str, &IWpointInfo::attacking, "攻击动作"),
      field("dvx", FieldKind::Flt, &IWpointInfo::dvx, "初速度X"),
      field("dvy", FieldKind::Flt, &IWpointInfo::dvy, "初速度Y"),
      field("dvz", FieldKind::Flt, &IWpointInfo::dvz, "初速度Z"));
  return fs;
}

LFW_NS_END

#endif
