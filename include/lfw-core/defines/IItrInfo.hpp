#ifndef LFW_CORE_DEFINES_IITR_INFO_HPP
#define LFW_CORE_DEFINES_IITR_INFO_HPP

#include <optional>
#include <string>

#include "IRect.hpp"
#include "lfw-core/base/Fields.hpp"

/// IItrInfo — 碰撞体信息（攻击）
struct IItrInfo : IQube
{
  std::optional<std::string> id;
  std::optional<std::string> name;
  std::optional<std::string> ref;
  std::optional<int> hit_flag;
  std::optional<int> kind;
  std::optional<int> effect;
  std::optional<double> fall;
  std::optional<double> vrest;
  std::optional<double> bdefend;
  std::optional<double> injury;
  std::optional<double> zwidth;
  std::optional<std::string> test;
};

inline const auto &itr_info_fields()
{
  static const auto fs = fields<IItrInfo>(
      field("id", FieldKind::Str, &IItrInfo::id, "ID"),
      field("hit_flag", FieldKind::Int, &IItrInfo::hit_flag, "碰撞标记"),
      field("kind", FieldKind::Int, &IItrInfo::kind, "类型"),
      field("effect", FieldKind::Int, &IItrInfo::effect, "效果"),
      field("fall", FieldKind::Flt, &IItrInfo::fall, "击倒值"),
      field("vrest", FieldKind::Flt, &IItrInfo::vrest, "速度衰减"),
      field("bdefend", FieldKind::Flt, &IItrInfo::bdefend, "破防值"),
      field("injury", FieldKind::Flt, &IItrInfo::injury, "伤害"),
      field("zwidth", FieldKind::Flt, &IItrInfo::zwidth, "Z宽度"),
      field("x", FieldKind::Flt, &IItrInfo::x, "X"),
      field("y", FieldKind::Flt, &IItrInfo::y, "Y"),
      field("w", FieldKind::Flt, &IItrInfo::w, "宽"),
      field("h", FieldKind::Flt, &IItrInfo::h, "高"),
      field("z", FieldKind::Flt, &IItrInfo::z, "Z"));
  return fs;
}

#endif
