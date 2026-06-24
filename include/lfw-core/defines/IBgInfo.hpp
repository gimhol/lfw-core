#ifndef LFW_CORE_DEFINES_IBG_INFO_HPP
#define LFW_CORE_DEFINES_IBG_INFO_HPP

#include <optional>
#include <string>
#include <vector>

#include "lfw-core/base/Fields.hpp"

/// IBgInfo — 背景信息
struct IBgInfo
{
  std::string name;
  std::string shadow;
  double shadow_w = 0;
  double shadow_h = 0;
  std::vector<std::string> group;
  double left = 0;
  double right = 0;
  double far = 0;
  double near = 0;
  double height = 0;
  std::optional<double> zoom_x;
  std::optional<double> zoom_y;
  std::optional<double> zoom_z;
};

inline const auto &bg_info_fields()
{
  static const auto fs = fields<IBgInfo>(
      field("name",     FieldKind::String, &IBgInfo::name,     "名称"),
      field("shadow",   FieldKind::String, &IBgInfo::shadow,   "阴影文件"),
      field("shadow_w", FieldKind::Float,  &IBgInfo::shadow_w, "阴影宽"),
      field("shadow_h", FieldKind::Float,  &IBgInfo::shadow_h, "阴影高"),
      field("group",    FieldKind::StringArray, &IBgInfo::group, "分组"),
      field("left",     FieldKind::Float,  &IBgInfo::left,     "左边界"),
      field("right",    FieldKind::Float,  &IBgInfo::right,    "右边界"),
      field("far",      FieldKind::Float,  &IBgInfo::far,      "远边界"),
      field("near",     FieldKind::Float,  &IBgInfo::near,     "近边界"),
      field("height",   FieldKind::Float,  &IBgInfo::height,   "高度"),
      field("zoom_x",   FieldKind::Float,  &IBgInfo::zoom_x,   "缩放X"),
      field("zoom_y",   FieldKind::Float,  &IBgInfo::zoom_y,   "缩放Y"),
      field("zoom_z",   FieldKind::Float,  &IBgInfo::zoom_z,   "缩放Z"));
  return fs;
}

#endif
