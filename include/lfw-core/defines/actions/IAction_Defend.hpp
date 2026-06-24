#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_DEFEND_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_DEFEND_HPP

#include "IAction_NextFrame.hpp"

/// 动作: 防御（结构与 NextFrame 相同，type 不同）
struct IAction_Defend : IAction_NextFrame
{
  // 覆盖常量
  static constexpr ActionType TYPE_A = ActionType::A_DEFEND;
  static constexpr ActionType TYPE_V = ActionType::V_DEFEND;
};

#endif
