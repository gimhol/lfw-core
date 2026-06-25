#ifndef LFW_CORE_DEFINES_IBDY_INFO_HPP
#define LFW_CORE_DEFINES_IBDY_INFO_HPP

#include <optional>
#include <string>
#include <vector>

#include "IRect.hpp"
#include "lfw-core/base/Fields.h"

/// IBdyInfo — 碰撞体信息（身体）
struct IBdyInfo : IQube
{
  std::optional<std::string> id;
  std::optional<std::string> name;
  std::optional<std::string> ref;
  std::optional<int> hit_flag;
  std::optional<std::string> hit_flag_name;
  int kind = 0;
  std::optional<std::string> kind_name;
  std::optional<std::string> test;
};

inline const auto &bdy_info_fields()
{
  static const auto fs = fields<IBdyInfo>(
      field("id", FieldKind::Str, &IBdyInfo::id, "ID"),
      field("name", FieldKind::Str, &IBdyInfo::name, "名称"),
      field("hit_flag", FieldKind::Int, &IBdyInfo::hit_flag, "碰撞标记"),
      field("kind", FieldKind::Int, &IBdyInfo::kind, "类型"),
      field("x", FieldKind::Flt, &IBdyInfo::x, "X"),
      field("y", FieldKind::Flt, &IBdyInfo::y, "Y"),
      field("w", FieldKind::Flt, &IBdyInfo::w, "宽"),
      field("h", FieldKind::Flt, &IBdyInfo::h, "高"),
      field("z", FieldKind::Flt, &IBdyInfo::z, "Z"),
      field("l", FieldKind::Flt, &IBdyInfo::l, "长"));
  return fs;
}

#endif
