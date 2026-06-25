#ifndef LFW_CORE_DEFINES_IDRINK_INFO_HPP
#define LFW_CORE_DEFINES_IDRINK_INFO_HPP

#include <optional>
#include <string>

#include "lfw-core/base/Fields.hpp"

/// IDrinkInfo — 饮料数据
struct IDrinkInfo
{
  std::optional<std::string> id;
  std::optional<std::string> name;
  std::optional<double> hp_h_total;
  std::optional<double> mp_total;
  std::optional<double> hp_p;
};

inline const auto &drink_info_fields()
{
  static const auto fs = fields<IDrinkInfo>(
      field("id", FieldKind::Str, &IDrinkInfo::id, "ID"),
      field("name", FieldKind::Str, &IDrinkInfo::name, "名称"),
      field("hp_h_total", FieldKind::Flt, &IDrinkInfo::hp_h_total, "总HP"),
      field("mp_total", FieldKind::Flt, &IDrinkInfo::mp_total, "总MP"),
      field("hp_p", FieldKind::Flt, &IDrinkInfo::hp_p, "HP百分比"));
  return fs;
}

#endif
