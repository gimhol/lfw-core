#ifndef LFW_CORE_DEFINES_ACTIONTYPE_HPP
#define LFW_CORE_DEFINES_ACTIONTYPE_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

enum class ActionType : uint8_t
{
  A_Sound,
  A_NextFrame,
  A_SetProp,
  A_Defend,
  A_BrokenDefend,
  V_Sound,
  V_NextFrame,
  V_SetProp,
  V_Defend,
  V_BrokenDefend,
  A_REBOUND_VX,
  V_REBOUND_VX,
  V_TURN_FACE,
  V_TURN_TEAM,
  FUSION,
  BROADCAST,
  VALUE_STEAL,
  A_BUFF,
  V_BUFF,
};

inline std::string_view action_type_to_string(ActionType v)
{
  switch (v)
  {
  case ActionType::A_Sound:
    return "a_sound";
  case ActionType::A_NextFrame:
    return "a_next_frame";
  case ActionType::A_SetProp:
    return "a_set_prop";
  case ActionType::A_Defend:
    return "a_defend";
  case ActionType::A_BrokenDefend:
    return "a_broken_defend";
  case ActionType::V_Sound:
    return "v_sound";
  case ActionType::V_NextFrame:
    return "v_next_frame";
  case ActionType::V_SetProp:
    return "v_set_prop";
  case ActionType::V_Defend:
    return "v_defend";
  case ActionType::V_BrokenDefend:
    return "v_broken_defend";
  case ActionType::A_REBOUND_VX:
    return "a_rebound_vx";
  case ActionType::V_REBOUND_VX:
    return "v_rebound_vx";
  case ActionType::V_TURN_FACE:
    return "v_turn_face";
  case ActionType::V_TURN_TEAM:
    return "v_turn_team";
  case ActionType::FUSION:
    return "fusion";
  case ActionType::BROADCAST:
    return "broadcast";
  case ActionType::VALUE_STEAL:
    return "VALUE_STEAL";
  case ActionType::A_BUFF:
    return "abuff";
  case ActionType::V_BUFF:
    return "vbuff";
  }
  return "";
}

inline std::optional<ActionType> action_type_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, ActionType> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(ActionType::V_BUFF); ++i)
    {
      auto v = static_cast<ActionType>(i);
      r[action_type_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_ACTIONTYPE_HPP
