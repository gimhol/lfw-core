#ifndef LFW_CORE_DEFINES_STAGEVAL_HPP
#define LFW_CORE_DEFINES_STAGEVAL_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

enum class StageVal : uint8_t
{
  EnemiesCleared,
  DialogCleared,
  CurPhaseTime,
  CurDialogTime,
  PressAttack,
  PressJump,
  PressDefend,
  PressUp,
  PressDown,
  PressLeft,
  PressRight,
  Broadcast
};

inline std::string_view stage_val_to_string(StageVal v)
{
  switch (v)
  {
  case StageVal::EnemiesCleared:
    return "enemies_cleared";
  case StageVal::DialogCleared:
    return "dialog_cleared";
  case StageVal::CurPhaseTime:
    return "cur_phase_time";
  case StageVal::CurDialogTime:
    return "cur_dialog_time";
  case StageVal::PressAttack:
    return "press_attack";
  case StageVal::PressJump:
    return "press_jump";
  case StageVal::PressDefend:
    return "press_defend";
  case StageVal::PressUp:
    return "press_up";
  case StageVal::PressDown:
    return "press_down";
  case StageVal::PressLeft:
    return "press_left";
  case StageVal::PressRight:
    return "press_right";
  case StageVal::Broadcast:
    return "broadcast";
  }
  return "";
}

inline std::optional<StageVal> stage_val_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, StageVal> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(StageVal::Broadcast); ++i)
    {
      auto v = static_cast<StageVal>(i);
      r[stage_val_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_STAGEVAL_HPP
