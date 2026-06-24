#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_TURN_TEAM_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_TURN_TEAM_HPP

#include <optional>
#include <string>

#include "IAction_Base.hpp"
#include "ActionType.hpp"

/// 动作: 转换队伍
struct IAction_TurnTeam : IAction_Base
{
  static constexpr ActionType TYPE_V = ActionType::V_TURN_TEAM;

  ActionType type = TYPE_V;

  struct Data
  {
    std::optional<std::string> team;
  };
  std::optional<Data> data;
};

#endif
