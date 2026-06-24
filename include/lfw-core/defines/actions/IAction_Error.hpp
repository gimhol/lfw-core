#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_ERROR_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_ERROR_HPP

#include <string>

#include "IAction_Base.hpp"
#include "ActionType.hpp"
#include "lfw-core/base/Fields.hpp"

/// 动作: 错误 — 对应 TS IAction_Error
struct IAction_Error : IAction_Base
{
  static constexpr ActionType TYPE = ActionType::ERROR;

  ActionType type = TYPE;

  struct Data
  {
    std::string msg;
  };
  Data data;
};

inline const auto &error_data_fields()
{
  static const auto fs = fields<IAction_Error::Data>(
      field("msg", FieldKind::String, &IAction_Error::Data::msg, "错误消息"));
  return fs;
}

#endif
