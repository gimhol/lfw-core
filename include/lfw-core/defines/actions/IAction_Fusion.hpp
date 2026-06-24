#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_FUSION_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_FUSION_HPP

#include <optional>
#include <string>
#include <vector>

#include "IAction_Base.hpp"
#include "IAction_NextFrame.hpp"
#include "ActionType.hpp"

/// 动作: 合体
struct IAction_Fusion : IAction_Base
{
  static constexpr ActionType TYPE = ActionType::FUSION;

  ActionType type = TYPE;

  struct Data
  {
    std::string oid;                                          // 合体成为什么
    std::optional<INextFrame> act;                            // 合体后动作
    std::optional<double> time;                               // 合体持续时间
    std::optional<std::vector<std::vector<int>>> cancel_keys; // 取消合体按键
  };
  Data data;
};

#endif
