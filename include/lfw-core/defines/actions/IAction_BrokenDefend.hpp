#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_BROKEN_DEFEND_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_BROKEN_DEFEND_HPP

#include "IAction_NextFrame.hpp"

/// 动作: 破防（结构与 NextFrame 相同，type 不同）
struct IAction_BrokenDefend : IAction_NextFrame
{
  static constexpr ActionType TYPE_A = ActionType::A_BROKEN_DEFEND;
  static constexpr ActionType TYPE_V = ActionType::V_BROKEN_DEFEND;

  IAction_BrokenDefend() { type = TYPE_A; }
};

#endif
