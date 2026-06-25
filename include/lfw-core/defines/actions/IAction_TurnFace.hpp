#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_TURN_FACE_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_TURN_FACE_HPP

#include "IAction_Base.hpp"
#include "ActionType.hpp"
#include "lfw-core/base/Fields.h"

/// 动作: 转向
struct IAction_TurnFace : IAction_Base
{
  static constexpr ActionType TYPE_V = ActionType::V_TURN_FACE;

  ActionType type = TYPE_V;
};

#endif
