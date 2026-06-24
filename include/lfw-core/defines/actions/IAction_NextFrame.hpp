#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_NEXT_FRAME_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_NEXT_FRAME_HPP

#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "IAction_Base.hpp"
#include "ActionType.hpp"

/// INextFrame — 下一帧跳转描述（简化版，完整版后续补充）
struct INextFrame
{
  std::optional<std::variant<std::string, std::vector<std::string>>> id;
  std::optional<std::variant<std::string, double>> wait;
};

/// 动作: 进入指定帧
struct IAction_NextFrame : IAction_Base
{
  static constexpr ActionType TYPE_A = ActionType::A_NEXT_FRAME;
  static constexpr ActionType TYPE_V = ActionType::V_NEXT_FRAME;

  ActionType type = TYPE_A;
  INextFrame data;
};

#endif
