#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_SET_PROP_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_SET_PROP_HPP

#include <string>
#include <any>

#include "IAction_Base.hpp"
#include "ActionType.hpp"

/// 动作: 设置属性
struct IAction_SetProp : IAction_Base
{
  static constexpr ActionType TYPE_A = ActionType::A_SET_PROP;
  static constexpr ActionType TYPE_V = ActionType::V_SET_PROP;

  ActionType type = TYPE_A;
  std::string prop_name;
  std::any prop_value;
};

#endif
