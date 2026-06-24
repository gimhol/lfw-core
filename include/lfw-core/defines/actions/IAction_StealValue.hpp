#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_STEAL_VALUE_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_STEAL_VALUE_HPP

#include <optional>

#include "IAction_Base.hpp"
#include "ActionType.hpp"

/// 动作: 偷取值（吸血/吸蓝等）
struct IAction_StealValue : IAction_Base
{
  static constexpr ActionType TYPE = ActionType::VALUE_STEAL;

  ActionType type = TYPE;

  struct Data
  {
    /// 对象: 0=自己, 1=顶级发射者, 2=发射者, 3=持有者
    std::optional<int> target;

    std::optional<double> hp;        // 固定加血
    std::optional<double> hp_r;      // 固定加暗血
    std::optional<double> over_hp_r; // 允许恢复真伤
    std::optional<double> revive;    // 允许复活
    std::optional<double> mp;        // 固定加蓝
  };
  Data data;
};

#endif
