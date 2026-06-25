#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_SET_PROP_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_SET_PROP_HPP

#include <any>
#include <optional>
#include <string>

#include "IAction_Base.hpp"
#include "ActionType.hpp"
#include "lfw-core/base/Fields.h"

/// 动作: 设置属性 — 对应 TS IAction_SetProp
struct IAction_SetProp : IAction_Base
{
  static constexpr ActionType TYPE_A = ActionType::A_SET_PROP;
  static constexpr ActionType TYPE_V = ActionType::V_SET_PROP;

  ActionType type = TYPE_A;

  struct Data
  {
    std::optional<std::string> name;
    std::optional<std::any> value; // unknown in TS，太通用无法 Fields 反射
  };
  std::optional<Data> data;
};

inline const auto &set_prop_data_fields()
{
  static const auto fs = fields<IAction_SetProp::Data>(
      field("name", FieldKind::Str, &IAction_SetProp::Data::name, "属性名"));
  return fs;
}

#endif
