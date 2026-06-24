#ifndef LFW_CORE_DEFINES_ACTIONTYPE_HPP
#define LFW_CORE_DEFINES_ACTIONTYPE_HPP

#include <cstdint>
#include <cctype>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

enum class ActionType : uint8_t
{
  A_SOUND,
  A_NEXT_FRAME,
  A_SET_PROP,
  A_DEFEND,
  A_BROKEN_DEFEND,
  V_SOUND,
  V_NEXT_FRAME,
  V_SET_PROP,
  V_DEFEND,
  V_BROKEN_DEFEND,
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
  case ActionType::A_SOUND:
    return "A_SOUND";
  case ActionType::A_NEXT_FRAME:
    return "A_NEXT_FRAME";
  case ActionType::A_SET_PROP:
    return "A_SET_PROP";
  case ActionType::A_DEFEND:
    return "A_DEFEND";
  case ActionType::A_BROKEN_DEFEND:
    return "A_BROKEN_DEFEND";
  case ActionType::V_SOUND:
    return "V_SOUND";
  case ActionType::V_NEXT_FRAME:
    return "V_NEXT_FRAME";
  case ActionType::V_SET_PROP:
    return "V_SET_PROP";
  case ActionType::V_DEFEND:
    return "V_DEFEND";
  case ActionType::V_BROKEN_DEFEND:
    return "V_BROKEN_DEFEND";
  case ActionType::A_REBOUND_VX:
    return "A_REBOUND_VX";
  case ActionType::V_REBOUND_VX:
    return "V_REBOUND_VX";
  case ActionType::V_TURN_FACE:
    return "V_TURN_FACE";
  case ActionType::V_TURN_TEAM:
    return "V_TURN_TEAM";
  case ActionType::FUSION:
    return "FUSION";
  case ActionType::BROADCAST:
    return "BROADCAST";
  case ActionType::VALUE_STEAL:
    return "VALUE_STEAL";
  case ActionType::A_BUFF:
    return "A_BUFF";
  case ActionType::V_BUFF:
    return "V_BUFF";
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

  // 转为大写后查找（不区分大小写）
  std::string upper;
  upper.reserve(s.size());
  for (char c : s)
    upper += static_cast<char>(std::toupper(static_cast<unsigned char>(c)));

  auto it = m.find(upper);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_ACTIONTYPE_HPP
