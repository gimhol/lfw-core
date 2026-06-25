#ifndef LFW_CORE_DEFINES_IDRINK_INFO_HPP
#define LFW_CORE_DEFINES_IDRINK_INFO_HPP

#include <optional>
#include <string>

#include "lfw-core/base/Fields.h"

/// IDrinkInfo — 饮料数据
struct IDrinkInfo
{
  std::optional<std::string> id;
  std::optional<std::string> name;

  // HP 恢复
  std::optional<double> hp_h_total;   // 最多恢复 HP
  std::optional<double> hp_h_value;   // 每次恢复 HP
  std::optional<double> hp_h_ticks;   // HP 恢复间隔（帧）

  // 暗 HP 恢复
  std::optional<double> hp_r_total;   // 最多恢复暗 HP
  std::optional<double> hp_r_value;   // 每次恢复暗 HP
  std::optional<double> hp_r_ticks;   // 暗 HP 恢复间隔（帧）

  // MP 恢复
  std::optional<double> mp_h_total;   // 最多恢复 MP
  std::optional<double> mp_h_value;   // 每次恢复 MP
  std::optional<double> mp_h_ticks;   // MP 恢复间隔（帧）
};

inline const auto &drink_info_fields()
{
  static const auto fs = fields<IDrinkInfo>(
      field("id", FieldKind::Str, &IDrinkInfo::id, "ID"),
      field("name", FieldKind::Str, &IDrinkInfo::name, "名称"),
      field("hp_h_total", FieldKind::Flt, &IDrinkInfo::hp_h_total, "总HP恢复"),
      field("hp_h_value", FieldKind::Flt, &IDrinkInfo::hp_h_value, "单次HP恢复"),
      field("hp_h_ticks", FieldKind::Flt, &IDrinkInfo::hp_h_ticks, "HP恢复间隔"),
      field("hp_r_total", FieldKind::Flt, &IDrinkInfo::hp_r_total, "总暗HP恢复"),
      field("hp_r_value", FieldKind::Flt, &IDrinkInfo::hp_r_value, "单次暗HP恢复"),
      field("hp_r_ticks", FieldKind::Flt, &IDrinkInfo::hp_r_ticks, "暗HP恢复间隔"),
      field("mp_h_total", FieldKind::Flt, &IDrinkInfo::mp_h_total, "总MP恢复"),
      field("mp_h_value", FieldKind::Flt, &IDrinkInfo::mp_h_value, "单次MP恢复"),
      field("mp_h_ticks", FieldKind::Flt, &IDrinkInfo::mp_h_ticks, "MP恢复间隔"));
  return fs;
}

#endif
