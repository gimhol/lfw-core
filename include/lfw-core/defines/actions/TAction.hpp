#ifndef LFW_CORE_DEFINES_ACTIONS_TACTION_HPP
#define LFW_CORE_DEFINES_ACTIONS_TACTION_HPP

#include <variant>

#include "IAction_Sound.hpp"
#include "IAction_NextFrame.hpp"
#include "IAction_SetProp.hpp"
#include "IAction_Defend.hpp"
#include "IAction_BrokenDefend.hpp"
#include "IAction_ReboundVX.hpp"
#include "IAction_TurnFace.hpp"
#include "IAction_TurnTeam.hpp"
#include "IAction_Fusion.hpp"
#include "IAction_Broadcast.hpp"
#include "IAction_StealValue.hpp"
#include "IAction_ABuff.hpp"
#include "IAction_VBuff.hpp"

/// TAction — 动作联合类型（对应 TS 的 TAction union）
using TAction = std::variant<
    IAction_Sound,
    IAction_NextFrame,
    IAction_SetProp,
    IAction_Defend,
    IAction_BrokenDefend,
    IAction_ReboundVX,
    IAction_TurnFace,
    IAction_TurnTeam,
    IAction_Fusion,
    IAction_Broadcast,
    IAction_StealValue,
    IAction_ABuff,
    IAction_VBuff>;

#endif
