#ifndef LFW_CORE_DEFINES_IVELOCITY_INFO_HPP
#define LFW_CORE_DEFINES_IVELOCITY_INFO_HPP

#include <optional>

#include "lfw-core/base/Fields.hpp"

/// IVelocityInfo — 速度信息
struct IVelocityInfo
{
  std::optional<double> dvx;
  std::optional<double> dvy;
  std::optional<double> dvz;
  std::optional<double> acc_x;
  std::optional<double> acc_y;
  std::optional<double> acc_z;
  std::optional<int> vxm;
  std::optional<int> vym;
  std::optional<int> vzm;
  std::optional<int> ctrl_x;
  std::optional<int> ctrl_y;
  std::optional<int> ctrl_z;
};

inline const auto &velocity_info_fields()
{
  static const auto fs = fields<IVelocityInfo>(
      field("dvx", FieldKind::Flt, &IVelocityInfo::dvx, "DVX"),
      field("dvy", FieldKind::Flt, &IVelocityInfo::dvy, "DVY"),
      field("dvz", FieldKind::Flt, &IVelocityInfo::dvz, "DVZ"),
      field("acc_x", FieldKind::Flt, &IVelocityInfo::acc_x, "加速度X"),
      field("acc_y", FieldKind::Flt, &IVelocityInfo::acc_y, "加速度Y"),
      field("acc_z", FieldKind::Flt, &IVelocityInfo::acc_z, "加速度Z"),
      field("vxm", FieldKind::Int, &IVelocityInfo::vxm, "VX模式"),
      field("vym", FieldKind::Int, &IVelocityInfo::vym, "VY模式"),
      field("vzm", FieldKind::Int, &IVelocityInfo::vzm, "VZ模式"),
      field("ctrl_x", FieldKind::Int, &IVelocityInfo::ctrl_x, "控制X"),
      field("ctrl_y", FieldKind::Int, &IVelocityInfo::ctrl_y, "控制Y"),
      field("ctrl_z", FieldKind::Int, &IVelocityInfo::ctrl_z, "控制Z"));
  return fs;
}

#endif
