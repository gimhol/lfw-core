#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_VBUFF_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_VBUFF_HPP

#include <optional>
#include <string>

#include "IAction_Base.hpp"
#include "ActionType.hpp"
#include "../HitFlag.hpp"
#include "lfw-core/base/Fields.hpp"

/// 动作: 受击者 Buff
struct IAction_VBuff : IAction_Base
{
  static constexpr ActionType TYPE = ActionType::V_BUFF;

  ActionType type = TYPE;

  struct Data
  {
    std::optional<HitFlag> hitflag;
    std::optional<double> duration;
    std::optional<std::string> buff;
  };
  std::optional<Data> data;
};

inline const auto &vbuff_data_fields()
{
  static const auto fs = fields<IAction_VBuff::Data>(
      field("duration", FieldKind::Flt, &IAction_VBuff::Data::duration, "持续时间"),
      field("buff", FieldKind::Str, &IAction_VBuff::Data::buff, "Buff 类型"));
  return fs;
}

#endif
