#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_REBOUND_VX_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_REBOUND_VX_HPP

#include "IAction_Base.hpp"
#include "ActionType.hpp"

/// 动作: 反弹速度
struct IAction_ReboundVX : IAction_Base
{
  static constexpr ActionType TYPE_A = ActionType::A_REBOUND_VX;
  static constexpr ActionType TYPE_V = ActionType::V_REBOUND_VX;

  ActionType type = TYPE_A;
};

#endif
