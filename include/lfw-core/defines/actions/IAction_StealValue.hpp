#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_STEAL_VALUE_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_STEAL_VALUE_HPP

#include <optional>

#include "IAction_Base.hpp"
#include "ActionType.hpp"
#include "lfw-core/base/Fields.hpp"

/// 动作: 偷取值（吸血/吸蓝等）
struct IAction_StealValue : IAction_Base
{
  static constexpr ActionType TYPE = ActionType::VALUE_STEAL;

  ActionType type = TYPE;

  struct Data
  {
    /// 对象: 0=自己, 1=顶级发射者, 2=发射者, 3=持有者
    std::optional<int> target;

    std::optional<double> hp;             // 固定加血
    std::optional<double> hp_r;           // 固定加暗血
    std::optional<double> over_hp_r;      // 允许恢复真伤
    std::optional<double> revive;         // 允许复活
    std::optional<double> mp;             // 固定加蓝
    std::optional<double> itr_hp_ratio;   // 吸血比例
    std::optional<double> itr_hp_r_ratio; // 吸暗血比例
    std::optional<double> itr_mp_ratio;   // 吸蓝比例
    std::optional<double> over_injury;    // 允许超出伤害上限
  };
  std::optional<Data> data;
};

inline const auto &steal_value_data_fields()
{
  static const auto fs = fields<IAction_StealValue::Data>(
      field("target", FieldKind::Int, &IAction_StealValue::Data::target, "目标"),
      field("hp", FieldKind::Float, &IAction_StealValue::Data::hp, "加血"),
      field("hp_r", FieldKind::Float, &IAction_StealValue::Data::hp_r, "加暗血"),
      field("over_hp_r", FieldKind::Float, &IAction_StealValue::Data::over_hp_r, "允许恢复真伤"),
      field("revive", FieldKind::Float, &IAction_StealValue::Data::revive, "允许复活"),
      field("mp", FieldKind::Float, &IAction_StealValue::Data::mp, "加蓝"),
      field("itr_hp_ratio", FieldKind::Float, &IAction_StealValue::Data::itr_hp_ratio, "吸血比例"),
      field("itr_hp_r_ratio", FieldKind::Float, &IAction_StealValue::Data::itr_hp_r_ratio, "吸暗血比例"),
      field("itr_mp_ratio", FieldKind::Float, &IAction_StealValue::Data::itr_mp_ratio, "吸蓝比例"),
      field("over_injury", FieldKind::Float, &IAction_StealValue::Data::over_injury, "允许超伤"));
  return fs;
}

#endif
