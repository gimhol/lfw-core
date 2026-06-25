#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_BROADCAST_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_BROADCAST_HPP

#include <string>

#include "IAction_Base.hpp"
#include "ActionType.hpp"
#include "lfw-core/base/Fields.h"

/// 动作: 广播消息
struct IAction_Broadcast : IAction_Base
{
  static constexpr ActionType TYPE = ActionType::BROADCAST;

  ActionType type = TYPE;

  struct Data
  {
    std::string msg;
  };
  Data data;
};

inline const auto &broadcast_data_fields()
{
  static const auto fs = fields<IAction_Broadcast::Data>(
      field("msg", FieldKind::Str, &IAction_Broadcast::Data::msg, "消息"));
  return fs;
}

#endif
