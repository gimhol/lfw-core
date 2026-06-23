#ifndef LFW_CORE_DEFINES_STAGEACTION_HPP
#define LFW_CORE_DEFINES_STAGEACTION_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

enum class StageAction : uint8_t
{
  GoGoGoRight,
  EnterNextPhase,
  LoopGoGoGoRight
};

inline std::string_view stage_action_to_string(StageAction v)
{
  switch (v)
  {
  case StageAction::GoGoGoRight:
    return "gogogo_right";
  case StageAction::EnterNextPhase:
    return "enter_next_phase";
  case StageAction::LoopGoGoGoRight:
    return "loop_gogogo_right";
  }
  return "";
}

inline std::optional<StageAction> stage_action_from_string(std::string_view s)
{
  static const auto m = std::unordered_map<std::string_view, StageAction>{
      {"gogogo_right", StageAction::GoGoGoRight},
      {"enter_next_phase", StageAction::EnterNextPhase},
      {"loop_gogogo_right", StageAction::LoopGoGoGoRight},
  };
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_STAGEACTION_HPP
