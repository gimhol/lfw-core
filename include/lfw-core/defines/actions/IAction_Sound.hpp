#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_SOUND_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_SOUND_HPP

#include <string>
#include <vector>
#include <optional>

#include "IAction_Base.hpp"
#include "IPos.hpp"
#include "ActionType.hpp"

/// 动作: 播放声音
struct IAction_Sound : IAction_Base
{
  static constexpr ActionType TYPE_A = ActionType::A_SOUND;
  static constexpr ActionType TYPE_V = ActionType::V_SOUND;

  ActionType type = TYPE_A;

  struct Data
  {
    std::vector<std::string> path; // 声音文件路径列表
    std::optional<IPos> pos;       // 播放位置
  };
  Data data;
};

#endif
