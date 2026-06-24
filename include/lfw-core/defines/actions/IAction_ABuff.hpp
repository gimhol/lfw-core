#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_ABUFF_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_ABUFF_HPP

#include <optional>
#include <string>

#include "IAction_Base.hpp"
#include "ActionType.hpp"
#include "../HitFlag.hpp"

/// 动作: 攻击者 Buff
struct IAction_ABuff : IAction_Base
{
  static constexpr ActionType TYPE = ActionType::A_BUFF;

  ActionType type = TYPE;

  struct Data
  {
    std::optional<HitFlag> hitflag;
    std::optional<double> duration;
    std::optional<std::string> buff;
  };
  std::optional<Data> data;
};

#endif
