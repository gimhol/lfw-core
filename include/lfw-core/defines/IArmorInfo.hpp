#ifndef LFW_CORE_DEFINES_IARMOR_INFO_HPP
#define LFW_CORE_DEFINES_IARMOR_INFO_HPP

#include <optional>
#include <string>
#include <vector>

#include "ArmorEnum.hpp"
#include "lfw-core/base/Fields.hpp"

/// IArmorInfo — 护甲信息
struct IArmorInfo
{
  std::optional<std::string> id;
  std::optional<std::string> name;
  std::optional<int> type;
  std::optional<double> toughness;
  std::optional<double> fireproof;
  std::optional<double> antifreeze;
  std::optional<bool> fulltime;
  std::optional<double> injury_ratio;
  std::optional<double> shaking_ratio;
  std::optional<double> motionless_ratio;
  std::optional<std::vector<std::string>> hit_sounds;
  std::optional<std::vector<std::string>> dead_sounds;
};

inline const auto &armor_info_fields()
{
  static const auto fs = fields<IArmorInfo>(
      field("id", FieldKind::Str, &IArmorInfo::id, "ID"),
      field("name", FieldKind::Str, &IArmorInfo::name, "名称"),
      field("type", FieldKind::Int, &IArmorInfo::type, "护甲类型"),
      field("toughness", FieldKind::Flt, &IArmorInfo::toughness, "耐久"),
      field("fireproof", FieldKind::Flt, &IArmorInfo::fireproof, "防火"),
      field("antifreeze", FieldKind::Flt, &IArmorInfo::antifreeze, "防冻"),
      field("fulltime", FieldKind::Bool, &IArmorInfo::fulltime, "全时生效"),
      field("injury_ratio", FieldKind::Flt, &IArmorInfo::injury_ratio, "受伤比例"),
      field("shaking_ratio", FieldKind::Flt, &IArmorInfo::shaking_ratio, "硬直比例"),
      field("motionless_ratio", FieldKind::Flt, &IArmorInfo::motionless_ratio, "不动比例"),
      field("hit_sounds", FieldKind::Strs, &IArmorInfo::hit_sounds, "受击音效"),
      field("dead_sounds", FieldKind::Strs, &IArmorInfo::dead_sounds, "击破音效"));
  return fs;
}

#endif
